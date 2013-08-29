#ifndef _CENEMY_H_
    #define _CENEMY_H_

#include "CEntity.h"

enum
{
	WALKDIR_LEFT = 0,
	WALKDIR_RIGHT
};

class CEnemy : public CEntity {


private:
	int _walkDir;

public:
	CEnemy();

	bool OnLoad(char* file, int width, int height, int maxFrames);
 
    void OnLoop();

	void ChangeDirection();
 
    void OnAnimate();
 
    bool OnCollision(CEntity* entity);
};

#endif