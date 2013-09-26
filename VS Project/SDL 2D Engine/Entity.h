#ifndef _ENTITY_H_
    #define _ENTITY_H_

#include <vector>
#include <string>

#include "Area.h"
#include "SpriteAnimator.h"
#include "GameTimer.h"
#include "SurfaceWrapper.h"
#include "OneTimeAnimation.h"

class CApp;
class Camera;

enum ENTITY_TYPE
{
	COMMON = 0,
	PLAYER
};

enum ENTITY_STATE
{
	NO_STATE = 0,
	MOVE_LEFT,
	MOVE_RIGHT,
	DEAD
};

/**
	An entity which can be moved / animated. (everything besides solid map objects)
*/
class Entity {
public:
	// list of all existing entities
	static std::vector<Entity*>	currentEntities; 

	// entity properties
	ENTITY_STATE	state;

	OneTimeAnimation *deathAnimation;

protected:
	SpriteAnimator	_animator;
	SDL_Surface*	_entitySprite;

	ENTITY_TYPE		_type;

	// entity world position / bounds
	float	_x;
	float	_y;
	int		_width;
	int		_height;

	// current movement properties (pixel per second)
	float	_speedX;
	float	_speedY;
	float	_accelX;
	float	_accelY;
	float	_maxSpeedX;
	float	_maxSpeedY;

	// sprite animation state
	int		_currentFrameCol;
	int		_currentFrameRow;
	int		_framesAmount;

	bool	_canJump;

	// position to respawn on death
	float	_respawnX;
	float	_respawnY;

public:
	Entity();

	static void RespawnAll();

	//loading the entity spritefile and setting pink as transparent color
	virtual bool Load(char* file, int width, int height, int maxFrames);

	virtual void Update();
	virtual void Render(SDL_Surface* surfDisplay);
	virtual void Cleanup();

	virtual void Animate();
	virtual void OnEntityCollision(Entity* entity);
	virtual void Die();

	// move in a certain direction in pixel/seconds with acceleration.
	void OnMove(float moveX, float moveY);
	// inverts acceleration until entity stops.
	void StopMove();
	void Spawn(float posX, float posY);
	void Respawn();
	// checks collision with specified rectangle based on entity bounds as rectangle
	bool Collides(int oX, int oY, int oW, int oH);
	// executes a single jump
	bool Jump();

	bool IsDead(){return state == DEAD;}
	bool IsPlayer(){return _type == PLAYER;}

	float GetX();
	float GetY();
	int GetWidth();
	int GetHeight();

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
class EntityCollision {
public: 
	// queue-like list of entity collisions occurred.
	static std::vector<EntityCollision> curCollisions;

	EntityCollision();

	Entity* eA;
	Entity* eB;
};

#endif