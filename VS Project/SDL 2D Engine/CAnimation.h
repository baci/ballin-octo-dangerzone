#ifndef _CANIMATION_H_
    #define _CANIMATION_H_
 
#include <SDL.h>

class CAnimation {

private:
	int currentFrame;
	int frameInc;

	int frameRate; // DELAY in milliseconds
	long oldTime; // time passed since last animation frame

public:
	int maxFrames;
	bool oscillate; // true: increase/decrease frames, false: loop

	CAnimation();

	/*
	animate one frame.
	*/
	void OnAnimate();

	void SetFrameRate(int rate);

	void SetCurrentFrame(int frame);

	int GetCurrentFrame();
};

#endif