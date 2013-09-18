#include "Enemy.h"

Enemy::Enemy()
{
	isPlayer = false;
	_walkDir = WALKDIR_RIGHT;
	maxSpeedX = maxSpeedX / 2;
}

bool Enemy::OnLoad(char* file, int width, int height, int maxFrames)
{
	if(Entity::OnLoad(file, width, height, maxFrames) == false) {
        return false;
    }
 
    return true;
}

void Enemy::OnLoop()
{
	if(isDead)
		return;
	
	// move in one direction as long as possible
	if(_walkDir == WALKDIR_LEFT)
	{
		// TODO change to posvalidtile and handle player collision in oncollision -> add current area to capp class
		if(!PosValid(x-width, y) || PosValid(x-width, y+height)) 
			_walkDir = WALKDIR_RIGHT;
	}
	else if(_walkDir == WALKDIR_RIGHT)
	{
		if(!PosValid(x+width, y) || PosValid(x+width, y+height)) 
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

	Entity::OnLoop();
}

void Enemy::ChangeDirection()
{
	_walkDir = _walkDir == WALKDIR_LEFT ? WALKDIR_RIGHT : WALKDIR_LEFT;
}
 
void Enemy::OnAnimate()
{
	if(speedX != 0) {
        animControl.maxFrames = framesAmount;
    }else{
        animControl.maxFrames = 0;
    }
 
    Entity::OnAnimate();
}
 
void Enemy::OnCollision(Entity* entity)
{
	if(entity->IsPlayer() && (entity->y + height < y))
		OnDie();
	else
		ChangeDirection();
}