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

#ifndef IW_FEED_H
#define IW_FEED_H

// Includes
#include "IwManaged.h"
#include "IwSerialise.h"
#include "IwUIElement.h"

#define U_MILLIS_PER_SECOND 1000
#define U_MILLIS_PER_MINUTE 60000
#define U_MILLIS_PER_HOUR   3600000
#define U_MILLIS_PER_DAY    86400000

//-----------------------------------------------------------------------------

class CIwFeed : public CIwManaged
{
public:
    IW_MANAGED_DECLARE(CIwFeed);

    //Serialised data
    uint64 m_Time;
    char* m_FeedTitle;
    char* m_FeedURL;
    uint32 m_Hash;

    //Discardable data
    CIwUIElement * m_Element;

    CIwFeed(void);
    ~CIwFeed(void);
    void Serialise();
};

#endif
