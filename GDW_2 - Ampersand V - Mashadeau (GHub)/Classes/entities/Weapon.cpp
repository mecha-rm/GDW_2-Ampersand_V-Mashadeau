#include "entities/Weapon.h"



entity::Weapon::Weapon(unsigned int WIN) : Inactive() {}


// entity::Weapon::~Weapon() {}

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

	// WIN 000
	case 0:
	default:
		this->WIN = 0;

		setName("Lite Dagger");
		setDescription("A weak dagger that the player starts with");
		magic = new magic::MagicTypes(magic::magic_t(0));
		damage = 3.0F;
	
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(152.0F, 63.0F), 63, 68, CLR_ATK));
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(187.0F, 71.0F), 37, 89, CLR_ATK));
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(167.0F, 130.0F), 53, 68, CLR_ATK));

		break;
	}
}

// the update loop
void entity::Weapon::update(float deltaTime)
{
}

