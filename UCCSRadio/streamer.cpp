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

float buttonTop = 0;

Streamer::~Streamer()
{
}

void Streamer::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
    
    // Detect screen tap
    if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        g_pInput->Reset();
        if(playButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
        
        
        }
    }
}

void Streamer::Render()
{
    CNode::Render();
}

void Streamer::Init()
{
    
    //Game* game = (Game*)g_pSceneManager->Find("game");
    
    // Create menu background
    playButton = new CSprite();
    playButton->SetImage(g_pResources->getPlayButton());
    playButton->m_X = (float)IwGxGetScreenWidth() / 2;
    playButton->m_Y = (float)IwGxGetScreenHeight() / 1.2;
    buttonTop = (float)IwGxGetScreenHeight() / 1.2 - (playButton->GetImage()->GetHeight() / 10);
    playButton->m_W = playButton->GetImage()->GetWidth();
    playButton->m_H = playButton->GetImage()->GetHeight();
    playButton->m_AnchorX = 0.5;
    playButton->m_AnchorY = 0.5;
    // Fit background to screen size
    playButton->m_ScaleX = (float)IwGxGetScreenWidth() / playButton->GetImage()->GetWidth() / 5;
    playButton->m_ScaleY = (float)IwGxGetScreenHeight() / playButton->GetImage()->GetHeight() / 6;
    AddChild(playButton);
}

