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
	int oldTime;
	int lastTime;

	float speedFactor; // relative game speed. play around with to get slowmo / highspeed effects.

	int numFrames; // game's current FPS
	int frames;

public:
	GameTimer();
	void OnLoop();
	int GetFPS();
	float GetSpeedFactor();
};

#endif