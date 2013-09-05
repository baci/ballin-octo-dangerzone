#include "CEntity.h"
#include "CCamera.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity()
{
	surfEntity = NULL;

	x = 0;
	y = 0;
	width = 0;
	height = 0;
	moveLeft = false;
	moveRight = false;

	type = ENTITY_TYPE_GENERIC;
	dead = false;
	flags = ENTITY_FLAG_GRAVITY;

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

CEntity::~CEntity()
{
}

bool CEntity::OnLoad(char* file, int width, int height, int maxFrames)
{
	std::string fs = file;
	std::string path = "./charsets/";
	std::string filepath = path + fs;
	if((surfEntity = CSurface::OnLoad(const_cast<char*>(filepath.c_str()))) == NULL)
		return false;

	CSurface::Transparent(surfEntity, 255, 255, 255, false);

	this->width = width;
	this->height = height;
	this->framesAmount = maxFrames;
	
	animControl.maxFrames = maxFrames;

	return true;
}

void CEntity::OnLoop()
{
	// we're not moving
	if(moveLeft == false && moveRight == false)
		StopMove();
	
	if(moveLeft)
		accelX = -0.5;
	else if(moveRight)
		accelX = 0.5;

	if(flags & ENTITY_FLAG_GRAVITY)
		accelY = 0.75f;

	speedX += accelX * CFPS::FPSControl.GetSpeedFactor();
	speedY += accelY * CFPS::FPSControl.GetSpeedFactor();

	if(speedX > maxSpeedX) speedX = maxSpeedX;
	if(speedX < -maxSpeedX) speedX = -maxSpeedX;
	if(speedY > maxSpeedY) speedY = maxSpeedY;
	if(speedY < -maxSpeedY) speedY = -maxSpeedY;

	OnAnimate();
	OnMove(speedX, speedY);
}

void CEntity::OnRender(SDL_Surface* surfDisplay)
{
	if(surfEntity == NULL || surfDisplay == NULL) return;

	CSurface::OnDraw(surfDisplay, surfEntity, x - CCamera::CameraControl.GetX(), y - CCamera::CameraControl.GetY(), 
		(currentFrameCol + animControl.GetCurrentFrame())*width, currentFrameRow*height, width, height);
}

void CEntity::OnCleanup()
{
	if(surfEntity)
		SDL_FreeSurface(surfEntity);

	surfEntity = NULL;
}

void CEntity::OnAnimate()
{
	if(moveLeft)
		currentFrameRow = 1;
	else if(moveRight)
		currentFrameRow = 2;

	if(canJump)
		animControl.OnAnimate();
}

bool CEntity::OnCollision(CEntity* entity)
{
	return true;
}

void CEntity::OnMove(float moveX, float moveY)
{
	if(moveX == 0 && moveY == 0) return;

	canJump = false;

	// position of where we WANT to go in the next iteration of the loop below
	double newX = 0;
	double newY = 0;

	// get correct movement per second
	moveX *= CFPS::FPSControl.GetSpeedFactor();
	moveY *= CFPS::FPSControl.GetSpeedFactor();

	if(moveX != 0)
	{
		if(moveX >= 0)	newX = CFPS::FPSControl.GetSpeedFactor();
		else			newX = -CFPS::FPSControl.GetSpeedFactor();
	}
	if(moveY != 0)
	{
		if(moveY >= 0)	newY = CFPS::FPSControl.GetSpeedFactor();
		else			newY = -CFPS::FPSControl.GetSpeedFactor();
	}

	while(true)
	{
		if(flags & ENTITY_FLAG_GHOST)
		{
			// we don't care about collisions, but we need to send events to other entities
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

void CEntity::StopMove()
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

bool CEntity::Collides(int oX, int oY, int oW, int oH)
{
	// define bounds of the two collision boxes...
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

	// if all of the sides of the first object are out of range of the second object,
	// there is no collision.
	if(bottom1 < top2) return false;
	else if(top1 > bottom2) return false;
	else if(right1 < left2) return false;
	else if(left1 > right2) return false;

	return true;
}

/**
	newX, newY: position of where I want to move next
*/
bool CEntity::PosValid(int newX, int newY)
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
			CTile* tile = CArea::areaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
			if(PosValidTile(tile) == false) ret = false;
		}
	}

	// check for collision with entity
	if(flags & ENTITY_FLAG_MAPONLY) ;
	else
	{
		for(int i=0; i<EntityList.size(); i++)
		{
			if(PosValidEntity(EntityList[i], newX, newY) == false) ret = false;
		}
	}

	return ret;
}

bool CEntity::PosValidTile(CTile* tile)
{
	if(tile == NULL) return true;

	if(tile->TypeID == TILE_TYPE_BLOCK) return false;

	return true;
}

bool CEntity::PosValidEntity(CEntity* entity, int newX, int newY)
{
	if(this != entity && entity != NULL && entity->dead == false &&
		entity->flags ^ ENTITY_FLAG_MAPONLY &&
		entity->Collides(newX + colX, newY + colY, width - colWidth, height - colHeight) == true)
	{
		CEntityCol entityCol;
		entityCol.entityA = this;
		entityCol.entityB = entity;

		CEntityCol::entityColList.push_back(entityCol);
		return false;
	}

	return true;
}

bool CEntity::Jump()
{
	if(canJump == false) return false;

	speedY = -maxSpeedY;
	return true;
}