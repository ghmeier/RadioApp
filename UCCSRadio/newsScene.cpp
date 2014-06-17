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
	delete feed;
}

void NewsScene::Update(float deltaTime, float alphaMul)
{
    if (!m_IsActive)
        return;
	_STL::cout << "news : " << xmlDownload->GetStatus() << "\n";
    Scene::Update(deltaTime, alphaMul);
	if (xmlDownload->GetStatus() == 4 && !hasFeed) {
		feed = new CIwRSS(this);		
		feed->ParseRSS("<rss>");
		hasFeed = true;
		//delete feed;
	}
	else if (hasFeed) {
		_STL::cout << "news : " << xmlDownload->GetStatus() << "\n";
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
		_STL::cout << "Load news : " << xmlDownload->GetStatus() << "\n";*/
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
    background->SetImage(g_pResources->getbackground());
    background->m_W = background->GetImage()->GetWidth();
    background->m_H = background->GetImage()->GetHeight();
    background->m_AnchorX = 0.5;
    background->m_AnchorY = 0.5;
    // Fit background to screen size
    background->m_ScaleX = (float)IwGxGetScreenWidth() / background->GetImage()->GetWidth();
    background->m_ScaleY = (float)IwGxGetScreenHeight() / background->GetImage()->GetHeight();
    AddChild(background);
}
