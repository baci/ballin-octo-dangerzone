#include "Player.h"

Player::Player()
{
	type = PLAYER;
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
	EntityCol::entityColList.clear();
}

void Player::Update()
{
	Entity::Update();

	if(y/TILE_SIZE > Area::Instance.areaSizeY)
	{
		Die();
		Entity::RespawnAll();
	}
}

void Player::Animate()
{
	if(_speedX != 0) {
        animControl.maxFrames = _framesAmount;
    }else{
        animControl.maxFrames = 0;
    }
 
    Entity::Animate();
}
 
void Player::OnEntityCollision(Entity* entity) 
{
	if(entity->y <= y + height)
	{
 		Die();

		deathAnimation->Play(&Entity::RespawnAll, (int)x, (int)y, width, height);
	}
	else
	  	Jump();
	
}