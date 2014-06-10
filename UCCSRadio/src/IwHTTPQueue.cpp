/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This source code is intended only as a supplement to the Marmalade SDK.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */
#include "IwHTTPQueue.h"
#include "IwUtil.h"
#include "s3eConfig.h"

IW_SINGLETON_INSTANTIATE(HTTPQueue);

CIwHTTPQueue::CIwHTTPQueue() :
    m_ActiveRequest(NULL),
    m_Result(NULL),
    m_ResultLen(0),
    m_GotResult(false),
    m_MaxResultLen(-1)
{
    IW_SINGLETON_SET(HTTPQueue);
}

CIwHTTPQueue::~CIwHTTPQueue()
{
    IW_SINGLETON_CLEAR(HTTPQueue);

    while (m_QueuedRequests.size())
    {
        delete m_QueuedRequests.pop_back_get();
    }

    delete m_ActiveRequest;

    s3eFree(m_Result);
}

int32 CIwHTTPQueue::GotData()
{
    int32 newLen = m_HTTP.ContentExpected();

    if (m_HTTP.GetStatus() == S3E_RESULT_ERROR ||
        !IsResultLenAllowed(newLen))
    {
        // Free data now
        s3eFree(m_Result);
        m_Result = NULL;
        m_ResultLen = 0;

        m_GotResult = true;
    }
    else if (!m_HTTP.ContentFinished())
    {
        // We have some data but not all of it. We need more space.
        int32 oldLen = m_ResultLen;

        // Allocate some more space and fetch the data.
        m_ResultLen = newLen;
        m_Result = (char*)s3eRealloc(m_Result, m_ResultLen + 1);

        int32 timeout = GetConnectionTimeout();
        m_HTTP.ReadDataAsync(&m_Result[oldLen], m_ResultLen - oldLen,
            timeout, GotDataCallback, this);
    }
    else
    {
        int finalLength = MIN(m_ResultLen, (int32)m_HTTP.ContentReceived());
        m_ResultLen = finalLength;
        m_Result[m_ResultLen] = 0;
        m_GotResult = true;
    }

    return 0;
}

int32 CIwHTTPQueue::GotDataCallback(void* object, void* argument)
{
    return ((CIwHTTPQueue*) argument)->GotData();
}

// Called when the response headers have been received
int32 CIwHTTPQueue::GotHeaders()
{
    IwAssert(HTTP, !m_Result && !m_ResultLen);

    if (m_HTTP.GetStatus() == S3E_RESULT_ERROR)
    {
        // Something has gone wrong.
        // Pass NULL result to handler to indicate error.
        m_GotResult = true;
    }
    else
    {
        m_ResultLen = m_HTTP.ContentExpected();
        if (!m_ResultLen)
        {
            // Depending on encoding, we don't always know how much to expect
            m_ResultLen = 1024;
        }

        // Ensure we have space to null-terminate result
        m_Result = (char*)s3eMalloc(m_ResultLen + 1);

        int32 timeout = GetConnectionTimeout();
        m_HTTP.ReadDataAsync(m_Result, m_ResultLen, timeout, GotDataCallback, this);
    }
    return 0;
}

int32 CIwHTTPQueue::GotHeadersCallback(void* object, void* argument)
{
    return ((CIwHTTPQueue*)argument)->GotHeaders();
}

// Add request the back of the queue
void CIwHTTPQueue::Get(const char* pURL, void* pArgument, HTTPHandler pHandler)
{
    Request* pGetRequest = new Request(pURL, pArgument, pHandler);
    m_QueuedRequests.push_back(pGetRequest);
}

// Add request the front of the queue
void CIwHTTPQueue::GetFirst(const char* pURL, void* pArgument, HTTPHandler pHandler)
{
    Request* pGetRequest = new Request(pURL, pArgument, pHandler);
    m_QueuedRequests.insert_slow(pGetRequest, 0);
}

void CIwHTTPQueue::CancelByArgument(void *pArgument)
{
    // Cancel any requests with matching argument
    for (int i=m_QueuedRequests.size()-1; i>=0; --i)
    {
        if (m_QueuedRequests[i]->HasArgument(pArgument))
        {
            delete m_QueuedRequests[i];
            m_QueuedRequests.erase(i);
        }
    }

    // Check active request
    if (m_ActiveRequest && m_ActiveRequest->HasArgument(pArgument))
    {
        CancelActiveRequest();
    }
}

void CIwHTTPQueue::CancelActiveRequest()
{
    m_HTTP.Cancel();

    // Clean-up
    s3eFree(m_Result);
    m_Result = NULL;
    m_ResultLen = 0;
    m_GotResult = false;

    delete m_ActiveRequest;
    m_ActiveRequest = NULL;
}

bool CIwHTTPQueue::IsResultLenAllowed(int32 resultLen) const
{
    if (m_MaxResultLen >= 0)
    {
        return resultLen <= m_MaxResultLen;
    }
    return true;
}

int32 CIwHTTPQueue::GetConnectionTimeout() const
{
    int ms = 60000; // 1 minute
    s3eConfigGetInt("connection", "httpconnecttimeout", &ms);

    return ms;
}

void CIwHTTPQueue::Update()
{
    if (m_ActiveRequest && m_GotResult)
    {
        // Call the request's handler with the received data
        m_ActiveRequest->HandleResult(m_Result, m_ResultLen);

        CancelActiveRequest();
    }

    if (!m_ActiveRequest && m_QueuedRequests.size())
    {
        IwAssert(HTTP, !m_Result && !m_ResultLen);

        m_ActiveRequest = m_QueuedRequests.front();
        m_QueuedRequests.erase(0);

        CIwURI uri(m_ActiveRequest->GetURL());
        if (uri.GetProtocol() == CIwURI::HTTP)
        {
            // Fetch remote resource
            m_HTTP.Get(uri.GetAll(), GotHeadersCallback, this);
        }
        else if (uri.GetProtocol() == CIwURI::FILE)
        {
            // Fetch local file
            s3eFile* file = s3eFileOpen(uri.GetHost(), "rb");
            if (file)
            {
                int32 fileSize = s3eFileGetSize(file);
                char* pFileData = (char*)s3eMalloc(fileSize+1);

                if ((int32)s3eFileRead(pFileData, 1, fileSize, file) == fileSize)
                {
                    m_Result = pFileData;
                    m_ResultLen = fileSize;
                    m_Result[m_ResultLen] = 0;
                }
                else
                {
                    s3eFree(pFileData);
                }

                s3eFileClose(file);
            }

            m_GotResult = true;
        }
        else
        {
            IwAssertMsg(UI, false, ("Unhandled URI: %s", uri.GetAll()));
        }
    }
}

void CIwHTTPQueue::SetMaxResultLen(int32 maxResultLen)
{
    m_MaxResultLen = maxResultLen;
}

CIwHTTPQueue::Request::Request(const char* pURL, void* pArgument, HTTPHandler pHandler) :
    m_URL(strdup(pURL)),
    m_Argument(pArgument),
    m_Handler(pHandler)
{
}

CIwHTTPQueue::Request::~Request()
{
    free(m_URL);
}

void CIwHTTPQueue::Request::HandleResult(char* pResult, int32 resultLen)
{
    if (m_Handler)
    {
        m_Handler(m_Argument, m_URL, pResult, resultLen);
    }
}
