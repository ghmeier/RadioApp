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

#if !defined(__INPUT_H__)
#define __INPUT_H__

#include "s3ePointer.h"


#define MAX_TOUCHES     10

class Input
{
public:
    int             m_X, m_Y,start_X,start_Y; // Touched position
	int				prev_Y,prev_X;
    bool            m_Touched;          // Touched status
    bool            m_PrevTouched;      // Previous touched status
	bool			m_canScroll;
    
public:
    Input();
    
    /**
     * @fn    void Input::Update()
     *
     * @brief Updates the input system, called every frame
     */
    void            Update();
    /**
     * @fn    void Input::Reset()
     *
     * @brief Resets touch status, usually called after a touch event has been acknowledged
     */
    void            Reset();
    
    // Callbacks
    static void     TouchButtonCB(s3ePointerEvent* event);
    static void     TouchMotionCB(s3ePointerMotionEvent* event);
    static void     MultiTouchButtonCB(s3ePointerTouchEvent* event);
    static void     MultiTouchMotionCB(s3ePointerTouchMotionEvent* event);
};

extern Input* g_pInput;


#endif  // __INPUT_H__


