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
    
	Font = Iw2DCreateFont("trackFont.gxfont");
	Font20 = Iw2DCreateFont("trackFont20.gxfont");
	Font7 = Iw2DCreateFont("font7.gxfont");
	Font12 = Iw2DCreateFont("trackFont12.gxfont");
	Font16 = Iw2DCreateFont("trackFont16.gxfont");
	Font24 = Iw2DCreateFont("trackFont24.gxfont");
	Font28 = Iw2DCreateFont("trackFont28.gxfont");
	Font32 = Iw2DCreateFont("trackFont32.gxfont");
	PFont12 = Iw2DCreateFont("palatFont12.gxfont");
	PFont16 = Iw2DCreateFont("palatFont16.gxfont");
	PFont20 = Iw2DCreateFont("palatFont20.gxfont");
	PFont24 = Iw2DCreateFont("palatFont24.gxfont");

	//--------------
	BannerFontLarge = Font24;
	BannerFontSmall = Font32;

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
	delete Font20;
	delete Font7;
    delete GoldBanner;
    delete ReadMore;
    
}

// Global resources
Resources* g_pResources = 0;



