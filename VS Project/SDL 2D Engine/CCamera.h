#ifndef _CCAMERA_H_
    #define _CCAMERA_H_
 
#include <SDL.h>
#include "Define.h"

enum {
    TARGET_MODE_NORMAL = 0,		// camera oriented on top-left of target sprite
    TARGET_MODE_CENTER,			// camera oriented on center of target sprite
	TARGET_MODE_FOLLOW			// camera following target if close to window bounds
};

class CEntity;

class CCamera {
    public:
        static CCamera CameraControl;
		int targetMode;
		CEntity* target;

		float followThreshold; // threshold of screen border distance to follow target sprite
 
    private:
        int x;
        int y;        
 
    public:
        CCamera();

		/*
		move by relative values
		*/
		void OnMove(int moveX, int moveY);
		int GetX();
        int GetY();
 
		/*
		move to absolute position
		*/
		void SetPos(int x, int y);
 
        void SetTarget(CEntity* _target);
};
 
#endif