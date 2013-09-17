#include "OSEventHandler.h"
 
OSEventHandler::OSEventHandler() 
{
	
}
 
OSEventHandler::~OSEventHandler() {
    
}
 
/*
triggered on incoming event from SDL
*/
void OSEventHandler::OnEvent(SDL_Event* ev) {
    switch(ev->type) {
		// system events

        case SDL_ACTIVEEVENT: {
            switch(ev->active.state) {
                case SDL_APPMOUSEFOCUS: {
                    if ( ev->active.gain )    
					{
						OnMouseFocusDelegate.fire();
					}
                    else 
					{
						OnMouseBlurDelegate.fire();
					}
 
                    break;
                }
                case SDL_APPINPUTFOCUS: {
                    if ( ev->active.gain )
					{
						OnInputFocusDelegate.fire();
					}
                    else        
					{
						OnInputBlurDelegate.fire();
					}
 
                    break;
                }
                case SDL_APPACTIVE:    {
                    if ( ev->active.gain )
					{
						OnRestoreDelegate.fire();
					}
                    else
					{
						OnMinimizeDelegate.fire();
					}
 
                    break;
                }
            }
            break;
        }

		case SDL_QUIT: {
            OnExitDelegate.fire();
            break;
        }
 
        case SDL_SYSWMEVENT: {
            //Ignore
            break;
        }
 
		case SDL_VIDEORESIZE: {
			OnResizeDelegate.fire(ev->resize.w,ev->resize.h);
            break;
        }
 
        case SDL_VIDEOEXPOSE: {
            OnExposeDelegate.fire();
            break;
        }
 
		// input events

        case SDL_KEYDOWN: {
            OnKeyDownDelegate.fire(ev->key.keysym.sym,ev->key.keysym.mod,ev->key.keysym.unicode);
            break;
        }
 
        case SDL_KEYUP: {
            OnKeyUpDelegate.fire(ev->key.keysym.sym,ev->key.keysym.mod,ev->key.keysym.unicode);
            break;
        }
 
        case SDL_MOUSEBUTTONDOWN: {
            switch(ev->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonDownDelegate.fire(ev->button.x,ev->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonDownDelegate.fire(ev->button.x,ev->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonDownDelegate.fire(ev->button.x,ev->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_MOUSEBUTTONUP:    {
            switch(ev->button.button) {
                case SDL_BUTTON_LEFT: {
                    OnLButtonUpDelegate.fire(ev->button.x,ev->button.y);
                    break;
                }
                case SDL_BUTTON_RIGHT: {
                    OnRButtonUpDelegate.fire(ev->button.x,ev->button.y);
                    break;
                }
                case SDL_BUTTON_MIDDLE: {
                    OnMButtonUpDelegate.fire(ev->button.x,ev->button.y);
                    break;
                }
            }
            break;
        }
 
        case SDL_JOYAXISMOTION: {
            OnJoyAxisDelegate.fire(ev->jaxis.which,ev->jaxis.axis,ev->jaxis.value);
            break;
        }
 
        case SDL_JOYBALLMOTION: {
            OnJoyBallDelegate.fire(ev->jball.which,ev->jball.ball,ev->jball.xrel,ev->jball.yrel);
            break;
        }
 
        case SDL_JOYHATMOTION: {
            OnJoyHatDelegate.fire(ev->jhat.which,ev->jhat.hat,ev->jhat.value);
            break;
        }
        case SDL_JOYBUTTONDOWN: {
            OnJoyButtonDownDelegate.fire(ev->jbutton.which,ev->jbutton.button);
            break;
        }
 
        case SDL_JOYBUTTONUP: {
            OnJoyButtonUpDelegate.fire(ev->jbutton.which,ev->jbutton.button);
            break;
        }
 
        default: {
            OnUserDelegate.fire(ev->user.type,ev->user.code,ev->user.data1,ev->user.data2);
            break;
        }
    }
}