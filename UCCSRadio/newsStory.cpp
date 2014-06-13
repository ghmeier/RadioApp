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

void NewsStory::Init(std::string titleText)
{
    CLabel* title = new CLabel();
    title->m_W = IwGxGetDisplayWidth();
    title->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    title->m_Font = g_pResources->getFont();
    title->SetText(titleText);
    
    AddChild(title);
    
}

