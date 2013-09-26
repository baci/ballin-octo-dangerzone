#ifndef _Camera_H_
    #define _Camera_H_
 
#include <SDL.h>
#include "Define.h"

enum {
    TARGET_MODE_NORMAL = 0,		// camera oriented on top-left of target sprite
    TARGET_MODE_CENTER,			// camera oriented on center of target sprite
	TARGET_MODE_FOLLOW			// camera following target if close to window bounds
};

class Entity;

class Camera {
    public:
        static Camera Instance;
		int targetMode;
 
    private:
        int _x;
        int _y;  

		Entity* _target;
		// threshold of screen border distance to follow target sprite
		float _followThreshold; 
 
    public:
        Camera();

		/*
		move by relative values
		*/
		void MoveRelative(int moveX, int moveY);

		/*
		adjusting camera according to camera mode and target position
		*/
		void Update();

		/*
		immediately centers the camera on the target
		*/
		void CenterOnTarget();

		int GetX();
		int GetY();
 
		/*
		move to absolute position
		*/
		void SetPos(int x, int y);
 
		/*
		sets the target entity which the camera is following
		*/
        void SetTarget(Entity* target);
};
 
#endif