#ifndef _ENEMY_H_
    #define _ENEMY_H_

#include "Entity.h"

enum
{
	WALKDIR_LEFT = 0,
	WALKDIR_RIGHT
};

class Enemy : public Entity {


private:
	int _walkDir;

public:
	Enemy();

	bool OnLoad(char* file, int width, int height, int maxFrames);
 
    void OnLoop();

	void ChangeDirection();
 
    void OnAnimate();
 
    void OnCollision(Entity* entity);
};

#endif