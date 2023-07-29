#include "Entity.h"

void Entity::destroy()
{
	if (markedForDeath_) delete this;
}