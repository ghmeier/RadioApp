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
#include "s3eOSExec.h"


NewsStory::~NewsStory()
{
}

void NewsStory::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
    if (!g_pInput->m_Touched && g_pInput->m_PrevTouched && sceneSwitchComplete)
    {
        if(readMore->HitTest(g_pInput->m_X, g_pInput->m_Y) && g_pInput->m_Y > buttonTop) {
            g_pInput->Reset();
            const char* charLink = link.c_str();
            _STL::cout << "\n" << "Mayo" << charLink << "\n";
			if (s3eOSExecExecute(charLink,S3E_FALSE ) == S3E_RESULT_SUCCESS) {
				s3eOSExecExecute(charLink, S3E_FALSE);
			}
        }
    }
}

void NewsStory::Render()
{
    CNode::Render();
}

void NewsStory::Init(std::string titleText, std::string descriptionText, std::string link)
{
	//Replace curved quotes with straight
	const char *desc = descriptionText.c_str();
	char *newstr = new char[descriptionText.length() + 1];
	int off = 0;
	for (int i = 0; i < descriptionText.length() + 1; i++){
		if      (desc[i] == 0xe2 && desc[i + 1] == 0x80 && desc[i + 2] == 0x9c){ newstr[i - off] = '\"'; off += 2; i += 2; }//Left double
		else if (desc[i] == 0xe2 && desc[i + 1] == 0x80 && desc[i + 2] == 0x9d){ newstr[i - off] = '\"'; off += 2; i += 2; }//Right double
		else if (desc[i] == 0xe2 && desc[i + 1] == 0x80 && desc[i + 2] == 0x98){ newstr[i - off] = '\''; off += 2; i += 2; }//Left single
		else if (desc[i] == 0xe2 && desc[i + 1] == 0x80 && desc[i + 2] == 0x99){ newstr[i - off] = '\''; off += 2; i += 2; }//Right single
		else newstr[i - off] = desc[i];
	}
	descriptionText = std::string(newstr);
	
    CLabel* title = new CLabel();
    title->m_W = IwGxGetDisplayWidth();
    title->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    title->m_Font = g_pResources->getHeaderFont();
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
    description->m_Font = g_pResources->getContentFont();
    description->m_Color = CColor(0, 0, 0, 0xff);
    description->SetText(descriptionText);
    description->m_Y = IwGxGetDisplayHeight() / 8;

    readMore = new CLabel();
	readMore->m_Color = CColor(0, 0, 0, 0xff);
	readMore->SetFont(g_pResources->getBannerFontSmall());
	readMore->SetText("Read More");
    readMore->m_X = (float)IwGxGetScreenWidth() / 1.3;
    readMore->m_Y = (float)IwGxGetScreenHeight() / 2.5;
    readMore->m_AnchorX = 0.5;
    readMore->m_AnchorY = 0.5;
    
    this->link = link;
    
    //AddChild(description);
    AddChild(readMore);
    AddChild(goldBanner);
    AddChild(title);
    AddChild(description);
    
    
}

