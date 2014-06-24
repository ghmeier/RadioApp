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
    
    CIw2DImage*     background;
    CIw2DImage*     PlayButton;
    CIw2DImage*     StopButton;
    CIw2DImage*     PlayWrapper;
    CIw2DImage*     Header;
    CIw2DImage*     WhiteBanner;
    CIw2DImage*     GreyBanner;
    CIw2DImage*     GoldBanner;
    CIw2DImage*     Facebook;
    CIw2DImage*     Twitter;
    
	CIw2DFont*		BannerFontLarge;
	CIw2DFont*		BannerFontSmall;
	CIw2DFont*		HeaderFont;
	CIw2DFont*		ContentFont;
    
public:
    CIw2DImage*     getPlayButton()                 { return PlayButton; }
    CIw2DImage*     getStopButton()                 { return StopButton; }
    CIw2DImage*     getPlayWrapper()                { return PlayWrapper; }
    CIw2DImage*     getHeader()                     { return Header; }
    CIw2DImage*     getbackground()                 { return background; }
    CIw2DImage*     getWhiteBanner()                { return WhiteBanner; }
    CIw2DImage*     getGoldBanner()                 { return GoldBanner; }
    CIw2DImage*     getGreyBanner()                 { return GreyBanner; }
    CIw2DImage*     getFacebook()                   { return Facebook; }
    CIw2DImage*     getTwitter()                    { return Twitter; }
	
    CIw2DFont*		getBannerFontLarge()			{ return BannerFontLarge; }
	CIw2DFont*		getBannerFontSmall()			{ return BannerFontSmall; }
	CIw2DFont*		getHeaderFont()					{ return HeaderFont; }
	CIw2DFont*		getContentFont()				{ return ContentFont; }

public:
    Resources();
    ~Resources();
};

extern Resources* g_pResources;

#endif  // __RESOURCES_H__


