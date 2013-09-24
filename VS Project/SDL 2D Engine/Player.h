#ifndef _PLAYER_H_
    #define _PLAYER_H_
 
#include <vector>
#include "Entity.h"
 
class Player : public Entity {
	public:
        Player();

		bool Load(char* file, int width, int height, int maxFrames);

		void Update();
 
        void Animate();
 
        void OnEntityCollision(Entity* entity);

		void Die();
};
 
#endif