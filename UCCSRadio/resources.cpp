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
    CalendarBG = Iw2DCreateImage("textures/whiteBG.png");
    EventsBG = Iw2DCreateImage("textures/whiteBG.png");
    NewsBG = Iw2DCreateImage("textures/whiteBG.png");
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
    GoldBanner = Iw2DCreateImage("textures/goldBanner.png");
    ReadMore = Iw2DCreateImage("textures/readMore.png");

	//--------------
	BannerFontLarge = Iw2DCreateFont("trackfont72.gxfont");
	BannerFontSmall = Iw2DCreateFont("trackfont48.gxfont");
	HeaderFont = Iw2DCreateFont("palatfont36.gxfont");
	ContentFont = Iw2DCreateFont("palatfont32.gxfont");

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
	//delete Font24;
	//delete Font28;
	//delete Font32;
	//delete PFont24;
	delete BannerFontLarge;
	delete BannerFontSmall;
    delete GoldBanner;
    delete ReadMore;
}

// Global resources
Resources* g_pResources = 0;



