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
#include "IwGx.h"

Resources::Resources()
{
    // Load images
    background = Iw2DCreateImage("textures/whiteBG.png");
    PlayButton = Iw2DCreateImage("textures/button-upSmall.png");
    StopButton = Iw2DCreateImage("textures/button-stopSmall.png");
    PlayWrapper = Iw2DCreateImage("textures/bottom-wrapper-large.png");
    Header = Iw2DCreateImage("textures/headerSmall.png");
    WhiteBanner = Iw2DCreateImage("textures/whiteBanner.png");
	GreyBanner = Iw2DCreateImage("textures/greyBanner.png");
    GoldBanner = Iw2DCreateImage("textures/goldBanner.png");

	//--------------
	char * one;
	char * two;
	char * three;
	char * four;
	if (IwGxGetDisplayWidth()>=520){
		one = "trackfont72.gxfont";
		two = "trackfont48.gxfont";
		three = "trebfont48.gxfont";
		four = "trebfont32.gxfont";
	}
	else 
	{
		one = "trackfont48.gxfont";
		two = "trackfont32.gxfont";
		three = "trebfont32.gxfont";
		four = "trebfont24.gxfont";
	}

	BannerFontLarge = Iw2DCreateFont(one);
	BannerFontSmall = Iw2DCreateFont(two);
	HeaderFont = Iw2DCreateFont(three);
	ContentFont = Iw2DCreateFont(four);

}

Resources::~Resources()
{
    delete PlayButton;
    delete PlayWrapper;
    delete Header;
    delete StopButton;
    delete WhiteBanner;
    delete GreyBanner;
	delete BannerFontLarge;
	delete BannerFontSmall;
    delete GoldBanner;
    delete HeaderFont;
    delete ContentFont;
    delete background;
}

// Global resources
Resources* g_pResources = 0;



