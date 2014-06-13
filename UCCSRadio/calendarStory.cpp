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
#include "calendarScene.h"
#include "calendarStory.h"


CalendarStory::~CalendarStory()
{
    
}

void CalendarStory::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
    
    if (!g_pInput->m_Touched && g_pInput->m_PrevTouched && sceneSwitchComplete)
    {
        /*if(readMore->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            g_pInput->Reset();
            //s3eOSExecExecute(link, true);
        }
         */
    }
}

void CalendarStory::Render()
{
    CNode::Render();
}

void CalendarStory::Init(std::string titleText, std::string descriptionText, std::string link,  std::string starttime, std::string endtime)
{
    CLabel* title = new CLabel();
    title->m_W = IwGxGetDisplayWidth();
    title->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    title->m_Font = g_pResources->getFont();
    title->m_Color = CColor(0, 0, 0, 0xff);
    title->SetText(titleText);
    
    CLabel* description = new CLabel();
    description->m_W = IwGxGetDisplayWidth();
    description->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    description->m_Font = g_pResources->getFont7();
    description->m_Color = CColor(0, 0, 0, 0xff);
    description->SetText(descriptionText);
    description->m_Y = IwGxGetDisplayHeight() / 12;
    description->m_X += 20;
    
    CLabel* time = new CLabel();
    time->m_W = IwGxGetDisplayWidth();
    time->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
    time->m_Font = g_pResources->getFont();
    time->m_Color = CColor(100, 100, 100, 0xff);
    _STL::string dash = " - ";
    _STL::string fullTime = starttime + dash + endtime;
    time->SetText(fullTime);
    time->m_Y = IwGxGetDisplayHeight() / 12;
    time->m_X += -20;
    
    //readMore = new CSprite();
    //readMore->SetImage(g_pResources->getReadMore());
    //readMore->m_X = (float)IwGxGetScreenWidth() / 1.3;
    //readMore->m_Y = (float)IwGxGetScreenHeight() / 2.5;
    //readMore->m_W = readMore->GetImage()->GetWidth();
    //readMore->m_H = readMore->GetImage()->GetHeight();
    //readMore->m_AnchorX = 0.5;
    //readMore->m_AnchorY = 0.5;
    // Fit background to screen size
    //readMore->m_ScaleX = (float)IwGxGetScreenWidth() / readMore->GetImage()->GetWidth() / 4;
    //readMore->m_ScaleY = (float)IwGxGetScreenHeight() / readMore->GetImage()->GetHeight() / 10;
    
    this->link = link;
    
    //AddChild(readMore);
    AddChild(title);
    AddChild(description);
    AddChild(time);
    
}

