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

#include "streamer.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "eventsScene.h"
#include <IwHTTP.h>
#include "src/HttpClient.h"
#include "calendarScene.h"
#include "newsScene.h"
#include "eventsScene.h"
#include "newsStory.h"
#include "s3eOSExec.h"


NewsStory::~NewsStory()
{
	link = nullptr;
}

void NewsStory::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
    
    if (!g_pInput->m_Touched && g_pInput->m_PrevTouched && sceneSwitchComplete)
    {
        if(readMore->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            g_pInput->Reset();
			if (s3eOSExecAvailable()) {
/*<<<<<<< HEAD
				s3eOSExecExecute(link, S3E_TRUE);
=======*/
				s3eOSExecExecute(link, S3E_FALSE);
//>>>>>>> 8e01e814bbeb267d1b438018728d469089c12ac2
			}
        }
    }
}

void NewsStory::Render()
{
    CNode::Render();
}

void NewsStory::Init(std::string titleText, std::string descriptionText, char* link)
{
    CLabel* title = new CLabel();
    title->m_W = IwGxGetDisplayWidth();
    title->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    title->m_Font = g_pResources->getHeaderFont();
    title->SetText(titleText);
    
    CSprite* goldBanner = new CSprite();
    goldBanner->SetImage(g_pResources->getGoldBanner());
    goldBanner->m_X = (float)IwGxGetScreenWidth() / 2;
    goldBanner->m_Y = (float)IwGxGetScreenHeight() /24;
    goldBanner->m_W = goldBanner->GetImage()->GetWidth();
    goldBanner->m_H = goldBanner->GetImage()->GetHeight();
    goldBanner->m_AnchorX = 0.5;
    goldBanner->m_AnchorY = 0.5;
    // Fit background to screen size
    goldBanner->m_ScaleX = (float)IwGxGetScreenWidth() / goldBanner->GetImage()->GetWidth() / 1;
    goldBanner->m_ScaleY = (float)IwGxGetScreenHeight() / goldBanner->GetImage()->GetHeight() / 8;
    
    CLabel* description = new CLabel();
    description->m_W = IwGxGetDisplayWidth();
    description->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    description->m_Font = g_pResources->getContentFont();
    description->m_Color = CColor(0, 0, 0, 0xff);
    description->SetText(descriptionText);
    description->m_Y = IwGxGetDisplayHeight() / 8;
<<<<<<< HEAD
=======

>>>>>>> 8e01e814bbeb267d1b438018728d469089c12ac2

    readMore = new CLabel();
	readMore->m_Color = CColor(0, 0, 0, 0xff);
	readMore->SetFont(g_pResources->getBannerFontSmall());
	readMore->SetText("Read More");
    readMore->m_X = (float)IwGxGetScreenWidth() / 1.3;
    readMore->m_Y = (float)IwGxGetScreenHeight() / 2.5;
    readMore->m_AnchorX = 0.5;
    readMore->m_AnchorY = 0.5;
    
    this->link = link;
    
    //AddChild(description);
    AddChild(readMore);
    AddChild(goldBanner);
    AddChild(title);
    AddChild(description);
    
}

