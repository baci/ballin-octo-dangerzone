#include "MainGame.h"

void MainGame::Update()
{
	GameTimer::FPSControl.Update();
	
	// handle entities
	for(uint16_t i=0; i<Entity::currentEntities.size(); i++)
	{
		Entity *curEntity = Entity::currentEntities[i];
		if(!curEntity) continue;

		if(curEntity->state == DEAD && curEntity->deathAnimation != NULL)
			curEntity->deathAnimation->Update();
		else
			curEntity->Update();
	}

	// handle entity collision events
	for(uint16_t i=0; i<EntityCollision::curCollisions.size(); i++)
	{
		Entity* eA = EntityCollision::curCollisions[i].eA;
		Entity* eB = EntityCollision::curCollisions[i].eB;

		if(eA == NULL || eB == NULL) continue;

		eA->OnEntityCollision(eB);
		eB->OnEntityCollision(eA);
	}
	EntityCollision::curCollisions.clear();

	// handle camera
	Camera::Instance.Update();
}
