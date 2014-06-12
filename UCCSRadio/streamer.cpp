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

float buttonTop = 0;
float buttonBottom = 0;
int currentPage = 0;

Streamer::~Streamer()
{
}

void Streamer::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
    
    // Detect screen tap
    if (!g_pInput->m_Touched && g_pInput->m_PrevTouched && sceneSwitchComplete)
    {
        if(playButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            g_pInput->Reset();
            playButton->m_X = IwGxGetScreenWidth() * 2.0;
            stopButton->m_X = IwGxGetScreenWidth() / 2.0;
        
        } else if(stopButton->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            g_pInput->Reset();
            playButton->m_X = IwGxGetScreenWidth() / 2.0;
            stopButton->m_X = IwGxGetScreenWidth() * 2.0;
            
        }
        
		if (labelLeft->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            sceneSwitchComplete = false;
            g_pInput->Reset();
            if(currentPage == 0) {
                CalendarScene* cal = (CalendarScene*)g_pSceneManager->Find("calscene");
                g_pSceneManager->SwitchTo(cal, 1);
                //banner->SetImage(g_pResources->getCalendarBanner());
                labelMain->SetText("Calendar");
                labelLeft->SetText("Events");
                labelRight->SetText("News");
                //labelRight->m_ScaleX = 1.0;
                currentPage = 1;
                
            } else if(currentPage == 1) {
                EventsScene* events = (EventsScene*)g_pSceneManager->Find("eventsscene");
                g_pSceneManager->SwitchTo(events, 1);
                //banner->SetImage(g_pResources->getEventsBanner());
                labelMain->SetText("Events");
                labelLeft->SetText("News");
                labelRight->SetText("Calendar");
                //labelRight->m_ScaleX = 1.0;
                currentPage = 2;
                
            } else if(currentPage == 2) {
                NewsScene* news = (NewsScene*)g_pSceneManager->Find("newsscene");
                g_pSceneManager->SwitchTo(news, 1);
                //banner->SetImage(g_pResources->getNewsBanner());
                labelMain->SetText("News");
                labelLeft->SetText("Calendar");
                labelRight->SetText("Events");
                //labelRight->m_ScaleX = 1.0;
                currentPage = 0;
            }
            
		}
		else if (labelRight->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            sceneSwitchComplete = false;
            g_pInput->Reset();
            if(currentPage == 0) {
                EventsScene* events = (EventsScene*)g_pSceneManager->Find("eventsscene");
                g_pSceneManager->SwitchTo(events, 0);
                //banner->SetImage(g_pResources->getEventsBanner());
                labelMain->SetText("Events");
                labelLeft->SetText("News");
                labelRight->SetText("Calendar");
                //labelRight->m_ScaleX = 1.0;
                currentPage = 2;
                
            } else if(currentPage == 1) {
                NewsScene* news = (NewsScene*)g_pSceneManager->Find("newsscene");
                g_pSceneManager->SwitchTo(news, 0);
                //banner->SetImage(g_pResources->getNewsBanner());
                labelMain->SetText("News");
                labelLeft->SetText("Calendar");
                labelRight->SetText("Events");
                //labelRight->m_ScaleX = 1.0;
                currentPage = 0;
                
            } else if(currentPage == 2) {
                CalendarScene* cal = (CalendarScene*)g_pSceneManager->Find("calscene");
                g_pSceneManager->SwitchTo(cal, 0);
                //banner->SetImage(g_pResources->getCalendarBanner());
                labelMain->SetText("Calendar");
                labelLeft->SetText("Events");
                labelRight->SetText("News");
                //labelRight->m_ScaleX = 1.0;
                currentPage = 1;
                
            }
		}
		g_pInput->Reset();
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
    header = new CSprite();
    header->SetImage(g_pResources->getHeader());
    header->m_X = (float)IwGxGetScreenWidth() / 2;
    header->m_Y = (float)IwGxGetScreenHeight() / 17;
    header->m_W = header->GetImage()->GetWidth();
    header->m_H = header->GetImage()->GetHeight();
    header->m_AnchorX = 0.5;
    header->m_AnchorY = 0.5;
    // Fit background to screen size
    header->m_ScaleX = (float)IwGxGetScreenWidth() / header->GetImage()->GetWidth() / 1.5;
    header->m_ScaleY = (float)IwGxGetScreenHeight() / header->GetImage()->GetHeight() / 5;
    
    // Create menu background
    CSprite* whiteBanner = new CSprite();
    whiteBanner->SetImage(g_pResources->getWhiteBanner());
    whiteBanner->m_X = (float)IwGxGetScreenWidth() / 2;
    whiteBanner->m_Y = (float)IwGxGetScreenHeight() / 17;
    whiteBanner->m_W = whiteBanner->GetImage()->GetWidth();
    whiteBanner->m_H = whiteBanner->GetImage()->GetHeight();
    whiteBanner->m_AnchorX = 0.5;
    whiteBanner->m_AnchorY = 0.5;
    // Fit background to screen size
    whiteBanner->m_ScaleX = (float)IwGxGetScreenWidth() / whiteBanner->GetImage()->GetWidth() / 1;
    whiteBanner->m_ScaleY = (float)IwGxGetScreenHeight() / whiteBanner->GetImage()->GetHeight() / 5;
    
    //buttonBottom = ((float)IwGxGetScreenHeight() / 17) + (header->GetImage()->GetHeight() / 1.4);
    
    // Create menu background
    playWrapper = new CSprite();
    playWrapper->SetImage(g_pResources->getPlayWrapper());
    playWrapper->m_X = (float)IwGxGetScreenWidth() / 2;
    playWrapper->m_Y = (float)IwGxGetScreenHeight() / 1.1;
    playWrapper->m_W = playWrapper->GetImage()->GetWidth();
    playWrapper->m_H = playWrapper->GetImage()->GetHeight();
    playWrapper->m_AnchorX = 0.5;
    playWrapper->m_AnchorY = 0.5;
    // Fit background to screen size
    playWrapper->m_ScaleX = (float)IwGxGetScreenWidth() / playWrapper->GetImage()->GetWidth() / 1;
    playWrapper->m_ScaleY = (float)IwGxGetScreenHeight() / playWrapper->GetImage()->GetHeight() / 5;

    playButton = new CSprite();
    playButton->SetImage(g_pResources->getPlayButton());
    playButton->m_X = (float)IwGxGetScreenWidth() / 2;
    playButton->m_Y = (float)IwGxGetScreenHeight() / 1.14;
    //buttonTop = (float)IwGxGetScreenHeight() / 1.14 - (playButton->GetImage()->GetHeight() / 8);
    playButton->m_W = playButton->GetImage()->GetWidth();
    playButton->m_H = playButton->GetImage()->GetHeight();
    playButton->m_AnchorX = 0.5;
    playButton->m_AnchorY = 0.5;
    // Fit background to screen size
    playButton->m_ScaleX = (float)IwGxGetScreenWidth() / playButton->GetImage()->GetWidth() / 3.2;
    playButton->m_ScaleY = (float)IwGxGetScreenHeight() / playButton->GetImage()->GetHeight() / 4.5;
    
    //buttonTop = ((float)IwGxGetScreenHeight() / 1.14) - (playButton->GetImage()->GetHeight() / 3.7);
    
    stopButton = new CSprite();
    stopButton->SetImage(g_pResources->getStopButton());
    stopButton->m_X = (float)IwGxGetScreenWidth() / 2;
    stopButton->m_Y = (float)IwGxGetScreenHeight() / 1.14;
    //buttonTop = (float)IwGxGetScreenHeight() / 1.14 - (playButton->GetImage()->GetHeight() / 8);
    stopButton->m_W = stopButton->GetImage()->GetWidth();
    stopButton->m_H = stopButton->GetImage()->GetHeight();
    stopButton->m_AnchorX = 0.5;
    stopButton->m_AnchorY = 0.5;
    // Fit background to screen size
    stopButton->m_ScaleX = (float)IwGxGetScreenWidth() / stopButton->GetImage()->GetWidth() / 3.2;
    stopButton->m_ScaleY = (float)IwGxGetScreenHeight() / stopButton->GetImage()->GetHeight() / 4.5;
    
    banner = new CSprite();
    banner->SetImage(g_pResources->getGreyBanner());
    banner->m_X = (float)IwGxGetScreenWidth() / 2;
    banner->m_Y = (float)IwGxGetScreenHeight() /6;
    banner->m_W = banner->GetImage()->GetWidth();
    banner->m_H = banner->GetImage()->GetHeight();
    banner->m_AnchorX = 0.5;
    banner->m_AnchorY = 0.5;
    // Fit background to screen size
    banner->m_ScaleX = (float)IwGxGetScreenWidth() / banner->GetImage()->GetWidth() / 1;
    banner->m_ScaleY = (float)IwGxGetScreenHeight() / banner->GetImage()->GetHeight() / 8;
    
    /*sideBannerOne = new CSprite();
    sideBannerOne->SetImage(g_pResources->getCalendarSideBanner());
    sideBannerOne->m_X = (float)IwGxGetScreenWidth() / 8;
    sideBannerOne->m_Y = (float)IwGxGetScreenHeight() / 6;
    sideBannerOne->m_W = sideBannerOne->GetImage()->GetWidth();
    sideBannerOne->m_H = sideBannerOne->GetImage()->GetHeight();
    sideBannerOne->m_AnchorX = 0.5;
    sideBannerOne->m_AnchorY = 0.5;
    // Fit background to screen size
    sideBannerOne->m_ScaleX = (float)IwGxGetScreenWidth() / sideBannerOne->GetImage()->GetWidth() / 3;
    sideBannerOne->m_ScaleY = (float)IwGxGetScreenHeight() / sideBannerOne->GetImage()->GetHeight() / 8;
    
    sideBannerTwo = new CSprite();
    sideBannerTwo->SetImage(g_pResources->getEventsSideBanner());
    sideBannerTwo->m_X = (float)IwGxGetScreenWidth() / 1.18;
    sideBannerTwo->m_Y = (float)IwGxGetScreenHeight() / 6;
    sideBannerTwo->m_W = sideBannerTwo->GetImage()->GetWidth();
    sideBannerTwo->m_H = sideBannerTwo->GetImage()->GetHeight();
    sideBannerTwo->m_AnchorX = 0.5;
    sideBannerTwo->m_AnchorY = 0.5;
    // Fit background to screen size
    sideBannerTwo->m_ScaleX = (float)IwGxGetScreenWidth() / sideBannerTwo->GetImage()->GetWidth() / 3;
    sideBannerTwo->m_ScaleY = (float)IwGxGetScreenHeight() / sideBannerTwo->GetImage()->GetHeight() / 10;
    */
    
    labelLeft = new CLabel();
	labelLeft->m_Font = g_pResources->getFont();
	labelLeft->m_Text = "Calendar";
    labelLeft->m_Y = IwGxGetDisplayHeight() / 6.5;
    labelLeft->m_W = IwGxGetDisplayWidth() / 2;
    labelLeft->m_ScaleX = 1.0;
    labelLeft->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    labelLeft->m_X += 10;
    
    labelRight = new CLabel();
	labelRight->m_Font = g_pResources->getFont();
	labelRight->m_Text = "Events";
    labelRight->m_Y = IwGxGetDisplayHeight() / 6.5;
    labelRight->m_W = IwGxGetDisplayWidth() / 2;
    labelRight->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
    labelRight->m_X += (IwGxGetDisplayWidth() / 2.0) -10;
    
    labelMain = new CLabel();
	labelMain->m_Font = g_pResources->getFont20();
	labelMain->m_Text = "Events";
    labelMain->m_Y = IwGxGetDisplayHeight() / 7.5;
    labelMain->m_W = IwGxGetDisplayWidth();
    labelMain->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    
    AddChild(playWrapper);
    AddChild(playButton);
    AddChild(stopButton);
    AddChild(banner);
    //AddChild(sideBannerTwo);
    //AddChild(sideBannerOne);
    AddChild(whiteBanner);
    AddChild(header);
    AddChild(labelRight);
    AddChild(labelLeft);
    AddChild(labelMain);
    
    stopButton->m_X = IwGxGetScreenWidth() * 2.0;
    currentPage = 0;
    
    
}

