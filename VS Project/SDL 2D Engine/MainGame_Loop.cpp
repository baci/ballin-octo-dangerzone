#include "MainGame.h"

void MainGame::Update()
{
	GameTimer::FPSControl.OnLoop();
	
	// handle entities
	for(uint16_t i=0; i<Entity::currentEntities.size(); i++)
	{
		if(!Entity::currentEntities[i]) continue;

		Entity::currentEntities[i]->Update();
	}

	// handle entity collision events
	for(uint16_t i=0; i<EntityCol::entityColList.size(); i++)
	{
		Entity* entityA = EntityCol::entityColList[i].entityA;
		Entity* entityB = EntityCol::entityColList[i].entityB;

		if(entityA == NULL || entityB == NULL) continue;

		entityA->OnEntityCollision(entityB);
		entityB->OnEntityCollision(entityA);
	}
	EntityCol::entityColList.clear();

	// handle camera
	Camera::Instance.Update();
}
