#ifndef _ENTITY_H_
    #define _ENTITY_H_

#include <vector>
#include <string>

#include "Area.h"
#include "SpriteAnimation.h"
#include "GameTimer.h"
#include "ExtendedSurface.h"

class CApp;

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

class Camera;

/**
	An entity which can be moved / animated. (everything besides solid map objects)
*/
class Entity {
public:
	static std::vector<Entity*>	EntityList; // list of all existing entities

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
	int		flags; // flags for special properties of entity.

	// movement max. values (pixel per seconds)
	float	maxSpeedX;
	float	maxSpeedY;

protected:
	SpriteAnimation	animControl;
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

	bool	isDead;
	bool	isPlayer;

public:
	Entity();

	/**
	loading the entity spritefile and setting pink as transparent color
	TODO: do with/without transparent color or let it be specified
	*/
	virtual bool OnLoad(char* file, int width, int height, int maxFrames);

	virtual void OnLoop();
	virtual void OnRender(SDL_Surface* surfDisplay);
	virtual void OnCleanup();
	virtual void OnAnimate();
	virtual void OnCollision(Entity* entity);
	virtual void OnDie();

	bool IsDead(){return isDead;}
	bool IsPlayer(){return isPlayer;}

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
	bool PosValidTile(Tile* tile);
	bool PosValidEntity(Entity* entity, int newX, int newY);
};

/**
	collision event between two entities.
*/
class EntityCol {
public: 
	// queue-like list of entity collisions occurred.
	static std::vector<EntityCol> entityColList;

	Entity* entityA;
	Entity* entityB;

public:
	EntityCol();
};

#endif