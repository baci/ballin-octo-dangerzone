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

    SDL_FreeSurface(_surfDisplay);

	// close joystick handler
	if(joystick != NULL)
	{
		SDL_JoystickClose(joystick);
		SDL_JoystickEventState(SDL_DISABLE);
	}

    SDL_Quit();
}
