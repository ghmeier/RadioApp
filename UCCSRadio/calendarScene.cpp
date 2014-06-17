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
#include "eventsScene.h"
#include "tinyxml.h"
#include "UCCSRadio.h"

CalendarScene::~CalendarScene()
{
	delete calFeed;
}

void CalendarScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
    
    Scene::Update(deltaTime, alphaMul);
	_STL::cout << "cal : " << xmlEventsDownload->GetStatus() << "\n";
	if (xmlCalendarDownload->GetStatus() == 4 && !hasFeed) {
		calFeed = new CIwRSS(this);
		TiXmlDocument doc("calendar.xml");
		calFeed->CalendarParseRSS("<feed>", doc, 1);
		hasFeed = true;
	}
	else if (hasFeed) {
		UpdateLabels();
	}
	else {
		/*CLabel * label = new CLabel();
		label->SetFont(g_pResources->getBannerFontLarge());
		label->SetText("Loading...");
		label->m_X = (float)IwGxGetScreenWidth() / 2;
		label->m_Y = (float)IwGxGetScreenHeight() / 2;
		label->m_AnchorX = 0.5;
		label->m_AnchorY = 0.5;
		labels.push_back(label);
		AddChild(label);
		_STL::cout << "cal : " << xmlCalendarDownload->GetStatus() << "\n";*/
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
    background->SetImage(g_pResources->getbackground());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight() * 6;
    AddChild(background);

}

