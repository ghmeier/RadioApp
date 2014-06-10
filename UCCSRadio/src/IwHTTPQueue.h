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
#ifndef IW_HTTPQUEUE_H
#define IW_HTTPQUEUE_H

#include "IwSingleton.h"
#include "IwHTTP.h"
#include "IwArray.h"

typedef void (*HTTPHandler)(void * Argument, const char* URL,
    const char * Result, int32 ResultLen);

class CIwHTTPQueue
{
public:
    CIwHTTPQueue();
    ~CIwHTTPQueue();

    void Get(const char* pURL, void* pArgument, HTTPHandler pHandler);
    void GetFirst(const char* pURL, void* pArgument, HTTPHandler pHandler);
    void CancelByArgument(void* pArgument);

    void Update();
    void SetMaxResultLen(int32 maxResultLen);

private:
    void CancelActiveRequest();

    bool IsResultLenAllowed(int32 resultLen) const;
    int32 GetConnectionTimeout() const;

    int32 GotData();
    static int32 GotDataCallback(void* object, void* argument);

    int32 GotHeaders();
    static int32 GotHeadersCallback(void* object, void* argument);

    struct Request
    {
        Request(const char* pURL, void* pArgument, HTTPHandler pHandler);
        ~Request();

        void HandleResult(char* pResult, int32 resultLen);

        const char* GetURL() const { return m_URL; }
        bool HasArgument(void* pArgument) const { return m_Argument == pArgument; }

    private:
        char*       m_URL;
        void*       m_Argument;
        HTTPHandler m_Handler;
    };

    CIwArray<Request*>  m_QueuedRequests;
    Request*            m_ActiveRequest;

    CIwHTTP             m_HTTP;
    int32               m_MaxResultLen;

    char*               m_Result;
    int32               m_ResultLen;
    bool                m_GotResult;
};

IW_SINGLETON_EXTERN(HTTPQueue);

#endif
