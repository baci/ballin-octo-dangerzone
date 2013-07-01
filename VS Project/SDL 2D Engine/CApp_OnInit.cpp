#include "CApp.h"
#include "CSurface.h"

bool CApp::OnInit()
{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
        return false;
    // set up screen
    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) // opt. SDL_FULLSCREEN
        return false;

	// set up joystick if found
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0); // open first joystick

	if((surfBackground = CSurface::OnLoad("whiteBackground.bmp")) == NULL)
		return false;

	if(CArea::areaControl.OnLoad("./maps/1.area") == false)
		return false;

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    if(player.OnLoad("./yoshi.png", 64, 64, 8) == false)
		return false;
	if(player2.OnLoad("./yoshi.png", 64, 64, 8) == false)
		return false;

	player2.x = 100;

	CEntity::EntityList.push_back(&player);
	CEntity::EntityList.push_back(&player2);

	CCamera::CameraControl.targetMode = TARGET_MODE_CENTER;
	CCamera::CameraControl.SetTarget(&player.x, &player.y);

    return true;
}
