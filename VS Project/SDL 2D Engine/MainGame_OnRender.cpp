#include "MainGame.h"
#include "ExtendedSurface.h"

void MainGame::OnRender()
{
    // render area
	Area::areaControl.OnRender(_surfDisplay, -Camera::CameraControl.GetX(), -Camera::CameraControl.GetY());
	
	// render entities
	for(uint16_t i=0; i<Entity::EntityList.size(); i++)
	{
		if(!Entity::EntityList[i]) continue;

		Entity::EntityList[i]->OnRender(_surfDisplay);
	}

	// render debug text
	if(_debugMode)
	{
		//Render the text
		SDL_Color _textColor = {255,0,0};
		std::string s = std::to_string(GameTimer::FPSControl.GetFPS());
		s += "FPS";
		char const *pchar = s.c_str();
		_debugMessage = TTF_RenderText_Solid(_debugFont, pchar, _textColor);
		ExtendedSurface::OnDraw(_surfDisplay, _debugMessage, 5, 5, 0, 0, 100, 100);
	}

    SDL_Flip(_surfDisplay);
}
