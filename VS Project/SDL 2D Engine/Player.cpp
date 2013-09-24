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

	// clear pending collisions
	EntityCol::entityColList.clear();

	// respawn all entities on the map
	for(uint16_t i=0; i<(Entity::currentEntities.size()); i++)
	{
		Entity::currentEntities.at(i)->Respawn();
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
	
}