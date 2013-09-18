#ifndef _PLAYER_H_
    #define _PLAYER_H_
 
#include "Entity.h"
 
class Player : public Entity {
	private:
		// position to respawn on death
		float _respawnX;
		float _respawnY;

	public:
        Player();

		void Spawn(float posX, float posY);
 
        bool OnLoad(char* file, int width, int height, int maxFrames);
 
        void OnAnimate();
 
        void OnCollision(Entity* entity);

		void OnDie();
};
 
#endif