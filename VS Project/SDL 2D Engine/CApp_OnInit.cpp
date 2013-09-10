
#include "CApp.h"
#include "CSurface.h"

bool CApp::OnInit()
{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
        return false;
    // set up screen
    if((_surfDisplay = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) // opt. SDL_FULLSCREEN
        return false;

	// set up joystick if found
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    SDL_JoystickEventState(SDL_ENABLE);
    if(SDL_NumJoysticks()>0)
		joystick = SDL_JoystickOpen(0); // open first joystick
	else
		joystick = NULL;

	if(CArea::areaControl.OnLoad("./maps/1.area") == false)
		return false;

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    return true;
}
