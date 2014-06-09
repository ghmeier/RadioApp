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
    CalendarBG = Iw2DCreateImage("textures/calendarBG.png");
    EventsBG = Iw2DCreateImage("textures/eventsBG.png");
    NewsBG = Iw2DCreateImage("textures/newsBG.png");
    PlayButton = Iw2DCreateImage("textures/button-up.png");
    StopButton = Iw2DCreateImage("textures/button-stop.png");
    PlayWrapper = Iw2DCreateImage("textures/bottom-wrapper.png");
    Header = Iw2DCreateImage("textures/header.png");
    CalendarBanner = Iw2DCreateImage("textures/calendarBanner.png");
    EventsBanner = Iw2DCreateImage("textures/eventsBanner.png");
    NewsBanner = Iw2DCreateImage("textures/newsBanner.png");
    
    // Load fonts
    /*Font = Iw2DCreateFont("fonts/arial8.gxfont");
    
    // Create atlases
    int frame_w = (int)(Gems[0]->GetWidth() / 5);
    int frame_h = (int)(Gems[0]->GetHeight() / 3);
    for (int t = 0; t < MAX_GEM_TYPES; t++)
        GemAtlases[t] = new CAtlas(frame_w, frame_h, 15, Gems[t]);
    frame_w = (int)(Explosion->GetWidth() / 5);
    frame_h = (int)(Explosion->GetHeight() / 3);
    ExplosionAtlas = new CAtlas(frame_w, frame_h, 15, Explosion);
     */
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
}

// Global resources
Resources* g_pResources = 0;



