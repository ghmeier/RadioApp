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
    CIw2DImage*     StopButton;
    CIw2DImage*     PlayWrapper;
    CIw2DImage*     Header;
    CIw2DImage*     CalendarBanner;
    CIw2DImage*     EventsBanner;
    CIw2DImage*     NewsBanner;
    CIw2DImage*     CalendarSideBanner;
    CIw2DImage*     EventsSideBanner;
    CIw2DImage*     NewsSideBanner;
<<<<<<< HEAD
    CIw2DImage*     WhiteBanner;
=======
	CIw2DFont*		Font;
>>>>>>> b578d7d3dea54aa2619ab4b9564172b5cef20302
    
    
public:
    
    CIw2DImage*     getCalendarBG()                 { return CalendarBG; }
    CIw2DImage*     getEventsBG()                   { return EventsBG; }
    CIw2DImage*     getNewsBG()                     { return NewsBG; }
    CIw2DImage*     getPlayButton()                 { return PlayButton; }
    CIw2DImage*     getStopButton()                 { return StopButton; }
    CIw2DImage*     getPlayWrapper()                { return PlayWrapper; }
    CIw2DImage*     getHeader()                     { return Header; }
    CIw2DImage*     getCalendarBanner()             { return CalendarBanner; }
    CIw2DImage*     getEventsBanner()               { return EventsBanner; }
    CIw2DImage*     getNewsBanner()                 { return NewsBanner; }
    CIw2DImage*     getCalendarSideBanner()         { return CalendarSideBanner; }
    CIw2DImage*     getEventsSideBanner()           { return EventsSideBanner; }
    CIw2DImage*     getNewsSideBanner()             { return NewsSideBanner; }
<<<<<<< HEAD
    CIw2DImage*     getWhiteBanner()                { return WhiteBanner; }
    
=======
	CIw2DFont*		getFont()						{ return Font; }
>>>>>>> b578d7d3dea54aa2619ab4b9564172b5cef20302

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;




#endif  // __RESOURCES_H__


