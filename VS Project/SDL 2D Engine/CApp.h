/**
CApp

SDL application class containing game loop

Author: Till Riemer
*/

#pragma once

#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include "define.h"
#include "OSEventHandler.h"
#include "CSurface.h"
#include "CAnimation.h"
#include "CEntity.h"
#include "CArea.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CEnemy.h"

class CApp {

private:
    bool    _running;
	bool	_debugMode;

    SDL_Surface*    _surfDisplay;
	SDL_Joystick*	_joystick;
	OSEventHandler*	_eventHandler;

	// debug message data
	SDL_Surface*	_debugMessage;
	TTF_Font*		_debugFont;

	// singleton
	CApp();
	static CApp *_instance;

public:
	static CApp *GetInstance();
    

    /**
    main loop function
    */
    int OnExecute();

    /**
    Initialize application window
    */
    bool OnInit();
    /**
    handle user input
    */
    void OnEvent(SDL_Event* Event);

	static void OnExit();
	static void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	static void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	static void OnJoyButtonDown(Uint8 which, Uint8 button);
	static void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);

    /**
    update game state
    */
    void OnLoop();
    /**
    render contents
    */
    void OnRender();
    /**
    cleanup application window
    */
    void OnCleanup();

};

#endif
