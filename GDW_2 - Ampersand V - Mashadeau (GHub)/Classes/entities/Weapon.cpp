#include "entities/Weapon.h"



entity::Weapon::Weapon(unsigned int WIN) : Inactive() {}


entity::Weapon::~Weapon() {}

// returns the weapon identification number
unsigned int entity::Weapon::getWIN() { return WIN; }

// creates a weapon based on preset values.
void entity::Weapon::createWeapon(unsigned int WIN)
{
	sprite->setGlobalZOrder(4.0F); // all weapons should have a global z order of 4.0F.
	sprite->setTag(weapon);

	// you would use this to determine which weapon to use. A default weapon should be made for weapons that do not have a corresponding number yet.
	switch (WIN)
	{
	default:
		this->WIN = 0;
	}
}


