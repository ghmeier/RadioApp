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

#ifndef IW_FEED_LIST_H
#define IW_FEED_LIST_H

// Includes
#include "IwUI.h"
#include "IwUIElement.h"
#include "IwFeed.h"
#include "IwArray.h"
#include "IwManaged.h"
#include "IwSerialise.h"

//-----------------------------------------------------------------------------

class CIwFeedList : public CIwManaged
{
public:
    IW_MANAGED_DECLARE(CIwFeedList);

    CIwFeedList(void);
    ~CIwFeedList(void);

    int GetFeed(CIwUIElement* pElement);
    int ClickFetch(CIwUIElement * pElement);
    int ClickEdit(CIwUIElement * pElement);

    void AddFeed(const char* title, const char* url);
    void EditFeed(int index, const char* pTitle, const char* pURL);
    void FetchFeed(int index);
    void RemoveFeed(int index);

    void Update();

    void Serialise();



private:
    //Array of Events
    CIwArray<CIwFeed*> m_Feeds;
};

IW_SINGLETON_EXTERN(FeedList);

#endif
