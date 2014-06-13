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

std::string link = "";

NewsStory::~NewsStory()
{
}

void NewsStory::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
      
    
}

void NewsStory::Render()
{
    CNode::Render();
}

void NewsStory::Init(std::string titleText, std::string descriptionText, std::string link)
{
    CLabel* title = new CLabel();
    title->m_W = IwGxGetDisplayWidth();
    title->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    title->m_Font = g_pResources->getFont();
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
    description->m_Font = g_pResources->getFont7();
    description->m_Color = CColor(0, 0, 0, 0xff);
    description->SetText(descriptionText);
    description->m_Y = IwGxGetDisplayHeight() / 8;
    
    this->link = link;
    
    //AddChild(description);
    AddChild(goldBanner);
    AddChild(title);
    AddChild(description);
    
}

