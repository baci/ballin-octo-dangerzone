#include "OneTimeAnimation.h"

OneTimeAnimation::OneTimeAnimation()
{
	_surfEntity = NULL;
	_playing = false;
	_targetX = 0;
	_targetY = 0;
}

bool OneTimeAnimation::Load(char* file, int width, int height, int maxFrames)
{
	std::string fs = file;
	std::string path = "./charsets/";
	std::string filepath = path + fs;
	if((_surfEntity = SurfaceWrapper::Load(const_cast<char*>(filepath.c_str()))) == NULL)
		return false;

	SurfaceWrapper::SetTransparency(_surfEntity, 255, 255, 255, false);

	this->width = width;
	this->height = height;
	this->_framesAmount = maxFrames;
	
	_animator.maxFrames = maxFrames;

	return true;
}

void OneTimeAnimation::Play(onAnimationEnd cb, int x, int y, int w, int h)
{
	OnAnimationEndDelegate.subscribe(cb);

	Play(x, y, w, h);
	
}

void OneTimeAnimation::Play(int x, int y, int w, int h)
{
	_targetX = x;
	_targetY = y;
	_targetW = w;
	_targetH = h;
	_playing = true;
}

void OneTimeAnimation::Update()
{
	if(_playing)
	{
		if(_animator.GetCurrentFrame() < _animator.maxFrames-1)
			_animator.OnAnimate();
		else
		{
			_playing = false;
			_animator.SetCurrentFrame(0);
			OnAnimationEndDelegate.fire();
			OnAnimationEndDelegate.subs.clear();
		}
	}
}

void OneTimeAnimation::Render(SDL_Surface* surfDisplay)
{
	if(_surfEntity == NULL || surfDisplay == NULL || _playing == false) return;

	SurfaceWrapper::Draw(surfDisplay, _surfEntity, 
		_targetX-(width/2 - _targetW/2) - Camera::Instance.GetX(), _targetY-(height - _targetH) - Camera::Instance.GetY(), 
		(_animator.GetCurrentFrame())*width, 0, width, height);
}