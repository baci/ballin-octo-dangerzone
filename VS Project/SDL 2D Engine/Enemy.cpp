#include "Enemy.h"

Enemy::Enemy()
{
	_walkDir = WALKDIR_RIGHT;
	maxSpeedX = maxSpeedX / 2;
}

bool Enemy::Load(char* file, int width, int height, int maxFrames)
{
	if(Entity::Load(file, width, height, maxFrames) == false) {
        return false;
    }
 
    return true;
}

void Enemy::Update()
{
	if(state == DEAD)
		return;
	
	// move in one direction as long as possible
	if(_walkDir == WALKDIR_LEFT)
	{
		if(!IsPositionValidTile(Area::Instance.GetTile(x-width, y)) || IsPositionValidTile(Area::Instance.GetTile(x-width, y+height))) 
			_walkDir = WALKDIR_RIGHT;
	}
	else if(_walkDir == WALKDIR_RIGHT)
	{
		if(!IsPositionValidTile(Area::Instance.GetTile(x+width, y)) || IsPositionValidTile(Area::Instance.GetTile(x+width, y+height))) 
			_walkDir = WALKDIR_LEFT;
	}
	
	if(_walkDir == WALKDIR_RIGHT)
	{
		state = MOVE_RIGHT;
	}
	else if(_walkDir == WALKDIR_LEFT)
	{
		state = MOVE_LEFT;
	}

	Entity::Update();
}

void Enemy::ChangeDirection()
{
	_walkDir = _walkDir == WALKDIR_LEFT ? WALKDIR_RIGHT : WALKDIR_LEFT;
}
 
void Enemy::Animate()
{
	if(_speedX != 0) {
        animControl.maxFrames = _framesAmount;
    }else{
        animControl.maxFrames = 0;
    }
 
    Entity::Animate();
}
 
void Enemy::OnEntityCollision(Entity* entity)
{
	if(entity->IsPlayer() && (entity->y + height < y))
		Die();
	else
		ChangeDirection();
}