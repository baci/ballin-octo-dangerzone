#include "Player.h"

Player::Player()
{
	isPlayer = true;
}

bool Player::OnLoad(char* file, int width, int height, int maxFrames)
{
	if(Entity::OnLoad(file, width, height, maxFrames) == false) {
        return false;
    }
 
    return true;
}
 
void Player::Spawn(float posX, float posY)
{
	x = _respawnX = posX;
	y = _respawnY = posY;
	isDead = false;
}

void Player::OnDie()
{
	Entity::OnDie();

	Spawn(_respawnX, _respawnY);
}

void Player::OnAnimate()
{
	if(speedX != 0) {
        animControl.maxFrames = framesAmount;
    }else{
        animControl.maxFrames = 0;
    }
 
    Entity::OnAnimate();
}
 
void Player::OnCollision(Entity* entity) 
{
	if(entity->y <= y + height)
		OnDie();
	else
		Jump();
}