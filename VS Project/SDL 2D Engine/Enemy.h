#ifndef _ENEMY_H_
    #define _ENEMY_H_

#include "Entity.h"

enum WALKDIR
{
	DIR_LEFT = 0,
	DIR_RIGHT
};

class Enemy : public Entity {

private:
	WALKDIR _walkDir;

public:
	Enemy();

	bool Load(char* file, int width, int height, int maxFrames);
 
    void Update();

	void ChangeDirection();
 
    void Animate();
 
    void OnEntityCollision(Entity* entity);
};

#endif