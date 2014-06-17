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

#if !defined(__USSCRADIO_H__)
#define __USSCRADIO_H__

#include "IwTween.h"
#include "newsScene.h"
#include "src/HttpClient.h"

using namespace IwTween;

extern CTweenManager*       g_pTweener;
extern int newsFeedCount;
extern int calendarFeedCount;
extern int eventFeedCount;
extern HttpClient* globalHttpClient;
extern bool labelsScrolling;
extern Ptr<HttpDownload> xmlDownload;
extern Ptr<HttpDownload> xmlCalendarDownload;
extern Ptr<HttpDownload> xmlEventsDownload;

#endif  // __UCCSRADIO_H__