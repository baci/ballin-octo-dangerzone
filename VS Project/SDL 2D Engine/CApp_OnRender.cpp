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

	// render debug text
	if(_debugMode)
	{
		//Render the text
		SDL_Color _textColor = {255,0,0};
		std::string s = std::to_string(CFPS::FPSControl.GetFPS());
		s += "FPS";
		char const *pchar = s.c_str();
		_debugMessage = TTF_RenderText_Solid(_debugFont, pchar, _textColor);
		CSurface::OnDraw(_surfDisplay, _debugMessage, 5, 5, 0, 0, 100, 100);
	}

    SDL_Flip(_surfDisplay);
}
