#include "CApp.h"
#include "CSurface.h"

void CApp::OnRender()
{
    // render area
	CArea::areaControl.OnRender(_surfDisplay, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	
	// render entities
	for(uint16_t i=0; i<CEntity::EntityList.size(); i++)
	{
		if(!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnRender(_surfDisplay);
	}

    SDL_Flip(_surfDisplay);
}
