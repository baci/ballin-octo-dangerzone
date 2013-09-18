#include "MainGame.h"

void MainGame::OnLoop()
{
	GameTimer::FPSControl.OnLoop();
	
	for(uint16_t i=0; i<Entity::EntityList.size(); i++)
	{
		if(!Entity::EntityList[i]) continue;

		Entity::EntityList[i]->OnLoop();
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
}
