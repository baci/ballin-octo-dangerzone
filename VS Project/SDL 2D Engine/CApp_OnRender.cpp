#include "CApp.h"
#include "CSurface.h"

void CApp::OnRender()
{
    CSurface::OnDraw(Surf_Display, surfBackground, 0, 0, 0, 0, 600, 600);

	// render area
	CArea::areaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	
	// render entities
	for(int i=0; i<CEntity::EntityList.size(); i++)
	{
		if(!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnRender(Surf_Display);
	}

    SDL_Flip(Surf_Display);
}
