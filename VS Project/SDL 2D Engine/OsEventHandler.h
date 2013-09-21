#pragma once

#ifndef _OS_EVENT_HANDLER_H_
    #define _OS_EVENT_HANDLER_H_

#include <SDL.h>
#include <vector>
#include <functional>
#include <iostream>

using namespace std;

/**
	generic OS event handler system.
	HandleEvent() checks event type and calls according delegate,
	to which other classes can subscribe.
*/
class OSEventHandler {
public:
	typedef function<void()> onInputFocus;
	struct OnInputFocusEvent {
	  vector<onInputFocus> subs;//criptions  
	  void subscribe(onInputFocus cb) { subs.push_back(cb); }
	  void fire() { for(onInputFocus& cb : subs) cb(); }
	};
	OnInputFocusEvent OnInputFocusDelegate;
	
	typedef function<void()> onInputBlur;
	struct OnInputBlurEvent {
	  vector<onInputBlur> subs;//criptions  
	  void subscribe(onInputBlur cb) { subs.push_back(cb); }
	  void fire() { for(onInputBlur& cb : subs) cb(); }
	};
	OnInputBlurEvent OnInputBlurDelegate;
	
	typedef function<void(SDLKey sym, SDLMod mod, Uint16 unicode)> onKeyDown;
	struct OnKeyDownEvent {
	  vector<onKeyDown> subs;//criptions  
	  void subscribe(onKeyDown cb) { subs.push_back(cb); }
	  void fire(SDLKey sym, SDLMod mod, Uint16 unicode) { for(onKeyDown& cb : subs) cb(sym, mod, unicode); }
	};
	OnKeyDownEvent OnKeyDownDelegate;
	
	typedef function<void(SDLKey sym, SDLMod mod, Uint16 unicode)> onKeyUp;
	struct OnKeyUpEvent {
	  vector<onKeyUp> subs;//criptions  
	  void subscribe(onKeyUp cb) { subs.push_back(cb); }
	  void fire(SDLKey sym, SDLMod mod, Uint16 unicode) { for(onKeyUp& cb : subs) cb(sym, mod, unicode); }
	};
	OnKeyUpEvent OnKeyUpDelegate;
	
	typedef function<void()> onMouseFocus;
	struct OnMouseFocusEvent {
	  vector<onMouseFocus> subs;//criptions  
	  void subscribe(onMouseFocus cb) { subs.push_back(cb); }
	  void fire() { for(onMouseFocus& cb : subs) cb(); }
	};
	OnMouseFocusEvent OnMouseFocusDelegate;
	
	typedef function<void()> onMouseBlur;
	struct OnMouseBlurEvent {
	  vector<onMouseBlur> subs;//criptions  
	  void subscribe(onMouseBlur cb) { subs.push_back(cb); }
	  void fire() { for(onMouseBlur& cb : subs) cb(); }
	};
	OnMouseBlurEvent OnMouseBlurDelegate;
	
	typedef function<void(int mX, int mY)> onLButtonDown;
	struct OnLButtonDownEvent {
	  vector<onLButtonDown> subs;//criptions  
	  void subscribe(onLButtonDown cb) { subs.push_back(cb); }
	  void fire(int mX, int mY) { for(onLButtonDown& cb : subs) cb(mX, mY); }
	};
	OnLButtonDownEvent OnLButtonDownDelegate;
	
	typedef function<void(int mX, int mY)> onLButtonUp;
	struct OnLButtonUpEvent {
	  vector<onLButtonUp> subs;//criptions  
	  void subscribe(onLButtonUp cb) { subs.push_back(cb); }
	  void fire(int mX, int mY) { for(onLButtonUp& cb : subs) cb(mX, mY); }
	};
	OnLButtonUpEvent OnLButtonUpDelegate;

	typedef function<void(int mX, int mY)> onRButtonDown;
	struct OnRButtonDownEvent {
	  vector<onRButtonDown> subs;//criptions  
	  void subscribe(onRButtonDown cb) { subs.push_back(cb); }
	  void fire(int mX, int mY) { for(onRButtonDown& cb : subs) cb(mX, mY); }
	};
	OnRButtonDownEvent OnRButtonDownDelegate;
	
	typedef function<void(int mX, int mY)> onRButtonUp;
	struct OnRButtonUpEvent {
	  vector<onRButtonUp> subs;//criptions  
	  void subscribe(onRButtonUp cb) { subs.push_back(cb); }
	  void fire(int mX, int mY) { for(onRButtonUp& cb : subs) cb(mX, mY); }
	};
	OnRButtonUpEvent OnRButtonUpDelegate;
	
	typedef function<void(int mX, int mY)> onMButtonDown;
	struct OnMButtonDownEvent {
	  vector<onMButtonDown> subs;//criptions  
	  void subscribe(onMButtonDown cb) { subs.push_back(cb); }
	  void fire(int mX, int mY) { for(onMButtonDown& cb : subs) cb(mX, mY); }
	};
	OnMButtonDownEvent OnMButtonDownDelegate;
	
	typedef function<void(int mX, int mY)> onMButtonUp;
	struct OnMButtonUpEvent {
	  vector<onMButtonUp> subs;//criptions  
	  void subscribe(onMButtonUp cb) { subs.push_back(cb); }
	  void fire(int mX, int mY) { for(onMButtonUp& cb : subs) cb(mX, mY); }
	};
	OnMButtonUpEvent OnMButtonUpDelegate;
	
	// joystick event handlers (require open joystick) -> "which" specifies the specific joystick
	typedef function<void(Uint8 which, Uint8 axis, Sint16 value)> onjoyAxis;
	struct OnJoyAxisEvent {
	  vector<onjoyAxis> subs;//criptions  
	  void subscribe(onjoyAxis cb) { subs.push_back(cb); }
	  void fire(Uint8 which, Uint8 axis, Sint16 value) { for(onjoyAxis& cb : subs) cb(which, axis, value); }
	};
	OnJoyAxisEvent OnJoyAxisDelegate;
	
	typedef function<void(Uint8 which, Uint8 button)> onJoyButtonDown;
	struct OnJoyButtonDownEvent {
	  vector<onJoyButtonDown> subs;//criptions  
	  void subscribe(onJoyButtonDown cb) { subs.push_back(cb); }
	  void fire(Uint8 which, Uint8 button) { for(onJoyButtonDown& cb : subs) cb(which, button); }
	};
	OnJoyButtonDownEvent OnJoyButtonDownDelegate;
	
	typedef function<void(Uint8 which, Uint8 button)> onJoyButtonUp;
	struct OnJoyButtonUpEvent {
	  vector<onJoyButtonUp> subs;//criptions  
	  void subscribe(onJoyButtonUp cb) { subs.push_back(cb); }
	  void fire(Uint8 which, Uint8 button) { for(onJoyButtonUp& cb : subs) cb(which, button); }
	};
	OnJoyButtonUpEvent OnJoyButtonUpDelegate;
	
	typedef function<void(Uint8 which, Uint8 hat, Uint8 value)> onJoyHat;
	struct OnJoyHatEvent {
	  vector<onJoyHat> subs;//criptions  
	  void subscribe(onJoyHat cb) { subs.push_back(cb); }
	  void fire(Uint8 which, Uint8 hat, Uint8 value) { for(onJoyHat& cb : subs) cb(which, hat, value); }
	};
	OnJoyHatEvent OnJoyHatDelegate;
	
	typedef function<void(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel)> onJoyBall;
	struct OnJoyBallEvent {
	  vector<onJoyBall> subs;//criptions  
	  void subscribe(onJoyBall cb) { subs.push_back(cb); }
	  void fire(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) { for(onJoyBall& cb : subs) cb(which, ball, xrel, yrel); }
	};
	OnJoyBallEvent OnJoyBallDelegate;
	
	typedef function<void()> onMinimize;
	struct OnMinimizeEvent {
	  vector<onMinimize> subs;//criptions  
	  void subscribe(onMinimize cb) { subs.push_back(cb); }
	  void fire() { for(onMinimize& cb : subs) cb(); }
	};
	OnMinimizeEvent OnMinimizeDelegate;
	
	typedef function<void()> onRestore;
	struct OnRestoreEvent {
	  vector<onRestore> subs;//criptions  
	  void subscribe(onRestore cb) { subs.push_back(cb); }
	  void fire() { for(onRestore& cb : subs) cb(); }
	};
	OnRestoreEvent OnRestoreDelegate;
	
	typedef function<void(int w, int h)> onResize;
	struct OnResizeEvent {
	  vector<onResize> subs;//criptions  
	  void subscribe(onResize cb) { subs.push_back(cb); }
	  void fire(int w, int h) { for(onResize& cb : subs) cb(w, h); }
	};
	OnResizeEvent OnResizeDelegate;

	typedef function<void()> onExpose;
	struct OnExposeEvent {
	  vector<onExpose> subs;//criptions  
	  void subscribe(onExpose cb) { subs.push_back(cb); }
	  void fire() { for(onExpose& cb : subs) cb(); }
	};
	OnExposeEvent OnExposeDelegate;

	typedef function<void()> onExit;
	struct OnExitEvent {
	  vector<onExit> subs;//criptions  
	  void subscribe(onExit cb) { subs.push_back(cb); }
	  void fire() { for(onExit& cb : subs) cb(); }
	};
	OnExitEvent OnExitDelegate;
	
	typedef function<void(Uint8 type, int code, void* data1, void* data2)> onUser;
	struct OnUserEvent {
	  vector<onUser> subs;//criptions  
	  void subscribe(onUser cb) { subs.push_back(cb); }
	  void fire(Uint8 type, int code, void* data1, void* data2) { for(onUser& cb : subs) cb(type, code, data1, data2); }
	};
	OnUserEvent OnUserDelegate;
	

	OSEventHandler();

	virtual ~OSEventHandler();
 
    virtual void HandleEvent(SDL_Event* ev);
        

private:
	SDL_Joystick *joystick;
};
 
#endif