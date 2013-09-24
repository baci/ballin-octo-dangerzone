/**
MainGame

SDL application class containing game loop

Author: Till Riemer
*/

#pragma once

#ifndef _MAINGAME_H_
    #define _MAINGAME_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include "define.h"
#include "OSEventHandler.h"
#include "ExtendedSurface.h"
#include "GameData.h"
#include "Entity.h"
#include "Area.h"
#include "Camera.h"
#include "Player.h"
#include "Enemy.h"

class MainGame {

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
	MainGame();
	static MainGame *_instance;

public:
	static MainGame *GetInstance();    

    /**
    main loop function
    */
    int Execute();

    /**
    Initialize application window
    */
    bool Init();
    /**
    handle system event
    */
    void HandleEvent(SDL_Event* Event);

	static void OnExit();
	static void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	static void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	static void OnJoyButtonDown(Uint8 which, Uint8 button);
	static void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);

    /**
    update game state
    */
    void Update();
    /**
    render contents
    */
    void Render();
    /**
    cleanup application window
    */
    void Cleanup();

};

#endif
