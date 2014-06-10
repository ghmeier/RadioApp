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

// Includes
#include "IwFeedList.h"
#include "IwRSS.h"

// Macros
IW_SINGLETON_INSTANTIATE(FeedList);
IW_MANAGED_IMPLEMENT_FACTORY(CIwFeedList);

// Externs
extern CIwResGroup* g_ImageTextures;
extern CIwUILabel* g_Title;
extern CIwUIElement* g_Feeds;
extern CIwUIElement* g_FeedTemplate;
extern CIwUITextField* g_TextTitle, *g_TextURL;

//-----------------------------------------------------------------------------

CIwFeedList::CIwFeedList(void)
{
    IW_CLASS_REGISTER(CIwFeed);
    IW_CLASS_REGISTER(CIwFeedList);

    IW_SINGLETON_SET(FeedList);
}

CIwFeedList::~CIwFeedList(void)
{
    for (uint32 i=0;i<m_Feeds.size();i++)
        delete m_Feeds[i];

    m_Feeds.clear();

    IW_SINGLETON_CLEAR(FeedList);
}

void CIwFeedList::AddFeed(const char* title, const char* url)
{
    // Create a new feed and add it to the array
    CIwFeed * newFeed = new CIwFeed();

    newFeed->m_FeedTitle = new char[strlen(title)+1];
    newFeed->m_FeedURL = new char[strlen(url)+1];
    strcpy(newFeed->m_FeedTitle, title);
    strcpy(newFeed->m_FeedURL, url);

    m_Feeds.push_back(newFeed);
}

int CIwFeedList::GetFeed(CIwUIElement * pElement)
{
    // Search through the list of feeds and return the feed that contains pElement
    for (uint32 i=0;i<m_Feeds.size();i++)
    {
        if (m_Feeds[i]->m_Element->IsDescendant(pElement))
        {
            return i;
        }
    }
    return -1;
}

int CIwFeedList::ClickFetch(CIwUIElement * pElement)
{
    // Find the feed that was clicked
    int index = GetFeed(pElement);

    if (index >= 0)
        g_Title->SetCaption(m_Feeds[index]->m_FeedTitle);

    return index;
}

int CIwFeedList::ClickEdit(CIwUIElement * pElement)
{
    // Find the feed to edit
    int index = GetFeed(pElement);

    if (index >= 0)
    {
		g_TextTitle->SetCaption(m_Feeds[index]->m_FeedTitle);
		g_TextURL->SetCaption(m_Feeds[index]->m_FeedURL);
    }

    return index;
}

void CIwFeedList::RemoveFeed(int index)
{
    // Remove feed from array
    delete m_Feeds[index];
    m_Feeds.erase(index);
}

void CIwFeedList::FetchFeed(int index)
{
    // Prepare the RSS object
    g_IwRSS->FetchFeed(m_Feeds[index]->m_FeedURL);

    // Get local time in ms
    //int64 timems = s3eTimerGetUTC() + s3eTimerGetLocaltimeOffset();
    // Set the update time
    //m_Feeds[index]->m_Date = (int32)((int64)(timems / MS_PER_DAY) + UTC_IN_JD);
    //m_Feeds[index]->m_Time = (int32)(timems % MS_PER_DAY);

    m_Feeds[index]->m_Time = s3eTimerGetUTC() + s3eTimerGetLocaltimeOffset();

    // Move the feed to position 0 in the list
    if (index)
    {
        CIwFeed * Feed = m_Feeds[index];
        m_Feeds.erase(index);
        m_Feeds.insert_slow(Feed, 0);
    }
}

void CIwFeedList::EditFeed(int index, const char* pTitle, const char* pURL)
{
    // Free the title and url
    if (m_Feeds[index]->m_FeedTitle)
        delete[] m_Feeds[index]->m_FeedTitle;

    if (m_Feeds[index]->m_FeedURL)
        delete[] m_Feeds[index]->m_FeedURL;

    // Add new title and url
    m_Feeds[index]->m_FeedTitle = new char[strlen(pTitle)+1];
    strcpy(m_Feeds[index]->m_FeedTitle, pTitle);

    m_Feeds[index]->m_FeedURL = new char[strlen(pURL)+1];
    strcpy(m_Feeds[index]->m_FeedURL, pURL);
}



void CIwFeedList::Update()
{
    // Clear all existing items
	for (int h = g_Feeds->GetNumChildren() - 1; h >= 0; --h)
    {
		CIwUIElement * child = g_Feeds->GetChild(h);
		g_Feeds->RemoveChild(child);
        delete child;
    }

    // Get local time in ms
    int64 timems = s3eTimerGetUTC() + s3eTimerGetLocaltimeOffset();

    for (uint32 i=0;i<m_Feeds.size();i++)
    {
        //Instantiate the new item
		CIwUIElement* pItem = g_FeedTemplate->Clone();

        // Prepare the last updated string
        char strUpdated[100] = "";

        if (m_Feeds[i]->m_Time == 0)
            snprintf(strUpdated, 100, "Updated: Never");
        else {
            const char * units = "day";
            uint64 period = (timems - m_Feeds[i]->m_Time);

            if (period < U_MILLIS_PER_MINUTE)
            {
                period = period / U_MILLIS_PER_SECOND;
                units = "second";
            }
            else if (period < U_MILLIS_PER_HOUR)
            {
                period = period / U_MILLIS_PER_MINUTE;
                units = "minute";
            }
            else if (period < U_MILLIS_PER_DAY)
            {
                period = period / U_MILLIS_PER_HOUR;
                units = "hour";
            }
            else
            {
                period = period / U_MILLIS_PER_DAY;
                if (period > 365)
                {
                    period = period / 365;
                    units = "year";
                }
                else if (period > 7)
                {
                    period = period / 7;
                    units = "week";
                }
            }

            if (period == 1)
                snprintf(strUpdated, 100, "Updated: 1 %s ago", units);
            else if (period < 1000)
                snprintf(strUpdated, 100, "Updated: %u %ss ago", (uint32)period, units);
        }

        // Set name/value
        IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("Feed"))->SetCaption(m_Feeds[i]->m_FeedTitle);
        IwSafeCast<CIwUILabel*>(pItem->GetChildNamed("Updated"))->SetCaption(strUpdated);

        // Set the icon based on the URL
        CIwURI URIAddress = CIwURI(m_Feeds[i]->m_FeedURL);
        const char * host = URIAddress.GetHost();

        if (host)
        {
            if (strstr(host, "madewithmarmalade.com"))
                IwSafeCast<CIwUIImage*>(pItem->GetChildNamed("Icon"))->SetStyle("<MarmaladeIcon>");
            else if (strstr(host, "yahoo.com"))
                IwSafeCast<CIwUIImage*>(pItem->GetChildNamed("Icon"))->SetStyle("<YahooIcon>");
            else if (strstr(host, "google.com"))
                IwSafeCast<CIwUIImage*>(pItem->GetChildNamed("Icon"))->SetStyle("<GoogleIcon>");
            else if (strstr(host, "twitter.com"))
                IwSafeCast<CIwUIImage*>(pItem->GetChildNamed("Icon"))->SetStyle("<TwitterIcon>");
        }

        // Give the feed a unique name
        static int32 feednum = 0;
        char buf[20];
        sprintf(buf, "feed_%d", feednum++);
        pItem->SetName(buf);

        //Add to the list and its layout
		g_Feeds->GetLayout()->AddElement(pItem);
        m_Feeds[i]->m_Element = pItem;
    }
}

void CIwFeedList::Serialise()
{
    if (IwSerialiseIsWriting())
    {
        //Writing EventList
        uint32 Feeds = m_Feeds.size();

        IwSerialiseUInt32(Feeds);

        for (uint16 i=0;i<Feeds;i++)
        {
            m_Feeds[i]->Serialise();
        }
    }
    else
    {
        //Reading EventList
        uint32 Feeds, i;

        for (i=0;i<m_Feeds.size();i++)
            delete m_Feeds[i];

        m_Feeds.clear();

        IwSerialiseUInt32(Feeds);

        //Read in Feeds one by one
        for (i=0;i<Feeds;i++)
        {
            CIwFeed * newFeed = new CIwFeed();
            newFeed->Serialise();

            m_Feeds.push_back(newFeed);
        }
    }
}
