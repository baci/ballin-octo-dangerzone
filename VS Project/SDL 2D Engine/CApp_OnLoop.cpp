#include "CApp.h"

void CApp::OnLoop()
{
	CFPS::FPSControl.OnLoop();
	
	for(uint16_t i=0; i<CEntity::EntityList.size(); i++)
	{
		if(!CEntity::EntityList[i]) continue;

		CEntity::EntityList[i]->OnLoop();
	}

	// handle collision events
	for(uint16_t i=0; i<CEntityCol::entityColList.size(); i++)
	{
		CEntity* entityA = CEntityCol::entityColList[i].entityA;
		CEntity* entityB = CEntityCol::entityColList[i].entityB;

		if(entityA == NULL || entityB == NULL) continue;

		// call 2nd only if desired (timesaving)
		if(entityA->OnCollision(entityB))
			entityB->OnCollision(entityA);
	}
	CEntityCol::entityColList.clear();
}
