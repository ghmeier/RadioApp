/*
 * This file is part of the Marmalade SDK Code Samples.
 *
 * (C) 2001-2012 Marmalade. All Rights Reserved.
 *
 * This source code is intended only as a supplement to the Marmalade SDK.
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 */

// Includes
#include "IwRSS.h"
#include "IwUIAnimManager.h"
#include <string>
#include "s3eMemory.h"
#include <stdio.h>
#include "tinyxml.h"
#include "../UCCSRadio.h"
#include "../resources.h"
#include "s3e.h"
#include <string>
#include "../newsStory.h"
#include "../calendarStory.h"
#include <iostream>
#include <sstream>

// Globals
CIwRSS * g_IwRSS = 0;

// Declarations

//-----------------------------------------------------------------------------

void CIwRSS::Update()
{
    // Don't process requests whilst animating to avoid jerking
    //if (!IwGetUIAnimManager()->IsAnimPlaying())
    //{
        m_HTTPQueue.Update();
    //}
}

void CIwRSS::HTTPHandler(void* pArgument, const char* pURL,
    const char* pResult, int32 resultLen)
{
    if (pArgument && pResult && resultLen > 0)
    {
        CIwRSS* pRSS = ((CIwRSS*)pArgument);
        IwAssert(UI, pRSS == g_IwRSS);
        
		// Handle Data fetched by HTTP
        pRSS->HandleResult(pURL, pResult, resultLen);
    }
    else
    {
        IwAssertMsg(UI, false, ("Error fetching url: %s", pURL));
    }
}

void CIwRSS::HandleResult(const char* url, const char *data, int32 dataLen)
{
    const CFeedItem* pFeedItem = GetFeedItemByURL(url);
    if (!pFeedItem)
    {
        return;
    }

    const char* pXML = "<?xml";
    const char* pRSS = "<rss";
    if (!strnicmp(data, pXML, strlen(pXML)) ||
        !strnicmp(data, pRSS, strlen(pRSS)))
    {
        ParseRSS(data);
    }
    else
    {
        //THIS IS WHERE YOU ADD RSS Visaul STUFF
    }

    m_Progress = IW_FIXED_DIV(m_FeedItems.find((CFeedItem*)pFeedItem)+1, m_FeedItems.size());
    m_Progress = MAX(0, MIN(m_Progress, IW_GEOM_ONE));
}

const CIwRSS::CFeedItem* CIwRSS::GetFeedItemByURL(const char* url) const
{
    const CFeedItem* pFeedItem = NULL;
    for (int i=0; i<(int)m_FeedItems.size(); ++i)
    {
        const CFeedItem* pTest = m_FeedItems[i];
        if (!stricmp(url, pTest->GetURL()))
        {
            IwAssertMsg(UI, !pFeedItem, ("Multiple feeds with same url"));
            pFeedItem = pTest;
        }
    }

    IwAssertMsg(UI, pFeedItem, ("Feed item not found for URL"));
    return pFeedItem;
}

void CIwRSS::ParseRSS(const char * data)
{
    //Parse the RSS data
    TiXmlDocument doc( "newsFeed.xml" );
    bool loadOkay = doc.LoadFile();
    if (loadOkay) {
        printf("\nWe all good \n");
    } else {
        printf("\nWe not good \n");
    }
    doc.Parse(data, 0, TIXML_ENCODING_UNKNOWN );
    TiXmlElement * node = doc.RootElement();
    TiXmlNode * channel;
    TiXmlNode * element;
    TiXmlNode * title;
    TiXmlNode * desc;
    TiXmlNode * url;

    if (node != 0 && node->ToElement())
    {
        //Find channel
        channel = node->FirstChild("channel");
        if (channel != 0 && channel->ToElement())
        {
            //Loop through feed items
            for (element = channel->FirstChild("item");
                 element;
                 element = element->NextSibling("item") )
            {
                if (!element->FirstChild("title") || !(title = element->FirstChild("title")->FirstChild()))
                    continue;
                //Found title
                std::string titlestr = title->Value();
                std::string description = "";
                std::string image = "";
                char* link = "";

                if (element->FirstChild("description") && (desc = element->FirstChild("description")->FirstChild()))
                {
                    description = desc->Value();

                    //Description contains HTML data
                    if (description[0] == '<')
                    {
                        TiXmlDocument desc( "description.html" );
                        desc.Parse( description.c_str(), 0, TIXML_ENCODING_UTF8);

                        TiXmlElement * head = desc.RootElement();
                        if (head != 0 && head->ToElement())
                        {
                            std::string::size_type start, end;
                            {
                                start = description.find("<img src=\"");
                                if (start != std::string::npos)
                                {
                                    start += 10;
                                    end = description.find('"', start + 1);
                                    if (end != std::string::npos)
                                    {
                                        image = description.substr(start, end - start);
                                       // IwTrace(UI, ("Image found %s", image.c_str()));
                                    }
                                }
                            }

                            start = 0;
                            while (1)
                            {
                                start = description.find(">", start);
                                if (start != std::string::npos)
                                {
                                    start += 1;
                                    end = description.find('<', start);
                                    if (end != std::string::npos)
                                    {
                                        if (end - start > 0)
                                        {
                                            description = description.substr(start, end - start).c_str();
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        description = "";
                                        break;
                                    }
                                }
                                else
                                {
                                    description = "";
                                    break;
                                }
                            }
                        }
                    }
                }

                if (element->FirstChild("link") && (url = element->FirstChild("link")->FirstChild()))
                {
                    link = (char*)url->Value();
                }

                std::string descr = description;
				std::cout << description << "\n";
                std::string delimiter = "[&#8230;]";
                
                description = descr.substr(0, descr.find(delimiter));
				
                description += "[...]";
            
                NewsStory* story = new NewsStory();
                story->Init(titlestr , description, link);
                story->m_W = IwGxGetDisplayWidth();
                story->m_Y = (IwGxGetDisplayHeight() / 4) + (IwGxGetDisplayHeight()/2)* (newsFeedCount - 1);
                newsFeedCount += 1;
				myScene->AddChild(story);
				myScene->labels.push_back(story);
                
                if (image.length())
                {
                    FetchImage(image.c_str(), titlestr.c_str());
                }
            }
        }
    }
    /*node = nullptr;
    channel = nullptr;
    element = nullptr;
    title = nullptr;
    desc = nullptr;
    url = nullptr;*/
}
//Type feed
//              1 = Calendar
//              2 = Events
void CIwRSS::CalendarParseRSS(const char * data, TiXmlDocument doc, int feedType)
{
    int bannerHeight = 0;
    _STL::string dateCheck = "";
    int numDates = 0;
    //Parse the RSS data
    bool loadOkay = doc.LoadFile();
    if (loadOkay) {
        printf("\nWe all good \n");
    } else {
        printf("\nWe not good \n");
    }
    doc.Parse(data, 0, TIXML_ENCODING_UTF8 );
    
    TiXmlElement * node = doc.RootElement();
	TiXmlElement * when;
    TiXmlNode * channel;
    TiXmlNode * element;
    TiXmlNode * start;
    TiXmlNode * end;
    TiXmlNode * title;
    TiXmlNode * desc;
    //printf("\nFirst Level \n");
    if (node != 0 && node->ToElement())
    {
        
        //Find channel
        //channel = node->FirstChild("feed");
        //printf("\nSecond Level \n");
        //if (channel != 0 && channel->ToElement())
        //{
            //printf("\nThird Level \n");
            //Loop through feed items
            for (element = node->FirstChild("entry");
                 element;
                 element = element->NextSibling("entry") )
            {
                // printf("\nLoop Level \n");
                if (!element->FirstChild("title") || !(title = element->FirstChild("title")->FirstChild())) {
                    continue;
                }
                //Found title
                std::string titlestr = title->Value();
                //TiXmlElement * titleElement = (TiXmlElement*) title;
                std::string description = "";
                std::string image = "";
                
                if (element->FirstChild("content") && (desc = element->FirstChild("content")->FirstChild()))
                {
                    description = desc->Value();
                    
                    //Description contains HTML data
                    if (description[0] == '<')
                    {
                        TiXmlDocument desc( "content.html" );
                        desc.Parse( description.c_str(), 0, TIXML_ENCODING_UTF8);
                        
                        TiXmlElement * head = desc.RootElement();
                        if (head != 0 && head->ToElement())
                        {
                            std::string::size_type start, end;
                            {
                                start = description.find("<img src=\"");
                                if (start != std::string::npos)
                                {
                                    start += 10;
                                    end = description.find('"', start + 1);
                                    if (end != std::string::npos)
                                    {
                                        image = description.substr(start, end - start);
                                       // IwTrace(UI, ("Image found %s", image.c_str()));
                                    }
                                }
                            }
                            
                            start = 0;
                            while (1)
                            {
                                start = description.find(">", start);
                                if (start != std::string::npos)
                                {
                                    start += 1;
                                    end = description.find('<', start);
                                    if (end != std::string::npos)
                                    {
                                        if (end - start > 0)
                                        {
                                            //IwTrace(UI, ("Out: %s", description.substr(start, end - start).c_str()));
                                            description = description.substr(start, end - start).c_str();
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        description = "";
                                        break;
                                    }
                                }
                                else
                                {
                                    description = "";
                                    break;
                                }
                            }
                        }
                    }

                }
				std::string starttime;
				std::string endtime;
				when = element->FirstChildElement("gd:when");

				starttime = when->Attribute("startTime");
				endtime= when->Attribute("endTime");
                //Get the start time and date
				std::string s = starttime;
                std::string delimiter = "T";
                
                std::string date = s.substr(0, s.find(delimiter));
                std::string fullTime = s.substr(s.find(delimiter), s.length());
                delimiter = ":";
                starttime = fullTime.substr(1, fullTime.find(delimiter)-1);
                //Get the end time
                s = endtime;
                delimiter = "T";
                
                fullTime = s.substr(s.find(delimiter), s.length());
                delimiter = ":";
                endtime = fullTime.substr(1, fullTime.find(delimiter)-1);
                
                _STL::istringstream buffer(starttime);
                int startTimeValue;
                buffer >> startTimeValue;
                
                buffer.clear();
                
                buffer.str(endtime);
                int endTimeValue;
                buffer >> endTimeValue;
                
                _STL::ostringstream convert;
                if(startTimeValue > 12) {
                    convert.clear();
                    convert << (startTimeValue - 12) << "p";
                    starttime = convert.str();
                } else {
                    convert.clear();
                    convert << (startTimeValue) << "a";
                    starttime = convert.str();
                
                }
                
                if(endTimeValue > 12) {
                    convert.clear();
                    convert.str("");
                    convert << (endTimeValue - 12) << "p";
                    endtime = convert.str();
                } else {
                    convert.clear();
                    convert.str("");
                    convert << (endTimeValue) << "a";
                    endtime = convert.str();
                }
                
                if(date.compare(dateCheck) != 0) {
                    dateCheck = date;
                    
                    CLabel* title = new CLabel();
                    title->m_W = IwGxGetDisplayWidth();
                    if(feedType == 1) {
                        title->m_Y = (IwGxGetDisplayHeight() / 4) + (IwGxGetDisplayHeight()/4)* (calendarFeedCount - 1) + ((numDates) * bannerHeight);
                    } else {
                        title->m_Y = (IwGxGetDisplayHeight() / 4) + (IwGxGetDisplayHeight()/4)* (eventFeedCount - 1) + ((numDates) * bannerHeight);
                    }
                    title->m_AlignHor = IW_2D_FONT_ALIGN_CENTRE;
                    title->m_Font = g_pResources->getHeaderFont();
                    //title->m_Color = CColor(255, , 0, 0xff);
                    title->SetText(date);
                    
                    CSprite* goldBanner = new CSprite();
                    goldBanner->SetImage(g_pResources->getGoldBanner());
                    goldBanner->m_X = (float)IwGxGetScreenWidth() / 2;
                    if(feedType == 1) {
                        goldBanner->m_Y = (IwGxGetDisplayHeight() / 3.5) + (IwGxGetDisplayHeight()/4)* (calendarFeedCount - 1) + ((numDates) * bannerHeight);
                    } else {
                        goldBanner->m_Y = (IwGxGetDisplayHeight() / 3.5) + (IwGxGetDisplayHeight()/4)* (eventFeedCount - 1) + ((numDates) * bannerHeight);
                    }
                    goldBanner->m_W = goldBanner->GetImage()->GetWidth();
                    goldBanner->m_H = goldBanner->GetImage()->GetHeight();
                    bannerHeight = goldBanner->GetImage()->GetHeight();
                    goldBanner->m_AnchorX = 0.5;
                    goldBanner->m_AnchorY = 0.5;
                    // Fit background to screen size
                    goldBanner->m_ScaleX = (float)IwGxGetScreenWidth() / goldBanner->GetImage()->GetWidth() / 1;
                    goldBanner->m_ScaleY = (float)IwGxGetScreenHeight() / goldBanner->GetImage()->GetHeight() / 8;
                    
                    myScene->AddChild(goldBanner);
                    myScene->AddChild(title);
                    myScene->labels.push_back(goldBanner);
                    myScene->labels.push_back(title);
                    numDates++;
                }
                
                if(feedType == 1) {
                    //RSS FEED ITEMs...
                    CalendarStory* story = new CalendarStory();
                    story->Init(titlestr , description, "http://radio.uccs.edu/index.php/schedule", starttime, endtime);
                    story->m_W = IwGxGetDisplayWidth();
                    story->m_Y = (IwGxGetDisplayHeight() / 2.5) + ((IwGxGetDisplayHeight()/4)* (calendarFeedCount - 1)) + ((numDates-1) * bannerHeight);
                    calendarFeedCount += 1;
                    myScene->AddChild(story);
                    myScene->labels.push_back(story);
                } else {
                    _STL::cout << "cowboy" << titlestr;
                    //RSS FEED ITEMs...
                    CalendarStory* story = new CalendarStory();
                    story->Init(titlestr , description, "http://radio.uccs.edu/index.php/schedule", starttime, endtime);
                    story->m_W = IwGxGetDisplayWidth();
                    story->m_Y = (IwGxGetDisplayHeight() / 2.5) + ((IwGxGetDisplayHeight()/4)* (eventFeedCount - 1)) + ((numDates-1) * bannerHeight);
                    eventFeedCount += 1;
                    myScene->AddChild(story);
                    myScene->labels.push_back(story);
                }
            //}
        }
    }
    /*node = nullptr;
	when = nullptr;
    channel = nullptr;
    element = nullptr;
    start = nullptr;
    end = nullptr;
    title = nullptr;
    desc = nullptr;*/
}


//-----------------------------------------------------------------------------

CIwRSS::CIwRSS(Scene* scene) : m_Progress(0)
{
	myScene = scene;
    m_HTTPQueue.SetMaxResultLen(200000);
}

CIwRSS::~CIwRSS(void)
{
    CancelFetch();
}

void CIwRSS::CancelFetch()
{
    // Clear all pending feed items
    m_HTTPQueue.CancelByArgument(this);

    while (m_FeedItems.size())
    {
        delete m_FeedItems.pop_back_get();
    }
}

void CIwRSS::FetchFeed(const char * url)
{
    CancelFetch();

    CFeedItem * feed = new CFeedItem(url, NULL);
    m_FeedItems.push_back(feed);

    m_Progress = 0;
    Fetch(feed);
}

void CIwRSS::FetchImage(const char * url, const char * title)
{
    CFeedItem * image = new CFeedItem(url, title);
    m_FeedItems.push_back(image);

    Fetch(image);
}

void CIwRSS::Fetch(CFeedItem* pFeedItem)
{
    m_HTTPQueue.Get(pFeedItem->GetURL(), this, HTTPHandler);
}

//-----------------------------------------------------------------------------

CIwRSS::CFeedItem::CFeedItem() : m_URL(NULL), m_ImageTitle(NULL)
{
}

CIwRSS::CFeedItem::CFeedItem(const char* url, const char* imageTitle) :
    m_URL(NULL), m_ImageTitle(NULL)
{
    if (url)
    {
        m_URL = new char[strlen(url)+1];
        strcpy(m_URL, url);
    }

    if (imageTitle)
    {
        m_ImageTitle = new char[strlen(imageTitle)+1];
        strcpy(m_ImageTitle, imageTitle);
    }
}

CIwRSS::CFeedItem::~CFeedItem()
{
    delete[] m_URL;
    delete[] m_ImageTitle;
}
