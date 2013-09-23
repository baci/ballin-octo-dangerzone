#include "MainGame.h"

void MainGame::OnExit()
{
	MainGame::GetInstance()->_running = false;
}

void MainGame::OnJoyButtonDown(Uint8 which, Uint8 button)
{
	switch (button)
	{
	case 0:
		Area::Instance.GetPlayer()->Jump();
		break;
	case 7:
		OnExit();
	default:
		break;
	}
}

void MainGame::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
	Player* player = Area::Instance.GetPlayer();
	if(axis == 0) // x axis
	{
		if(value < -7000)
		{
			player->state = MOVE_LEFT;
		}
		else if(value > 7000)
		{
			player->state = MOVE_RIGHT;
		}
		else
		{
			player->state = NO_STATE;
		}
	}
}

void MainGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	Player* player = Area::Instance.GetPlayer();
	switch (sym)
	{
	case SDLK_LEFT:
		player->state = MOVE_LEFT;
		break;
	case SDLK_RIGHT:
		player->state = MOVE_RIGHT;
		break;
	case SDLK_SPACE:
		player->Jump();
		break;
	default:
		break;
	}
}

void MainGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	Player* player = Area::Instance.GetPlayer();
	switch (sym)
	{
	case SDLK_LEFT:
	case SDLK_RIGHT:
		player->state = NO_STATE;
		break;
	default:
		break;
	}
}