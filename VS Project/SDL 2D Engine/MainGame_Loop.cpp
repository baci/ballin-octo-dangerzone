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

	// handle collision events
	for(uint16_t i=0; i<EntityCol::entityColList.size(); i++)
	{
		Entity* entityA = EntityCol::entityColList[i].entityA;
		Entity* entityB = EntityCol::entityColList[i].entityB;

		if(entityA == NULL || entityB == NULL) continue;

		entityA->OnCollision(entityB);
		entityB->OnCollision(entityA);
	}
	EntityCol::entityColList.clear();

	// handle camera
	Camera::Instance.Update();
}
