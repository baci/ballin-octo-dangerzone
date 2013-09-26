#include "GameTimer.h"

GameTimer GameTimer::FPSControl;

GameTimer::GameTimer()
{
	_oldTime = 0;
	_lastTime = 0;
	_speedFactor = 0;
	_frames = 0;
	_numFrames = 0;
}

void GameTimer::Update()
{
	if(_oldTime + 1000 < SDL_GetTicks())
	{
		_oldTime = SDL_GetTicks();
		_numFrames = _frames;
		_frames = 0;
	}

	_speedFactor = ((SDL_GetTicks() - _lastTime) / 1000.0f) * 32.0f;

	_lastTime = SDL_GetTicks();
	_frames++;
}

int GameTimer::GetFPS(){
	return _numFrames;
}

float GameTimer::GetSpeedFactor(){
	return _speedFactor;
}