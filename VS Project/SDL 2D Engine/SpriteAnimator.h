#ifndef _SPRITEANIMATOR_H_
    #define _SPRITEANIMATOR_H_
 
#include <SDL.h>

class SpriteAnimator {

private:
	int currentFrame;
	int frameInc;

	int frameRate; // DELAY in milliseconds
	long oldTime; // time passed since last animation frame

public:
	int maxFrames;
	bool oscillate; // true: increase/decrease frames, false: loop

	SpriteAnimator();

	/*
	animate one frame.
	*/
	void OnAnimate();

	void SetFrameRate(int rate);

	void SetCurrentFrame(int frame);

	int GetCurrentFrame();
};

#endif