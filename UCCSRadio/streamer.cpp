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
#include "UCCSRadio.h"

#include "audioStreamer.h"

float buttonTop = 0;
float buttonBottom = 0;
int currentPage = 0;

float x = 0;
float y = 0;
int count = 0;
bool touched = false;
Streamer::~Streamer()
{
    stopStreaming();
}

void Streamer::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
    
    if (g_pInput->m_Touched) {
        if(!touched) {
            touched = true;
            x = g_pInput->m_X;
            y = g_pInput->m_Y;
        }
    }
    // Detect screen tap
    if (!g_pInput->m_Touched && g_pInput->m_PrevTouched && sceneSwitchComplete)
    {
        if(playButton->HitTest(g_pInput->m_X, g_pInput->m_Y) && g_pInput->m_X > x - 20 && g_pInput->m_X < x + 20 && g_pInput->m_Y > y - 20 && g_pInput->m_Y < y + 20) {
            g_pInput->Reset();
            playButton->m_X = IwGxGetScreenWidth() * 2.0;
            stopButton->m_X = IwGxGetScreenWidth() / 2.0;
			startStreaming();
			
        } else if(stopButton->HitTest(g_pInput->m_X, g_pInput->m_Y) && g_pInput->m_X > x - 20 && g_pInput->m_X < x + 20 && g_pInput->m_Y > y - 20 && g_pInput->m_Y < y + 20) {
            g_pInput->Reset();
            playButton->m_X = IwGxGetScreenWidth() / 2.0;
            stopButton->m_X = IwGxGetScreenWidth() * 2.0;
			pauseStreaming();
        }
        
		if(facebook->HitTest(g_pInput->m_X, g_pInput->m_Y) && g_pInput->m_X > x - 20 && g_pInput->m_X < x + 20 && g_pInput->m_Y > y - 20 && g_pInput->m_Y < y + 20) {
            g_pInput->Reset();
            s3eOSExecExecute("https://www.facebook.com/pages/UCCS-Radio/229529077104562", S3E_FALSE);
			
           
        } else if(twitter->HitTest(g_pInput->m_X, g_pInput->m_Y) && g_pInput->m_X > x - 20 && g_pInput->m_X < x + 20 && g_pInput->m_Y > y - 20 && g_pInput->m_Y < y + 20) {
            g_pInput->Reset();
            s3eOSExecExecute("https://twitter.com/uccsonlineradio", S3E_FALSE);
        }
        
		if ((labelLeft->HitTest(g_pInput->m_X, g_pInput->m_Y) && g_pInput->m_X > x - 20 && g_pInput->m_X < x + 20 && g_pInput->m_Y > y - 20 && g_pInput->m_Y < y + 20) || (g_pInput->m_X>g_pInput->prev_X + IwGxGetDeviceWidth() / 2)) {
			g_pInput->prev_X = g_pInput->m_X;
			sceneSwitchComplete = false;
            g_pInput->Reset();
            if(currentPage == 0) {
                CalendarScene* cal = (CalendarScene*)g_pSceneManager->Find("calscene");
                g_pSceneManager->SwitchTo(cal, 1);
                labelMain->SetText("Calendar");
                labelLeft->SetText("Events");
                labelRight->SetText("News");
                currentPage = 1;
                
            } else if(currentPage == 1) {
                EventsScene* events = (EventsScene*)g_pSceneManager->Find("eventsscene");
                g_pSceneManager->SwitchTo(events, 1);
                labelMain->SetText("Events");
                labelLeft->SetText("News");
                labelRight->SetText("Cal.");
                currentPage = 2;
                
            } else if(currentPage == 2) {
                NewsScene* news = (NewsScene*)g_pSceneManager->Find("newsscene");
                g_pSceneManager->SwitchTo(news, 1);
                labelMain->SetText("News");
                labelLeft->SetText("Cal.");
                labelRight->SetText("Events");
                currentPage = 0;
            }
            
		}
		else if ( 
			(labelRight->HitTest(g_pInput->m_X, g_pInput->m_Y) && 
			g_pInput->m_X > x - 20 && g_pInput->m_X < x + 20 && g_pInput->m_Y > y - 20
			&&
			g_pInput->m_Y < y + 20)
			|| 
			((g_pInput->m_X) < (g_pInput->prev_X - (int)IwGxGetDeviceWidth() / 2))
			) {
			g_pInput->prev_X = g_pInput->m_X;
			sceneSwitchComplete = false;
            g_pInput->Reset();
            if(currentPage == 0) {
                EventsScene* events = (EventsScene*)g_pSceneManager->Find("eventsscene");
                g_pSceneManager->SwitchTo(events, 0);
                labelMain->SetText("Events");
                labelLeft->SetText("News");
                labelRight->SetText("Cal.");
                currentPage = 2;
                
            } else if(currentPage == 1) {
                NewsScene* news = (NewsScene*)g_pSceneManager->Find("newsscene");
                g_pSceneManager->SwitchTo(news, 0);
                labelMain->SetText("News");
                labelLeft->SetText("Cal.");
                labelRight->SetText("Events");
                currentPage = 0;
                
            } else if(currentPage == 2) {
                CalendarScene* cal = (CalendarScene*)g_pSceneManager->Find("calscene");
                g_pSceneManager->SwitchTo(cal, 0);
                labelMain->SetText("Cal.");
                labelLeft->SetText("Events");
                labelRight->SetText("News");
                currentPage = 1;
                
            }
		}
		g_pInput->Reset();
        x = 0;
        y = 0;
        touched = false;
	}
    if(g_pInput->m_PrevTouched) {
        x = 0;
        y = 0;
        touched = false;
    }
}

void Streamer::Render()
{
    CNode::Render();
}

void Streamer::Init()
{
    
    //Game* game = (Game*)g_pSceneManager->Find("game");
	initAudio("128.198.85.100", 8000);
	s3eDeviceRegister(S3E_DEVICE_EXIT, &exitCB, 0);
    
    facebook = new CSprite();
    facebook->SetImage(g_pResources->getFacebook());
    facebook->m_X = (float)IwGxGetScreenWidth() / 1.4;
    facebook->m_Y = (float)IwGxGetScreenHeight() / 16;
    facebook->m_W = facebook->GetImage()->GetWidth();
    facebook->m_H = facebook->GetImage()->GetHeight();
    facebook->m_AnchorX = 0.5;
    facebook->m_AnchorY = 0.5;
    facebook->m_ScaleX = (float)IwGxGetScreenWidth() / facebook->GetImage()->GetWidth() / 8;
    facebook->m_ScaleY = (float)IwGxGetScreenHeight() / facebook->GetImage()->GetHeight() / 12;
    
    twitter = new CSprite();
    twitter->SetImage(g_pResources->getTwitter());
    twitter->m_X = (float)IwGxGetScreenWidth() / 1.1;
    twitter->m_Y = (float)IwGxGetScreenHeight() / 16;
    twitter->m_W = twitter->GetImage()->GetWidth();
    twitter->m_H = twitter->GetImage()->GetHeight();
    twitter->m_AnchorX = 0.5;
    twitter->m_AnchorY = 0.5;
    twitter->m_ScaleX = (float)IwGxGetScreenWidth() / twitter->GetImage()->GetWidth() / 8;
    twitter->m_ScaleY = (float)IwGxGetScreenHeight() / twitter->GetImage()->GetHeight() / 12;

    // Create menu background
    header = new CSprite();
    header->SetImage(g_pResources->getHeader());
    header->m_X = (float)IwGxGetScreenWidth() / 3;
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
    
    // Create menu background
    playWrapper = new CSprite();
    playWrapper->SetImage(g_pResources->getPlayWrapper());
    playWrapper->m_X = (float)IwGxGetScreenWidth() / 2;
    playWrapper->m_Y = (float)IwGxGetScreenHeight() / 1.09;
    playWrapper->m_W = playWrapper->GetImage()->GetWidth();
    playWrapper->m_H = playWrapper->GetImage()->GetHeight();
    playWrapper->m_AnchorX = 0.5;
    playWrapper->m_AnchorY = 0.5;
    //playWrapper->m_Alpha = 0.9;
    // Fit background to screen size
    playWrapper->m_ScaleX = (float)IwGxGetScreenWidth() / playWrapper->GetImage()->GetWidth() / 1;
    playWrapper->m_ScaleY = (float)IwGxGetScreenHeight() / playWrapper->GetImage()->GetHeight() / 6;

    playButton = new CSprite();
    playButton->SetImage(g_pResources->getPlayButton());
    playButton->m_X = (float)IwGxGetScreenWidth() / 2;
    playButton->m_Y = (float)IwGxGetScreenHeight() / 1.13;
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
    stopButton->m_Y = (float)IwGxGetScreenHeight() / 1.13;
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
    
    buttonTop = IwGxGetScreenHeight() / 4;
    
    labelLeft = new CLabel();
	labelLeft->m_Font = g_pResources->getBannerFontSmall();
	labelLeft->m_Text = "Cal.";
    labelLeft->m_Y = IwGxGetDisplayHeight() / 6.5;
    labelLeft->m_W = IwGxGetDisplayWidth() / 2;
    labelLeft->m_ScaleX = 1.0;
    labelLeft->m_AlignHor = IW_2D_FONT_ALIGN_LEFT;
    labelLeft->m_X += 10;
    labelLeft->m_Color = CColor(114, 114, 114, 0xff);
    
    labelRight = new CLabel();
	labelRight->m_Font = g_pResources->getBannerFontSmall();
	labelRight->m_Text = "Events";
    labelRight->m_Y = IwGxGetDisplayHeight() / 6.5;
    labelRight->m_W = IwGxGetDisplayWidth() / 2;
    labelRight->m_AlignHor = IW_2D_FONT_ALIGN_RIGHT;
    labelRight->m_X += (IwGxGetDisplayWidth() / 2.0) -10;
    labelRight->m_Color = CColor(114, 114, 114, 0xff);
    
    labelMain = new CLabel();
	labelMain->m_Font = g_pResources->getBannerFontLarge();
	labelMain->m_Text = "News";
    labelMain->m_Y = IwGxGetDisplayHeight() / 7.5;
    labelMain->m_W = IwGxGetDisplayWidth();
    labelMain->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
    
    AddChild(banner);
    AddChild(whiteBanner);
    AddChild(header);
    AddChild(labelRight);
    AddChild(labelLeft);
    AddChild(playWrapper);
    AddChild(playButton);
    AddChild(stopButton);
    AddChild(labelMain);
    AddChild(facebook);
    AddChild(twitter);
    
    stopButton->m_X = IwGxGetScreenWidth() * 2.0;
    currentPage = 0;
    
    
}

