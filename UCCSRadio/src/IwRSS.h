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
#ifndef IW_RSS_H
#define IW_RSS_H

#include "s3eDebug.h"
#include "s3eDevice.h"
#include "s3eFile.h"
#include "s3eKeyboard.h"
#include "s3eTimer.h"
#include "s3eSurface.h"
#include "IwHTTPQueue.h"
#include "IwUILabel.h"
#include "IwArray.h"
#include <string>
#include <vector>

//-----------------------------------------------------------------------------

class CIwRSS
{
public:
    CIwRSS();
    ~CIwRSS(void);

    // Public interface
    void Update();
    void FetchFeed(const char* url);
	//void Init();
    void CancelFetch();

    // What proportion of a feed's items have we fetched
    iwfixed GetProgress() const { return m_Progress; }

private:
    struct CFeedItem
    {
    public:
        CFeedItem();
        CFeedItem(const char* url, const char* imageTitle);
        ~CFeedItem();

        const char* GetURL() const { return m_URL; }
        const char* GetImageTitle() const { return m_ImageTitle; }

    private:
        char* m_URL;
        char* m_ImageTitle;
    };

    // Callback for HTTP queue
    static void HTTPHandler(void* pArgument, const char* pURL,
        const char* pResult, int32 resultLen);

    // Private utils
    void Fetch(CFeedItem* pFeed);
    void FetchImage(const char* url, const char* title);
    void ParseRSS(const char* data);
    void HandleResult(const char* url, const char* data, int32 dataLen);
    const CFeedItem* GetFeedItemByURL(const char* url) const;

    // Member data
    CIwHTTPQueue            m_HTTPQueue;
    CIwArray<CFeedItem*>    m_FeedItems;
    iwfixed                 m_Progress;
};

extern CIwRSS * g_IwRSS;

#endif
