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
		Area::areaControl.GetPlayer()->Jump();
		break;
	case 7:
		OnExit();
	default:
		break;
	}
}

void MainGame::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
	Player* player = Area::areaControl.GetPlayer();
	if(axis == 0) // x axis
	{
		if(value < -7000)
		{
			player->moveRight = false;
			player->moveLeft = true;
		}
		else if(value > 7000)
		{
			player->moveLeft = false;
			player->moveRight = true;
		}
		else
		{
			player->moveLeft = false;
			player->moveRight = false;
		}
	}
}

void MainGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	Player* player = Area::areaControl.GetPlayer();
	switch (sym)
	{
	case SDLK_LEFT:
		player->moveLeft = true;
		break;
	case SDLK_RIGHT:
		player->moveRight = true;
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
	Player* player = Area::areaControl.GetPlayer();
	switch (sym)
	{
	case SDLK_LEFT:
		player->moveLeft = false;
		break;
	case SDLK_RIGHT:
		player->moveRight = false;
		break;
	default:
		break;
	}
}