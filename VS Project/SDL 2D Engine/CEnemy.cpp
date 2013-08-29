#include "CEnemy.h"

CEnemy::CEnemy()
{
	_walkDir = WALKDIR_RIGHT;
	maxSpeedX = maxSpeedX / 2;
}

bool CEnemy::OnLoad(char* file, int width, int height, int maxFrames)
{
	if(CEntity::OnLoad(file, width, height, maxFrames) == false) {
        return false;
    }
 
    return true;
}

void CEnemy::OnLoop()
{
	// move in one direction as long as possible
	if(_walkDir == WALKDIR_LEFT)
	{
		if(!PosValid(x-width, y-height) || !PosValid(x-width, y) || PosValid(x-width, y+height)) 
			_walkDir = WALKDIR_RIGHT;
	}
	else if(_walkDir == WALKDIR_RIGHT)
	{
		if(!PosValid(x+width, y-height) || !PosValid(x+width, y) || PosValid(x+width, y+height)) 
			_walkDir = WALKDIR_LEFT;
	}
	
	if(_walkDir == WALKDIR_RIGHT)
	{
		moveLeft = false;
		moveRight = true;
	}
	else if(_walkDir == WALKDIR_LEFT)
	{
		moveRight = false;
		moveLeft = true;
	}

	CEntity::OnLoop();
}

void CEnemy::ChangeDirection()
{
	_walkDir = _walkDir == WALKDIR_LEFT ? WALKDIR_RIGHT : WALKDIR_LEFT;
}
 
void CEnemy::OnAnimate()
{
	if(speedX != 0) {
        animControl.maxFrames = framesAmount;
    }else{
        animControl.maxFrames = 0;
    }
 
    CEntity::OnAnimate();
}
 
bool CEnemy::OnCollision(CEntity* entity)
{
	ChangeDirection();
	return true;
}