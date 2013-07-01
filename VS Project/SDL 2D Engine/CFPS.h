#ifndef _CFPS_H_
    #define _CFPS_H_

#include <SDL.h>

/**
	speed control of the game. 
*/
class CFPS 
{
public:
	static CFPS FPSControl; // singleton instance

private:
	// vars to calculate FPS / speed factor
	int oldTime;
	int lastTime;

	float speedFactor; // relative game speed. play around with to get slowmo / highspeed effects.

	int numFrames; // game's current FPS
	int frames;

public:
	CFPS();
	void OnLoop();
	int GetFPS();
	float GetSpeedFactor();
};

#endif