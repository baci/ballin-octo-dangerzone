#ifndef _SPRITEANIMATOR_H_
    #define _SPRITEANIMATOR_H_
 
#include <SDL.h>

class SpriteAnimator {

private:
	int _currentFrame;
	int _frameInc;

	// delay in milliseconds
	int _delayMs;
	// time passed since last animation frame
	long _oldTime; 

public:
	int maxFrames;
	// true: increase/decrease frames, false: loop
	bool oscillate; 

	SpriteAnimator();

	// animate a single frame.
	void OnAnimate();

	void SetDelay(int delay);

	void SetCurrentFrame(int frame);

	int GetCurrentFrame();
};

#endif