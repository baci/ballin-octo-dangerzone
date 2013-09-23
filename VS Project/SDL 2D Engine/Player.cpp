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
 
void Player::Spawn(float posX, float posY)
{
	x = _respawnX = posX;
	y = _respawnY = posY;
	state = NO_STATE;
}

void Player::Die()
{
	Entity::Die();

	Spawn(_respawnX, _respawnY);
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
		Die();
	else
		Jump();
}