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

#include "eventsScene.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "newsScene.h"
#include "streamer.h"

EventsScene::~EventsScene()
{
    //delete calFeed;
}

void EventsScene::startGame(CTween* pTween)
{
    // Switch to game scene
    //NewsScene* news = (NewsScene*)g_pSceneManager->Find("newsscene");
    //g_pSceneManager->SwitchTo(news);
    
}

void EventsScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
    
    Scene::Update(deltaTime, alphaMul);
    
    // Detect screen tap
    if (m_IsInputActive && m_Manager->GetCurrent() == this && !g_pInput->m_Touched && g_pInput->m_PrevTouched)
    {
        //g_pInput->Reset();
        if(g_pInput->m_Y < buttonTop && g_pInput->m_Y > buttonBottom) {
            g_pInput->Reset();
            m_Tweener.Tween(0.2f,
                            DELAY, 0.25f,
                            EASING, Ease::powIn,
                            ONCOMPLETE, startGame,
                            END);
        }    }
}

void EventsScene::Render()
{
    Scene::Render();
}

void EventsScene::Init()
{
    Scene::Init();
    
    //Game* game = (Game*)g_pSceneManager->Find("game");
    
    // Create menu background
    CSprite* background = new CSprite();
    background->m_X = (float)IwGxGetScreenWidth() / 2;
    background->m_Y = (float)IwGxGetScreenHeight() / 2;
    background->SetImage(g_pResources->getEventsBG());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    AddChild(background);
    
    //adding scroll view
	//calFeed = new CIwRSS(this);
	printf("fetching...\n");
	//feed->FetchFeed("http://radio.uccs.edu/index.php/feed");
    //calFeed->ParseRSS("<rss>");
    printf("finished fetching\n");
	//feed->Update();
}

