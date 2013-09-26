#include "Enemy.h"

Enemy::Enemy()
{
	_walkDir = DIR_RIGHT;
	_maxSpeedX = _maxSpeedX / 2;
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
	if(state == NO_STATE)
		_walkDir = DIR_LEFT;
	
	// move in one direction as long as possible
	if(_walkDir == DIR_LEFT)
	{
		if(!IsPositionValidTile(Area::Instance.GetTile((int)_x-_width, (int)_y)) 
			|| IsPositionValidTile(Area::Instance.GetTile((int)_x-_width, (int)_y+_height))) 
			_walkDir = DIR_RIGHT;
	}
	else if(_walkDir == DIR_RIGHT)
	{
		if(!IsPositionValidTile(Area::Instance.GetTile((int)_x+_width, (int)_y)) 
			|| IsPositionValidTile(Area::Instance.GetTile((int)_x+_width, (int)_y+_height))) 
			_walkDir = DIR_LEFT;
	}
	
	if(_walkDir == DIR_RIGHT)
	{
		state = MOVE_RIGHT;
	}
	else if(_walkDir == DIR_LEFT)
	{
		state = MOVE_LEFT;
	}

	Entity::Update();
}

void Enemy::ChangeDirection()
{
	_walkDir = _walkDir == DIR_LEFT ? DIR_RIGHT : DIR_LEFT;
}
 
void Enemy::Animate()
{
	if(_speedX != 0) {
        _animator.maxFrames = _framesAmount;
    }else{
        _animator.maxFrames = 0;
    }
 
    Entity::Animate();
}
 
void Enemy::OnEntityCollision(Entity* entity)
{
	if(entity->IsPlayer() && (entity->GetY() + entity->GetHeight()*0.8 <= _y))
	{
		Die();
		deathAnimation->Play((int)_x, (int)_y, _width, _height);
	}
	else
		ChangeDirection();
}