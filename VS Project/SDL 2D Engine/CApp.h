/**
CApp

SDL application class containing game loop

Author: Till Riemer
*/

#ifndef _CAPP_H_
    #define _CAPP_H_

#include <SDL.h>
#include "define.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CAnimation.h"
#include "CEntity.h"
#include "CArea.h"
#include "CCamera.h"
#include "CPlayer.h"
#include "CEnemy.h"

class CApp : public CEvent {

private:
    bool            Running;

    SDL_Surface*    Surf_Display;

	SDL_Surface*	surfBackground;

	CPlayer player;
	CEnemy enemy;

	SDL_Joystick *joystick;

public:
    CApp();

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

	void OnExit();

	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnJoyButtonDown(Uint8 which, Uint8 button);
	void OnJoyButtonUp(Uint8 which, Uint8 button);
	void OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);

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
