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

#include "newsScene.h"
#include "input.h"
#include "resources.h"
#include "calendarScene.h"
#include "streamer.h"
#include "IwGx.h"
#include <tinyxml.h>
#include "UCCSRadio.h"
#include "src/HttpClient.h"
#include "s3e.h"
#include "IwDebug.h"
#include <IwHTTP.h>



NewsScene::~NewsScene()
{
	//delete feed;
}

void NewsScene::startGame(CTween* pTween)
{
    //CalendarScene* cal = (CalendarScene*)g_pSceneManager->Find("calscene");
    //g_pSceneManager->SwitchTo(cal);
    
}

void NewsScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
    
    Scene::Update(deltaTime, alphaMul);
	if (!hasFeed){
		try{
			
			feed = new CIwRSS(this);
			feed->ParseRSS("<rss>");
			hasFeed = true;
		}catch(int e){
			hasFeed = false;
		}
	}
	else
	{
		UpdateLabels();
	}
}

void NewsScene::Render()
{
    Scene::Render();
}

void NewsScene::Init()
{
    Scene::Init();

    // Create menu background
    CSprite* background = new CSprite();
    background->m_X = (float)IwGxGetScreenWidth() / 2;
    background->m_Y = (float)IwGxGetScreenHeight() / 2;
    background->SetImage(g_pResources->getNewsBG());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    AddChild(background);

	feed = new CIwRSS(this);
	try {
		feed->ParseRSS("<rss>");
		hasFeed = true;
	}
	catch (int e){
		printf("sooo yeah\n");
		hasFeed = false;
	}

    delete feed;
    
    
    
}
