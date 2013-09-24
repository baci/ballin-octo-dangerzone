#include "SpriteAnimator.h"

SpriteAnimator::SpriteAnimator()
{
	_currentFrame = 0;
	maxFrames = 0;
	_frameInc = 1;

	_frameRate = 200; 
	_oldTime = 0;

	oscillate = false;
}

void SpriteAnimator::OnAnimate()
{
	
	// check if frame time passed
	if(_oldTime + _frameRate > SDL_GetTicks())
		return;

	unsigned long frameCounter = (SDL_GetTicks() - _oldTime)/_frameRate;

	_oldTime = SDL_GetTicks();

	while(frameCounter)
	{
		// increment frame
		_currentFrame += _frameInc;
		if(oscillate)
		{
			if(_frameInc > 0)
			{
				if(_currentFrame >= maxFrames)
					_frameInc = -_frameInc;
			} else
			{
				if(_currentFrame <= 0)
					_frameInc = -_frameInc;
			}
		}
		else
		{
			if(_currentFrame >= maxFrames)
				_currentFrame = 0;
		}

		frameCounter--;
	}
}

void SpriteAnimator::SetFrameRate(int rate)
{
	_frameRate = rate;
}

void SpriteAnimator::SetCurrentFrame(int frame)
{
	if(frame < 0 || frame >= maxFrames) return;
	_currentFrame = frame;
}

int SpriteAnimator::GetCurrentFrame()
{
	return _currentFrame;
}