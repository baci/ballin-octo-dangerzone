#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator()
{
	currentFrame = 0;
	maxFrames = 0;
	frameInc = 1;

	frameRate = 200; 
	oldTime = 0;

	oscillate = false;
}

void SpriteAnimator::OnAnimate()
{
	
	// check if frame time passed
	if(oldTime + frameRate > SDL_GetTicks())
		return;

	unsigned long frameCounter = (SDL_GetTicks() - oldTime)/frameRate;

	oldTime = SDL_GetTicks();

	while(frameCounter)
	{
		// increment frame
		currentFrame += frameInc;
		if(oscillate)
		{
			if(frameInc>0)
			{
				if(currentFrame >= maxFrames)
					frameInc = -frameInc;
			} else
			{
				if(currentFrame <= 0)
					frameInc = -frameInc;
			}
		}
		else
		{
			if(currentFrame >= maxFrames)
				currentFrame = 0;
		}

		frameCounter--;
	}
}

void SpriteAnimator::SetFrameRate(int rate)
{
	frameRate = rate;
}

void SpriteAnimator::SetCurrentFrame(int frame)
{
	if(frame < 0 || frame >= maxFrames) return;
	currentFrame = frame;
}

int SpriteAnimator::GetCurrentFrame()
{
	return currentFrame;
}