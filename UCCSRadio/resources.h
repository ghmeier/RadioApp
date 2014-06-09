/*
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This document is protected by copyright, and contains information
 * proprietary to Marmalade.
 *
 * This file consists of source code released by Marmalade under
 * the terms of the accompanying End User License Agreement (EULA).
 * Please do not use this program/source code before you have read the
 * EULA and have agreed to be bound by its terms.
 */

#if !defined(__RESOURCES_H__)
#define __RESOURCES_H__

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"

using namespace Iw2DSceneGraph;

/**
 * @class Resources
 *
 * @brief Resources class
 *
 * The that manages the lifetime of the following types of resources:
 * - Images
 * - Fonts
 * - Atlases
 */
class Resources
{
protected:
    
    CIw2DImage*     CalendarBG;
    CIw2DImage*     EventsBG;
    CIw2DImage*     NewsBG;
    CIw2DImage*     PlayButton;
    CIw2DImage*     PlayWrapper;
    CIw2DImage*     Header;
    
public:
    
    CIw2DImage*     getCalendarBG()                 { return CalendarBG; }
    CIw2DImage*     getEventsBG()                   { return EventsBG; }
    CIw2DImage*     getNewsBG()                     { return NewsBG; }
    CIw2DImage*     getPlayButton()                 { return PlayButton; }
    CIw2DImage*     getPlayWrapper()                { return PlayWrapper; }
    CIw2DImage*     getHeader()                     { return Header; }

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


