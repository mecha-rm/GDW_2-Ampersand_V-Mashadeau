#include "Item.h"


// class for making items.
entity::Item::Item(unsigned int IIN) : Inactive() { createItem(IIN); }


entity::Item::~Item() {}

// returns the item identification number
unsigned int entity::Item::getIIN() { return IIN; }

// updates the item
void entity::Item::update(float deltaTime)
{
	entity::Inactive::update(deltaTime);
}

// creates the item based on a passed IIN
void entity::Item::createItem(unsigned int IIN)
{
	sprite->setGlobalZOrder(5.0F); // all items should have a global z order of 4.0F.
	sprite->setTag(item);

// you would use this to determine which weapon to use. A default item should be made for weapons that do not have a corresponding number yet.
	switch (IIN)
	{
	default:
		this->IIN = 0;
	}
}
