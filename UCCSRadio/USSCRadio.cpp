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

#include "Iw2D.h"
#include "Iw2DSceneGraph.h"
#include "IwTween.h"
#include "IwGx.h"
#include "IwGxPrint.h"
#include "input.h"
#include "scene.h"
#include "newsScene.h"
#include "calendarScene.h"
#include "eventsScene.h"
#include "resources.h"
#include "USSCRadio.h"
#include <sstream>
#include "streamer.h"
#include "src/HttpClient.h"
#include "s3e.h"
#include "IwDebug.h"
#include <IwHTTP.h>


using namespace Iw2DSceneGraph;
using namespace IwTween;
using namespace std;

// FRAME_TIME is the amount of time that a single frame should last in seconds
#define FRAME_TIME  (30.0f / 1000.0f)

// Global tweener is used by tweens that ned to be ranm outside of a scene
CTweenManager*  g_pTweener = 0;

int main()
{
	HttpClient::GlobalInit();

    // Initialise the 2D graphics system
    Iw2DInit();
    
    // Create resources
    g_pResources = new Resources();
    
    // Create global tween manager
    g_pTweener = new CTweenManager();
    
    // Set up input systems
    g_pInput = new Input();
    
    // Create scene manager
    g_pSceneManager = new SceneManager();
    

    // Init the news
    NewsScene* news_scene = new NewsScene();
    news_scene->SetName("newsscene");
    news_scene->Init();
    g_pSceneManager->Add(news_scene);
    
    // Init the calendar
    CalendarScene* cal_scene = new CalendarScene();
    cal_scene->SetName("calscene");
    cal_scene->Init();
    g_pSceneManager->Add(cal_scene);
    
    // Init the events list
    EventsScene* events_scene = new EventsScene();
    events_scene->SetName("eventsscene");
    events_scene->Init();
    g_pSceneManager->Add(events_scene);
    
    // Switch to main menu scene
    g_pSceneManager->SwitchTo(news_scene);
    

    Streamer* streamer = new Streamer();
    streamer->Init();

	HttpClient* globalHttpClient = new HttpClient(5, "HttpClient");
	Ptr<HttpDownload> xmlDownload = new HttpDownload("http://radio.uccs.edu/index.php/feed", "feed.xml");
	globalHttpClient->QueueRequest(xmlDownload);

    // Loop forever, until the user or the OS performs some action to quit the app
    while (!s3eDeviceCheckQuitRequest())
    {
		/*if (xmlDownload->GetStatus() == HttpRequest::DONE) {
			s3eDebugAssertShow(S3E_MESSAGE_CONTINUE, "YAY xml download");
		}
		else if (xmlDownload->GetStatus() == HttpRequest::ERROR){
			s3eDebugAssertShow(S3E_MESSAGE_CONTINUE, "both were downloaded!");
		}*/
        uint64 new_time = s3eTimerGetMs();
        
        // Update input system
        g_pInput->Update();
        
        // Update global tween manager
        g_pTweener->Update(FRAME_TIME);
        
        // Update scene manager
        g_pSceneManager->Update(FRAME_TIME);
        
		globalHttpClient->Update();
        streamer->Update();
        
        // Clear the drawing surface
        Iw2DSurfaceClear(0xff000000);
        
        
        // Render scene manager
        g_pSceneManager->Render();
        
        streamer->Render();
        
        // Show the drawing surface
        Iw2DSurfaceShow();
        
        // Lock frame rate
        int yield = (int)(FRAME_TIME /** 1000*/ - (s3eTimerGetMs() - new_time));
        if (yield < 0)
            yield = 0;
        // Yield to OS
        s3eDeviceYield(yield);
    }
    
    // Clean-up
    delete g_pInput;
    delete g_pSceneManager;
    delete g_pTweener;
    delete g_pResources;
	delete globalHttpClient;
	xmlDownload = nullptr;
    delete streamer;


    Iw2DTerminate();
  	HttpClient::GlobalCleanup();
    return 0;
}
