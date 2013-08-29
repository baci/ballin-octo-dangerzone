#include "CApp.h"

void CApp::OnCleanup()
{
    // free all existing surfaces
	for(Uint8 i=0; i<CEntity::EntityList.size(); i++)
	{
		if(!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnCleanup();
	}
	CEntity::EntityList.clear();

	CArea::areaControl.OnCleanup();

    SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(surfBackground);

	// close joystick handler
	if(joystick != NULL)
	{
		SDL_JoystickClose(joystick);
		SDL_JoystickEventState(SDL_DISABLE);
	}

    SDL_Quit();
}
