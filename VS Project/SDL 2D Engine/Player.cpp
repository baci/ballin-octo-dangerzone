#include "Player.h"

Player::Player()
{
	_type = PLAYER;
}

bool Player::Load(char* file, int width, int height, int maxFrames)
{
	if(Entity::Load(file, width, height, maxFrames) == false) {
        return false;
    }
 
    return true;
}

void Player::Die()
{
	Entity::Die();

	// clear pending collisions and respawn after animation
	EntityCollision::curCollisions.clear();
}

void Player::Update()
{
	Entity::Update();

	if(_y/TILE_SIZE > Area::Instance.GetAreaSizeY())
	{
		Die();
		Entity::RespawnAll();
	}
}

void Player::Animate()
{
	if(_speedX != 0) {
        _animator.maxFrames = _framesAmount;
    }else{
        _animator.maxFrames = 0;
    }
 
    Entity::Animate();
}
 
void Player::OnEntityCollision(Entity* entity) 
{
	if(entity->GetY() <= _y + _height*0.8)
	{
 		Die();

		deathAnimation->Play(&Entity::RespawnAll, (int)_x, (int)_y, _width, _height);
	}
	else
	  	Jump();
	
}