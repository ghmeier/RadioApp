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

Streamer::~Streamer()
{
}

void Streamer::Update(float deltaTime, float alphaMul)
{
    CNode::Update(deltaTime, alphaMul);
    
    // Detect screen tap
    if (!g_pInput->m_Touched && g_pInput->m_PrevTouched)
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
        
        if(newsBanner->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            g_pInput->Reset();
            CalendarScene* cal = (CalendarScene*)g_pSceneManager->Find("calscene");
            g_pSceneManager->SwitchTo(cal);
            newsBanner->m_X = IwGxGetScreenWidth() * 2;
            calBanner->m_X = IwGxGetScreenWidth() / 2;
            
        } else if(calBanner->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            g_pInput->Reset();
            EventsScene* events = (EventsScene*)g_pSceneManager->Find("eventsscene");
            g_pSceneManager->SwitchTo(events);
            calBanner->m_X = IwGxGetScreenWidth() * 2;
            eventsBanner->m_X = IwGxGetScreenWidth() / 2;
            
        } else if(eventsBanner->HitTest(g_pInput->m_X, g_pInput->m_Y)) {
            g_pInput->Reset();
            NewsScene* news = (NewsScene*)g_pSceneManager->Find("newsscene");
            g_pSceneManager->SwitchTo(news);
            eventsBanner->m_X = IwGxGetScreenWidth() * 2;
            newsBanner->m_X = IwGxGetScreenWidth() / 2;
            
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
    header = new CSprite();
    header->SetImage(g_pResources->getHeader());
    header->m_X = (float)IwGxGetScreenWidth() / 2;
    header->m_Y = (float)IwGxGetScreenHeight() / 17;
    header->m_W = header->GetImage()->GetWidth();
    header->m_H = header->GetImage()->GetHeight();
    header->m_AnchorX = 0.5;
    header->m_AnchorY = 0.5;
    // Fit background to screen size
    header->m_ScaleX = (float)IwGxGetScreenWidth() / header->GetImage()->GetWidth() / 1;
    header->m_ScaleY = (float)IwGxGetScreenHeight() / header->GetImage()->GetHeight() / 8;
    
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
    
    newsBanner = new CSprite();
    newsBanner->SetImage(g_pResources->getNewsBanner());
    newsBanner->m_X = (float)IwGxGetScreenWidth() / 2;
    newsBanner->m_Y = (float)IwGxGetScreenHeight() / 6;
    newsBanner->m_W = newsBanner->GetImage()->GetWidth();
    newsBanner->m_H = newsBanner->GetImage()->GetHeight();
    newsBanner->m_AnchorX = 0.5;
    newsBanner->m_AnchorY = 0.5;
    // Fit background to screen size
    newsBanner->m_ScaleX = (float)IwGxGetScreenWidth() / newsBanner->GetImage()->GetWidth() / 1;
    newsBanner->m_ScaleY = (float)IwGxGetScreenHeight() / newsBanner->GetImage()->GetHeight() / 10;
    
    calBanner = new CSprite();
    calBanner->SetImage(g_pResources->getCalendarBanner());
    calBanner->m_X = (float)IwGxGetScreenWidth() / 2;
    calBanner->m_Y = (float)IwGxGetScreenHeight() / 6;
    calBanner->m_W = calBanner->GetImage()->GetWidth();
    calBanner->m_H = calBanner->GetImage()->GetHeight();
    calBanner->m_AnchorX = 0.5;
    calBanner->m_AnchorY = 0.5;
    // Fit background to screen size
    calBanner->m_ScaleX = (float)IwGxGetScreenWidth() / calBanner->GetImage()->GetWidth() / 1;
    calBanner->m_ScaleY = (float)IwGxGetScreenHeight() / calBanner->GetImage()->GetHeight() / 10;
    
    eventsBanner = new CSprite();
    eventsBanner->SetImage(g_pResources->getEventsBanner());
    eventsBanner->m_X = (float)IwGxGetScreenWidth() / 2;
    eventsBanner->m_Y = (float)IwGxGetScreenHeight() / 6;
    eventsBanner->m_W = eventsBanner->GetImage()->GetWidth();
    eventsBanner->m_H = eventsBanner->GetImage()->GetHeight();
    eventsBanner->m_AnchorX = 0.5;
    eventsBanner->m_AnchorY = 0.5;
    // Fit background to screen size
    eventsBanner->m_ScaleX = (float)IwGxGetScreenWidth() / eventsBanner->GetImage()->GetWidth() / 1;
    eventsBanner->m_ScaleY = (float)IwGxGetScreenHeight() / eventsBanner->GetImage()->GetHeight() / 10;
    
    AddChild(header);
    AddChild(playWrapper);
    AddChild(playButton);
    AddChild(stopButton);
    AddChild(newsBanner);
    AddChild(calBanner);
    AddChild(eventsBanner);
    
    stopButton->m_X = IwGxGetScreenWidth() * 2.0;
    calBanner->m_X = IwGxGetScreenWidth() * 2.0;
    eventsBanner->m_X = IwGxGetScreenWidth() * 2.0;
    
}

