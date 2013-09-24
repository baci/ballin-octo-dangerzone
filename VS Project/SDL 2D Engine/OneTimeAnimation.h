/**
	sprite animation that is playing a single time and then sending an event.
*/

#ifndef _ONETIME_ANIMATION_H_
    #define _ONETIME_ANIMATION_H_


#include <SDL.h>
#include <vector>
#include <functional>
#include <iostream>
#include <string>
#include "SpriteAnimator.h"
#include "Camera.h"
#include "ExtendedSurface.h"

using namespace std;

class OneTimeAnimation {
public:
	typedef function<void()> onAnimationEnd;
	struct OnAnimationEndEvent {
	  vector<onAnimationEnd> subs;//criptions  
	  void subscribe(onAnimationEnd cb) { subs.push_back(cb); }
	  void fire() { for(onAnimationEnd& cb : subs) cb(); }
	};
	OnAnimationEndEvent OnAnimationEndDelegate;

	OneTimeAnimation();
	bool Load(char* file, int width, int height, int maxFrames);
	void Play(int x, int y, int w, int h);
	void Play(onAnimationEnd cb, int x, int y, int w, int h);
	void Update();
	void Render(SDL_Surface* surfDisplay);
	void OnAnimationEnd();

	int		width;
	int		height;

private:
	SpriteAnimator	_animator;
	SDL_Surface*	_surfEntity;
	bool _playing;

	int		_framesAmount;
	int		_targetX;
	int		_targetY;
	int		_targetW;
	int		_targetH;
};

#endif