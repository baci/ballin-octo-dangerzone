#include "CAnimation.h"

CAnimation::CAnimation()
{
	currentFrame = 0;
	maxFrames = 0;
	frameInc = 1;

	frameRate = 200; 
	oldTime = 0;

	oscillate = false;
}

void CAnimation::OnAnimate()
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

void CAnimation::SetFrameRate(int rate)
{
	frameRate = rate;
}

void CAnimation::SetCurrentFrame(int frame)
{
	if(frame < 0 || frame >= maxFrames) return;
	currentFrame = frame;
}

int CAnimation::GetCurrentFrame()
{
	return currentFrame;
}