#ifndef _ENTITY_H_
    #define _ENTITY_H_

#include <vector>
#include <string>

#include "Area.h"
#include "SpriteAnimator.h"
#include "GameTimer.h"
#include "ExtendedSurface.h"

class CApp;

enum ENTITY_TYPE
{
	GENERIC = 0,
	PLAYER
};

enum ENTITY_STATE
{
	NO_STATE = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	DIE,
	DEAD
};

class Camera;

/**
	An entity which can be moved / animated. (everything besides solid map objects)
*/
class Entity {
public:
	static std::vector<Entity*>	currentEntities; // list of all existing entities

	// entity bounds (pos. in world)
	float	x;
	float	y;
	int		width;
	int		height;

	// entity properties
	ENTITY_STATE	state;
	ENTITY_TYPE		type;

	// movement max. values (pixel per seconds)
	float	maxSpeedX;
	float	maxSpeedY;

protected:
	SpriteAnimator	animControl;
	SDL_Surface*	surfEntity;

	// current movement properties (pixel per second)
	float	_speedX;
	float	_speedY;
	float	_accelX;
	float	_accelY;

	// sprite animation state
	int		_currentFrameCol;
	int		_currentFrameRow;
	int		_framesAmount;

	bool	_canJump;

public:
	Entity();

	/**
	loading the entity spritefile and setting pink as transparent color
	TODO: do with/without transparent color or let it be specified
	*/
	virtual bool Load(char* file, int width, int height, int maxFrames);

	virtual void Update();
	virtual void Render(SDL_Surface* surfDisplay);
	virtual void Cleanup();

	virtual void Animate();
	virtual void OnEntityCollision(Entity* entity);
	virtual void Die();

	bool IsDead(){return state == DEAD;}
	bool IsPlayer(){return type == PLAYER;}

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
	bool IsPositionValid(int newX, int newY);
	bool IsPositionValidTile(Tile* tile);
	bool IsPositionValidEntity(Entity* entity, int newX, int newY);
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