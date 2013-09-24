#include "Entity.h"
#include "Camera.h"

std::vector<Entity*> Entity::currentEntities;

Entity::Entity()
{
	surfEntity = NULL;

	width = 0;
	height = 0;
	//x = 0;
	//y = 0;
	state = DEAD;

	type = GENERIC;

	_speedX = 0;
	_speedY = 0;
	_accelX = 0;
	_accelY = 0;
	maxSpeedX = 10;
	maxSpeedY = 10;

	_currentFrameCol = 0;
	_currentFrameRow = 0;

	_canJump = false;
}
bool Entity::Load(char* file, int width, int height, int maxFrames)
{
	std::string fs = file;
	std::string path = "./charsets/";
	std::string filepath = path + fs;
	if((surfEntity = ExtendedSurface::OnLoad(const_cast<char*>(filepath.c_str()))) == NULL)
		return false;

	ExtendedSurface::Transparent(surfEntity, 255, 255, 255, false);

	this->width = width;
	this->height = height;
	this->_framesAmount = maxFrames;
	
	animControl.maxFrames = maxFrames;

	return true;
}

void Entity::Update()
{
	if(state == DEAD)
		return;

	// calculate movement speed...
	if(state != MOVE_LEFT && state != MOVE_RIGHT)
		StopMove();
	else if(state == MOVE_LEFT)
		_accelX = -0.5;
	else if(state == MOVE_RIGHT)
		_accelX = 0.5;

	_accelY = 0.75f;

	_speedX += _accelX * GameTimer::FPSControl.GetSpeedFactor();
	_speedY += _accelY * GameTimer::FPSControl.GetSpeedFactor();

	if(_speedX > maxSpeedX) _speedX = maxSpeedX;
	if(_speedX < -maxSpeedX) _speedX = -maxSpeedX;
	if(_speedY > maxSpeedY) _speedY = maxSpeedY;
	if(_speedY < -maxSpeedY) _speedY = -maxSpeedY;

	Animate();
	OnMove(_speedX, _speedY);
}

void Entity::Render(SDL_Surface* surfDisplay)
{
	if(surfEntity == NULL || surfDisplay == NULL || state == DEAD) return;

	ExtendedSurface::OnDraw(surfDisplay, surfEntity, x - Camera::Instance.GetX(), y - Camera::Instance.GetY(), 
		(_currentFrameCol + animControl.GetCurrentFrame())*width, _currentFrameRow*height, width, height);
}

void Entity::Cleanup()
{
	if(surfEntity)
		SDL_FreeSurface(surfEntity);

	surfEntity = NULL;
}

void Entity::Animate()
{
	if(state == MOVE_LEFT)
		_currentFrameRow = 3;
	else if(state == MOVE_RIGHT)
		_currentFrameRow = 1;

	if(_canJump)
		animControl.OnAnimate();
}

void Entity::OnEntityCollision(Entity* entity)
{
	// purely virtual
}

void Entity::Spawn(float posX, float posY)
{
	x = _respawnX = posX;
	y = _respawnY = posY;
	state = NO_STATE;
}

void Entity::Respawn()
{
	x = _respawnX;
	y = _respawnY;
	state = NO_STATE;
}

void Entity::Die()
{
	state = DEAD;
}

void Entity::OnMove(float moveX, float moveY)
{
	if(moveX == 0 && moveY == 0) return;

	_canJump = false;

	// position of where we WANT to go in the NEXT iteration of the loop below
	float newX = 0;
	float newY = 0;

	// get correct movement per second
	moveX *= GameTimer::FPSControl.GetSpeedFactor();
	moveY *= GameTimer::FPSControl.GetSpeedFactor();

	if(moveX != 0)
	{
		newX = GameTimer::FPSControl.GetSpeedFactor();
		if(moveX < 0)	newX *= -1;
	}
	if(moveY != 0)
	{
		newY = GameTimer::FPSControl.GetSpeedFactor();
		if(moveY < 0)	newY *= -1;
	}

	// calculate actual movement while checking for collisions
	while(true)
	{
		// move or stop x movement on collision on the x axis
		if(IsPositionValid((int)(x+newX), (int)(y)))
			x += newX;
		else
			_speedX = 0;

		// move or stop y movement on collision on the y axis
		if(IsPositionValid((int)(x), (int)(y+newY)))
			y += newY;
		else
		{
			if(moveY > 0)
				_canJump = true;

			_speedY = 0;
		}

		moveX += -newX;
		moveY += -newY;

		// break loop on collision on x/y axis
		if(newX > 0 && moveX <= 0) newX = 0;
		else if(newX < 0 && moveX >= 0) newX = 0;
		else if(moveX == 0) newX = 0;
		
		if(newY > 0 && moveY <= 0) newY = 0;
		else if(newY < 0 && moveY >= 0) newY = 0;
		else if(moveY == 0) newY = 0;

		if(moveX == 0 && moveY == 0)	break;
		if(newX == 0 && newY == 0)		break;
	}
}

/*
	invert acceleration until zero-point.
*/
void Entity::StopMove()
{
	if(_speedX > 0)
		_accelX = -1;
	if(_speedX < 0)
		_accelX = 1;

	if(_speedX < 2.0f && _speedX > -2.0f)
	{
		_accelX = 0;
		_speedX = 0;
	}
}

/**
	returns true if entity collides with object of the specified bounds
	working with rectangular collision boxes
*/
bool Entity::Collides(int otherX, int otherY, int otherWidth, int otherHeight)
{
	// bounds of the two collision boxes...
	int myLeft, otherLeft, myRight, otherRight;
	int myTop, otherTop, myBottom, otherBottom;

	myLeft = (int)x;
	otherLeft = otherX;
	myRight = myLeft + width - 1;
	otherRight = otherLeft + otherWidth - 1;
	myTop = (int)y;
	otherTop = otherY;
	myBottom = myTop + height - 1;
	otherBottom = otherTop + otherHeight - 1;


	// no collision if first object is out of range of the second object
	if(myBottom < otherTop)			return false;
	else if(myTop > otherBottom)	return false;
	else if(myRight < otherLeft)	return false;
	else if(myLeft > otherRight)	return false;

	return true;
}

/**
	Checking whether entity can move to absolute position newX, newY.
*/
bool Entity::IsPositionValid(int newX, int newY)
{
	bool ret = true;

	// (rounded) range of all tileIds that the entity is over
	int startX = (int)floor(newX / TILE_SIZE);
	int startY = (int)floor(newY / TILE_SIZE);
	int endX = (int)ceil((newX + width - 1) / TILE_SIZE);
	int endY = (int)ceil((newY + height - 1) / TILE_SIZE);

	// check for collision with map
	if(GameData::Instance.IsFullMapCollision())
	{
		// check for any map collision
		for(int iY = startY; iY <= endY; iY++)
		{
			for(int iX = startX; iX <= endX; iX++)
			{
				Tile* tile = Area::Instance.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
				if(IsPositionValidTile(tile) == false) ret = false;
			}
		}
	}
	else
	{
		// check only for map tiles below the entity
		if(newY > y)
		{
			for(int iX = startX; iX <= endX; iX++)
			{
				Tile* tile = Area::Instance.GetTile(iX * TILE_SIZE, endY * TILE_SIZE);
				if(IsPositionValidTile(tile) == false) ret = false;
			}
		}
	}
	

	// check for collision with entity
	for(uint8_t i=0; i<currentEntities.size(); i++)
	{
		if(IsPositionValidEntity(currentEntities[i], newX, newY) == false) ret = false;
	}

	return ret;
}

bool Entity::IsPositionValidTile(Tile* tile)
{
	if(tile == NULL) return true; // fall out of world

	if(tile->TypeID == TILE_TYPE_BLOCK) return false;

	return true;
}

bool Entity::IsPositionValidEntity(Entity* entity, int newX, int newY)
{
	if(this != entity && entity != NULL && entity->IsDead() == false &&
		entity->Collides(newX, newY, width, height) == true)
	{
		EntityCol entityCol;
		entityCol.entityA = this;
		entityCol.entityB = entity;

		EntityCol::entityColList.push_back(entityCol);
		return false;
	}

	return true;
}

bool Entity::Jump()
{
	if(_canJump == false) return false;

	_speedY = -maxSpeedY;
	return true;
}