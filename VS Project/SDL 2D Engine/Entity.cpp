#include "Entity.h"
#include "Camera.h"

std::vector<Entity*> Entity::currentEntities;

Entity::Entity()
{
	surfEntity = NULL;

	x = 0;
	y = 0;
	width = 0;
	height = 0;
	state = NO_STATE;

	type = GENERIC;
	flags = GRAVITY;

	_speedX = 0;
	_speedY = 0;
	_accelX = 0;
	_accelY = 0;
	maxSpeedX = 10;
	maxSpeedY = 10;

	_currentFrameCol = 0;
	_currentFrameRow = 0;

	_colX = 0;
	_colY = 0;
	_colWidth = 0;
	_colHeight = 0;

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

	// standing
	if(state != MOVE_LEFT && state != MOVE_RIGHT)
		StopMove();
	
	if(state == MOVE_LEFT)
		_accelX = -0.5;
	else if(state == MOVE_RIGHT)
		_accelX = 0.5;

	if(flags & GRAVITY)
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
		_currentFrameRow = 1;
	else if(state == MOVE_RIGHT)
		_currentFrameRow = 2;

	if(_canJump)
		animControl.OnAnimate();
}

void Entity::OnCollision(Entity* entity)
{
	// purely virtual
}

void Entity::Die()
{
	state = DEAD;
}

void Entity::OnMove(float moveX, float moveY)
{
	if(moveX == 0 && moveY == 0) return;

	_canJump = false;

	// position of where we WANT to go in the next iteration of the loop below
	float newX = 0;
	float newY = 0;

	// get correct movement per second
	moveX *= GameTimer::FPSControl.GetSpeedFactor();
	moveY *= GameTimer::FPSControl.GetSpeedFactor();

	if(moveX != 0)
	{
		if(moveX >= 0)	newX = GameTimer::FPSControl.GetSpeedFactor();
		else			newX = -GameTimer::FPSControl.GetSpeedFactor();
	}
	if(moveY != 0)
	{
		if(moveY >= 0)	newY = GameTimer::FPSControl.GetSpeedFactor();
		else			newY = -GameTimer::FPSControl.GetSpeedFactor();
	}

	// actual movement while checking for collisions
	while(true)
	{
		// ghost mode - entity doesn't care about collisions, but sends events to other entities
		if(flags & GHOST)
		{
			
			IsPositionValid((int)(x+newX), (int)(y+newY)); // called for collision on other entities
			x += newX;
			y += newY;
		}
		else
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
		}

		moveX += -newX;
		moveY += -newY;

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
bool Entity::Collides(int oX, int oY, int oW, int oH)
{
	// bounds of the two collision boxes...
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;

	int tX = (int)x + _colX;
	int tY = (int)y + _colY;

	left1 = tX;
	left2 = oX;
	right1 = left1 + width - 1 - _colWidth;
	right2 = oX + oW - 1;
	top1 = tY;
	top2 = oY;
	bottom1 = top1 + height - 1 - _colHeight;
	bottom2 = oY + oH - 1;

	// no collision if first object is out of range of the second object
	if(bottom1 < top2) return false;
	else if(top1 > bottom2) return false;
	else if(right1 < left2) return false;
	else if(left1 > right2) return false;

	return true;
}

/**
	newX, newY: position of where I want to move next
*/
bool Entity::IsPositionValid(int newX, int newY)
{
	bool ret = true;

	int startX = (newX + _colX) / TILE_SIZE;
	int startY = (newY + _colY) / TILE_SIZE;
	int endX = ((newX + _colX) + width - _colWidth - 1) / TILE_SIZE;
	int endY = ((newY + _colY) + height - _colHeight - 1) / TILE_SIZE;

	// check for collision with map (getting all tileIds that the entity is over)
	for(int iY = startY; iY <= endY; iY++)
	{
		for(int iX = startX; iX <= endX; iX++)
		{
			Tile* tile = Area::areaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
			if(IsPositionValidTile(tile) == false) ret = false;
		}
	}

	// check for collision with entity
	if(flags & MAPONLY) ;
	else
	{
		for(uint8_t i=0; i<currentEntities.size(); i++)
		{
			if(IsPositionValidEntity(currentEntities[i], newX, newY) == false) ret = false;
		}
	}

	return ret;
}

bool Entity::IsPositionValidTile(Tile* tile)
{
	if(tile == NULL) return true;

	if(tile->TypeID == TILE_TYPE_BLOCK) return false;

	return true;
}

bool Entity::IsPositionValidEntity(Entity* entity, int newX, int newY)
{
	if(this != entity && entity != NULL && entity->flags ^ MAPONLY && entity->IsDead() == false &&
		entity->Collides(newX + _colX, newY + _colY, width - _colWidth, height - _colHeight) == true)
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