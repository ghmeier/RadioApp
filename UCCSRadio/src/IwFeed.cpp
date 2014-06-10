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
#include "IwFeed.h"
#include <stdio.h>

// Macros
IW_MANAGED_IMPLEMENT_FACTORY(CIwFeed);

//-----------------------------------------------------------------------------

CIwFeed::CIwFeed(void)
{
    m_Element = 0;
    m_FeedTitle = 0;
    m_FeedURL = 0;
    m_Time = 0;
    m_Hash = 0;
}

CIwFeed::~CIwFeed(void)
{
    if (m_FeedTitle)
        delete[] m_FeedTitle;

    if (m_FeedURL)
        delete[] m_FeedURL;
}


void CIwFeed::Serialise()
{
    if (IwSerialiseIsWriting())
    {
        //Write out the object state
        uint32 time = (uint32)(m_Time & 0xFFFFFFFF);
        uint32 time32 = (uint32)((m_Time >> 32) & 0xFFFFFFFF);
        IwSerialiseUInt32(time);
        IwSerialiseUInt32(time32);
        IwSerialiseUInt32(m_Hash);

        uint32 titlesize = strlen(m_FeedTitle) + 1;
        uint32 urlsize = strlen(m_FeedURL) + 1;
        IwSerialiseUInt32(titlesize);
        IwSerialiseUInt32(urlsize);
        IwSerialiseChar(*m_FeedTitle, titlesize);
        IwSerialiseChar(*m_FeedURL, urlsize);
    }
    else
    {
        //Read in the object state
        uint32 time;
        uint32 time32;
        IwSerialiseUInt32(time);
        IwSerialiseUInt32(time32);
        m_Time = time + ((uint64)time32 << 32);
        IwSerialiseUInt32(m_Hash);

        uint32 titlesize;
        uint32 urlsize;

        IwSerialiseUInt32(titlesize);
        IwSerialiseUInt32(urlsize);
        m_FeedTitle = new char[titlesize];
        m_FeedURL = new char[urlsize];
        IwSerialiseChar(*m_FeedTitle, titlesize);
        IwSerialiseChar(*m_FeedURL, urlsize);
    }
}
