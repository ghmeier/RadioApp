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

#if !defined(__STREAMER_H__)
#define __STREAMER_H__

#include "scene.h"

/**
 * @class Streamer
 *
 * @brief Streamer
 *
 * The main menu scene is a simple scene that contains a background, a button
 * and some text. The main menu is the first scene that is presented to the
 * player upon game boot. The user taps the button to start the game.
 *
 * The main menu scene is responsible for playing the main menu music and in-
 * game music.
 *
 */
class Streamer : public CNode
{
protected:
    // UI components
    CSprite*    playButton;
    CSprite*    stopButton;
    CSprite*    playWrapper;
    CSprite*    header;
    CSprite*    banner;
    CLabel*     labelLeft;
    CLabel*     labelRight;
    CLabel*     labelMain;
    
    
public:
    Streamer() {}
    ~Streamer();
    
    // initialise the menu
    void            Init();
    
    // Update the menu
    void            Update(float deltaTime = 0.0f, float alphaMul = 1.0f);
    
    // Render the menu
    void            Render();
    
    
};

#endif  // __STREAMER_H__

extern float buttonTop;
extern float buttonBottom;
extern int currentPage;
