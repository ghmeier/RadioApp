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
#include "tinyxml.h"

EventsScene::~EventsScene()
{
 
}

void EventsScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
    
    Scene::Update(deltaTime, alphaMul);
    
	if (!hasFeed){
		//_STL::ifstream * file = new _STL::ifstream("events.xml");
		if (s3eFileCheckExists("events.xml")) {
			eventFeed = new CIwRSS(this);
			hasFeed = true;
			TiXmlDocument doc("events.xml");
			eventFeed->CalendarParseRSS("<feed>", doc, 2);
			
		}
		//delete file;
	}
	else
	{
		UpdateLabels();
	}
}

void EventsScene::Render()
{
    Scene::Render();
}

void EventsScene::Init()
{
    Scene::Init();

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
	eventFeed = new CIwRSS(this);
	//_STL::ifstream * file = new _STL::ifstream("events.xml");
	if (s3eFileCheckExists("events.xml")) {
		//file->close();
		TiXmlDocument doc("events.xml");
		eventFeed->CalendarParseRSS("<feed>", doc, 2);
		hasFeed = true;
	}
    
	//delete file;
    delete eventFeed;
}

