#include "MainGame.h"

void MainGame::OnCleanup()
{
    // free all existing surfaces
	for(Uint8 i=0; i<Entity::EntityList.size(); i++)
	{
		if(!Entity::EntityList[i]) continue;

		Entity::EntityList[i]->OnCleanup();
	}
	Entity::EntityList.clear();

	Area::areaControl.OnCleanup();

	SDL_FreeSurface(_debugMessage);
	TTF_CloseFont( _debugFont );
    //Quit SDL_ttf
    TTF_Quit();

    SDL_FreeSurface(_surfDisplay);

	// close joystick handler
	if(_joystick != NULL)
	{
		SDL_JoystickClose(_joystick);
		SDL_JoystickEventState(SDL_DISABLE);
	}

    SDL_Quit();
}
