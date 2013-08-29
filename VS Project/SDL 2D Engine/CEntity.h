#ifndef _CENTITY_H_
    #define _CENTITY_H_

#include <vector>
#include <string>

#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"

enum
{
	ENTITY_TYPE_GENERIC = 0,
	ENTITY_TYPE_PLAYER
};

enum
{
	ENTITY_FLAG_NONE = 0,
	ENTITY_FLAG_GRAVITY = 0x00000001,	// entity affected by gravity
	ENTITY_FLAG_GHOST = 0x00000002,		// entity can walk through walls
	ENTITY_FLAG_MAPONLY = 0x00000004	// entity only collides with map (not with other entities)
};

/**
	An entity which can be moved / animated. (everything besides solid map objects)
*/
class CEntity {
public:
	static std::vector<CEntity*>	EntityList; // list of all existing entities

	// entity bounds (pos. in world)
	float	x;
	float	y;
	int		width;
	int		height;

	// flags whether entity is moving in one direction.
	bool	moveLeft;
	bool	moveRight;

	// entity properties
	int		type; // entity type
	bool	dead; // whether entity is dead
	int		flags; // flags for special properties of entity.

	// movement max. values (pixel per seconds)
	float	maxSpeedX;
	float	maxSpeedY;

protected:
	CAnimation	animControl;
	SDL_Surface*	surfEntity;

	// current movement properties (pixel per second)
	float	speedX;
	float	speedY;
	float	accelX;
	float	accelY;

	// sprite animation state
	int		currentFrameCol;
	int		currentFrameRow;
	int		framesAmount;

	// collision offset values
	int		colX;
	int		colY;
	int		colWidth;
	int		colHeight;

	bool	canJump;

public:
	CEntity();
	virtual ~CEntity();

	/**
	loading the entity spritefile and setting pink as transparent color
	TODO: do with/without transparent color or let it be specified
	*/
	virtual bool OnLoad(char* file, int width, int height, int maxFrames);

	virtual void OnLoop();
	virtual void OnRender(SDL_Surface* surfDisplay);
	virtual void OnCleanup();
	virtual void OnAnimate();
	virtual bool OnCollision(CEntity* entity);

	/*
	move in a certain direction in pixel/seconds with acceleration.
	*/
	void OnMove(float moveX, float moveY);
	/*
	inverts acceleration until entity stops.
	*/
	void StopMove();

	bool Collides(int oX, int oY, int oW, int oH);

	bool Jump();

protected:
	/**
	checks if the tile the entity is trying to move to is valid.
	*/
	bool PosValid(int newX, int newY);
	bool PosValidTile(CTile* tile);
	bool PosValidEntity(CEntity* entity, int newX, int newY);
};

/**
	collision event between two entities.
*/
class CEntityCol {
public: 
	// queue-like list of entity collisions occurred.
	static std::vector<CEntityCol> entityColList;

	CEntity* entityA;
	CEntity* entityB;

public:
	CEntityCol();
};

#endif