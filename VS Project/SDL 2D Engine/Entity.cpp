#include "Entity.h"
#include "Camera.h"

std::vector<Entity*> Entity::EntityList;

Entity::Entity()
{
	surfEntity = NULL;

	x = 0;
	y = 0;
	width = 0;
	height = 0;
	moveLeft = false;
	moveRight = false;

	type = ENTITY_TYPE_GENERIC;
	flags = ENTITY_FLAG_GRAVITY;
	isDead = false;

	speedX = 0;
	speedY = 0;
	accelX = 0;
	accelY = 0;
	maxSpeedX = 10;
	maxSpeedY = 10;

	currentFrameCol = 0;
	currentFrameRow = 0;

	colX = 0;
	colY = 0;
	colWidth = 0;
	colHeight = 0;

	canJump = false;
}
bool Entity::OnLoad(char* file, int width, int height, int maxFrames)
{
	std::string fs = file;
	std::string path = "./charsets/";
	std::string filepath = path + fs;
	if((surfEntity = ExtendedSurface::OnLoad(const_cast<char*>(filepath.c_str()))) == NULL)
		return false;

	ExtendedSurface::Transparent(surfEntity, 255, 255, 255, false);

	this->width = width;
	this->height = height;
	this->framesAmount = maxFrames;
	
	animControl.maxFrames = maxFrames;

	return true;
}

void Entity::OnLoop()
{
	if(isDead)
		return;

	// standing
	if(moveLeft == false && moveRight == false)
		StopMove();
	
	if(moveLeft)
		accelX = -0.5;
	else if(moveRight)
		accelX = 0.5;

	if(flags & ENTITY_FLAG_GRAVITY)
		accelY = 0.75f;

	speedX += accelX * GameTimer::FPSControl.GetSpeedFactor();
	speedY += accelY * GameTimer::FPSControl.GetSpeedFactor();

	if(speedX > maxSpeedX) speedX = maxSpeedX;
	if(speedX < -maxSpeedX) speedX = -maxSpeedX;
	if(speedY > maxSpeedY) speedY = maxSpeedY;
	if(speedY < -maxSpeedY) speedY = -maxSpeedY;

	OnAnimate();
	OnMove(speedX, speedY);
}

void Entity::OnRender(SDL_Surface* surfDisplay)
{
	if(surfEntity == NULL || surfDisplay == NULL || isDead) return;

	ExtendedSurface::OnDraw(surfDisplay, surfEntity, x - Camera::CameraControl.GetX(), y - Camera::CameraControl.GetY(), 
		(currentFrameCol + animControl.GetCurrentFrame())*width, currentFrameRow*height, width, height);
}

void Entity::OnCleanup()
{
	if(surfEntity)
		SDL_FreeSurface(surfEntity);

	surfEntity = NULL;
}

void Entity::OnAnimate()
{
	if(moveLeft)
		currentFrameRow = 1;
	else if(moveRight)
		currentFrameRow = 2;

	if(canJump)
		animControl.OnAnimate();
}

void Entity::OnCollision(Entity* entity)
{
	// purely virtual
}

void Entity::OnDie()
{
	isDead = true;
}

void Entity::OnMove(float moveX, float moveY)
{
	if(moveX == 0 && moveY == 0) return;

	canJump = false;

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
		if(flags & ENTITY_FLAG_GHOST)
		{
			
			PosValid((int)(x+newX), (int)(y+newY));
			x += newX;
			y += newY;
		}
		else
		{
			// move or stop x movement on collision on the x axis
			if(PosValid((int)(x+newX), (int)(y)))
				x += newX;
			else
				speedX = 0;

			// move or stop y movement on collision on the y axis
			if(PosValid((int)(x), (int)(y+newY)))
				y += newY;
			else
			{
				if(moveY > 0)
					canJump = true;

				speedY = 0;
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

void Entity::StopMove()
{
	if(speedX > 0)
		accelX = -1;
	if(speedX < 0)
		accelX = 1;

	if(speedX < 2.0f && speedX > -2.0f)
	{
		accelX = 0;
		speedX = 0;
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

	int tX = (int)x + colX;
	int tY = (int)y + colY;

	left1 = tX;
	left2 = oX;
	right1 = left1 + width - 1 - colWidth;
	right2 = oX + oW - 1;
	top1 = tY;
	top2 = oY;
	bottom1 = top1 + height - 1 - colHeight;
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
bool Entity::PosValid(int newX, int newY)
{
	bool ret = true;

	int startX = (newX + colX) / TILE_SIZE;
	int startY = (newY + colY) / TILE_SIZE;
	int endX = ((newX + colX) + width - colWidth - 1) / TILE_SIZE;
	int endY = ((newY + colY) + height - colHeight - 1) / TILE_SIZE;

	// check for collision with map (getting all tileIds that the entity is over)
	for(int iY = startY; iY <= endY; iY++)
	{
		for(int iX = startX; iX <= endX; iX++)
		{
			Tile* tile = Area::areaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
			if(PosValidTile(tile) == false) ret = false;
		}
	}

	// check for collision with entity
	if(flags & ENTITY_FLAG_MAPONLY) ;
	else
	{
		for(uint8_t i=0; i<EntityList.size(); i++)
		{
			if(PosValidEntity(EntityList[i], newX, newY) == false) ret = false;
		}
	}

	return ret;
}

bool Entity::PosValidTile(Tile* tile)
{
	if(tile == NULL) return true;

	if(tile->TypeID == TILE_TYPE_BLOCK) return false;

	return true;
}

bool Entity::PosValidEntity(Entity* entity, int newX, int newY)
{
	if(this != entity && entity != NULL && entity->flags ^ ENTITY_FLAG_MAPONLY && entity->IsDead() == false &&
		entity->Collides(newX + colX, newY + colY, width - colWidth, height - colHeight) == true)
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
	if(canJump == false) return false;

	speedY = -maxSpeedY;
	return true;
}