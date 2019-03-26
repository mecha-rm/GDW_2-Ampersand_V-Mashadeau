#include "entities/Inactive.h"



entity::Inactive::Inactive() : entity::Entity()
{
}


entity::Inactive::~Inactive()
{
}

// update loop
void entity::Inactive::update(float deltaTime)
{
	entity::Entity::update(deltaTime);
}
