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

#include "calendarScene.h"
#include "IwGx.h"
#include "input.h"
#include "resources.h"
#include "eventsScene.h"
#include "streamer.h"

CalendarScene::~CalendarScene()
{
}

void CalendarScene::startGame(CTween* pTween)
{
    // Switch to game scene
    //EventsScene* events = (EventsScene*)g_pSceneManager->Find("eventsscene");
    //g_pSceneManager->SwitchTo(events);
    
}

void CalendarScene::Update(float deltaTime, float alphaMul)
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
        }
		
    }
	if (m_IsInputActive && m_Manager->GetCurrent() == this && g_pInput->m_Touched) 
	{
		label->m_Y += (g_pInput->m_Y - g_pInput->prev_Y);
	}
}

void CalendarScene::Render()
{
    Scene::Render();
}

void CalendarScene::Init()
{
    Scene::Init();
  
    // Create menu background
    CSprite* background = new CSprite();
    background->m_X = (float)IwGxGetScreenWidth() / 2;
    background->m_Y = (float)IwGxGetScreenHeight() / 2;
    background->SetImage(g_pResources->getCalendarBG());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight() * 6;

	label = new CLabel();
	label->SetFont(g_pResources->getFont20());
	label->SetText("It is a period of civil war. Rebel spaceships, striking	from a hidden base, have won their first victory against the evil Galactic Empire.");
	label->m_W = IwGxGetScreenWidth();
	label->m_Y = (float)IwGxGetScreenHeight() / 2;

	AddChild(background);
	AddChild(label);
	
}

