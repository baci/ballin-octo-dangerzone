#include "CApp.h"

void CApp::OnExit()
{
	CApp::GetInstance()->_running = false;
}

void CApp::OnJoyButtonDown(Uint8 which, Uint8 button)
{
	switch (button)
	{
	case 0:
		CArea::areaControl.GetPlayer()->Jump();
		break;
	case 7:
		OnExit();
	default:
		break;
	}
}

void CApp::OnJoyAxis(Uint8 which, Uint8 axis, Sint16 value)
{
	CPlayer* player = CArea::areaControl.GetPlayer();
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

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	CPlayer* player = CArea::areaControl.GetPlayer();
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

void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	CPlayer* player = CArea::areaControl.GetPlayer();
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