#include "MainGame.h"
#include "SurfaceWrapper.h"

bool MainGame::Init()
{
    // init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING | SDL_INIT_JOYSTICK) < 0)
        return false;
    // set up screen
    if((_surfDisplay = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) // opt. SDL_FULLSCREEN
        return false;

	//Set the window caption
    SDL_WM_SetCaption( "2D Platformer Engine by Till Riemer", NULL );

	// set up joystick if found
	printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );
    SDL_JoystickEventState(SDL_ENABLE);
    if(SDL_NumJoysticks()>0)
		_joystick = SDL_JoystickOpen(0); // open first joystick
	else
		_joystick = NULL;

	// set up font system
	if(TTF_WasInit() != 1)
		if (TTF_Init() < 0)
			return false;

	// load font(s)
	_debugFont = TTF_OpenFont( "debugFont.ttf", 16 );

	// Register event callbacks
	_eventHandler = new OSEventHandler();
	_eventHandler->OnExitDelegate.subscribe(OnExit);
	_eventHandler->OnJoyButtonDownDelegate.subscribe(OnJoyButtonDown);
	_eventHandler->OnJoyAxisDelegate.subscribe(OnJoyAxis);
	_eventHandler->OnKeyDownDelegate.subscribe(OnKeyDown);
	_eventHandler->OnKeyUpDelegate.subscribe(OnKeyUp);

	if(GameData::Instance.OnLoad("./maps/main.game") == false)
		return false;

	if(Area::Instance.Load("./maps/1.area") == false)
		return false;

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

    return true;
}
