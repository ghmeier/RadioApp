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

#include "resources.h"
#include "Iw2D.h"

Resources::Resources()
{
    // Load images
    CalendarBG = Iw2DCreateImage("textures/calendarBGSmall.png");
    EventsBG = Iw2DCreateImage("textures/eventsBGSmall.png");
    NewsBG = Iw2DCreateImage("textures/newsBGSmall.png");
    PlayButton = Iw2DCreateImage("textures/button-upSmall.png");
    StopButton = Iw2DCreateImage("textures/button-stopSmall.png");
    PlayWrapper = Iw2DCreateImage("textures/bottom-wrapper.png");
    Header = Iw2DCreateImage("textures/headerSmall.png");
    CalendarBanner = Iw2DCreateImage("textures/CalendarBannerSmall.png");
    EventsBanner = Iw2DCreateImage("textures/EventsBannerSmall.png");
    NewsBanner = Iw2DCreateImage("textures/NewsBannerSmall.png");
    CalendarSideBanner = Iw2DCreateImage("textures/calendarSideBannerSmall.png");
    EventsSideBanner = Iw2DCreateImage("textures/eventsSideBannerSmall.png");
    NewsSideBanner = Iw2DCreateImage("textures/newsSideBannerSmall.png");
    WhiteBanner = Iw2DCreateImage("textures/whiteBanner.png");
	GreyBanner = Iw2DCreateImage("textures/greyBanner.png");

	Font = Iw2DCreateFont("trackFont.gxfont");
	Font20 = Iw2DCreateFont("trackFont20.gxfont");

}

Resources::~Resources()
{
    
    delete CalendarBG;
    delete EventsBG;
    delete NewsBG;
    delete PlayButton;
    delete PlayWrapper;
    delete Header;
    delete StopButton;
    delete CalendarBanner;
    delete EventsBanner;
    delete NewsBanner;
    delete CalendarSideBanner;
    delete EventsSideBanner;
    delete NewsSideBanner;
    delete WhiteBanner;
    delete GreyBanner;
    delete Font;
    
}

// Global resources
Resources* g_pResources = 0;



