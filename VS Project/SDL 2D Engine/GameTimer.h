#ifndef _GAMETIMER_H_
    #define _GAMETIMER_H_

#include <SDL.h>

/**
	speed control of the game. 
*/
class GameTimer 
{
public:
	static GameTimer FPSControl; // singleton instance

private:
	// vars to calculate FPS / speed factor
	int _oldTime;
	int _lastTime;

	// relative game speed. play around with to get slowmo / highspeed effects.
	float _speedFactor; 

	int _numFrames; // game's current FPS
	int _frames;

public:
	GameTimer();
	void Update();
	int GetFPS();
	float GetSpeedFactor();
};

#endif