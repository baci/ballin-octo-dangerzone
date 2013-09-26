#include "Entity.h"

std::vector<EntityCollision> EntityCollision::curCollisions;

EntityCollision::EntityCollision() 
{
    eA = NULL;
    eB = NULL;
}