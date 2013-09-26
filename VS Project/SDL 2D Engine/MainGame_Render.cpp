#include "MainGame.h"
#include "SurfaceWrapper.h"

void MainGame::Render()
{
    // render area
	Area::Instance.Render(_surfDisplay, -Camera::Instance.GetX(), -Camera::Instance.GetY());
	
	// render entities
	for(uint16_t i=0; i<Entity::currentEntities.size(); i++)
	{
		Entity *curEntity = Entity::currentEntities[i];
		if(!curEntity) continue;

		if(curEntity->state == DEAD && curEntity->deathAnimation != NULL)
			curEntity->deathAnimation->Render(_surfDisplay);
		else
			curEntity->Render(_surfDisplay);
	}

	// render debug text
	if(_debugMode)
	{
		SDL_Color _textColor = {255,0,0};
		std::string s = std::to_string(GameTimer::FPSControl.GetFPS());
		s += "FPS";
		char const *pchar = s.c_str();
		_debugMessage = TTF_RenderText_Solid(_debugFont, pchar, _textColor);
		SurfaceWrapper::Draw(_surfDisplay, _debugMessage, 5, 5, 0, 0, 100, 100);
	}

    SDL_Flip(_surfDisplay);
}
