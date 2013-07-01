#ifndef _CCAMERA_H_
    #define _CCAMERA_H_
 
#include <SDL.h>
 
#include "Define.h"
 
enum {
    TARGET_MODE_NORMAL = 0, // camera oriented on top-left of the target
    TARGET_MODE_CENTER
};

class CCamera {
    public:
        static CCamera CameraControl;
		int targetMode;
 
    private:
        int x;
        int y;
 
        float* targetX;
        float* targetY;
 
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
 
        void SetTarget(float* x, float* y);
};
 
#endif