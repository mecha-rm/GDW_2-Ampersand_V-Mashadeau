#include "entities/Weapon.h"



entity::Weapon::Weapon(unsigned int WIN, entity::Entity * owner) : Inactive(), owner(owner) { createWeapon(WIN); }


entity::Weapon::~Weapon() {}

// returns the weapon identification number
unsigned int entity::Weapon::getWIN() const { return WIN; }


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
		setTexture("images/weapons/WIN_000.png");
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
		setTextureRect(frameSize);

		setMagicType(magic::null);
		setDamage(5.0F);
	
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(152.0F, 63.0F), 63, 68, CLR_ATK));
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(187.0F, 71.0F), 37, 89, CLR_ATK));
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(167.0F, 130.0F), 53, 68, CLR_ATK));

		owner->getSprite()->addChild(sprite); // the sprite's positon won't be saved unless this is done. This is just to ensure that the code doesn't crash from trying to get the sprite's position.
		sprite->setVisible(false);
		break;
	}

	
	for (int i = 0; i < collisionBodies.size(); i++)
	{
		owner->getSprite()->addChild(collisionBodies.at(i)->getPrimitive()); // adds the drawNode to the owner's sprite.
		// owner->addCollisionBody(collisionBodies.at(i)); // adds the collision body to the owner's vector.
	}
	
	disableCollisionBodies(); // disables the collision bodies for the weapon.
}


// sets the damage done by the wepaon
void entity::Weapon::setDamage(float damage) { this->damage = (damage <= 0.0F) ? 1.0F : damage; }

// gets the damage done by the weapon
float entity::Weapon::getDamage() const { return damage; }

// sets the owner of the weapon.
void entity::Weapon::setOwner(entity::Entity * newOwner)
{
	if (newOwner == nullptr)
		return;

	for (int i = 0; i < collisionBodies.size(); i++) // removes the primitives from the old owner.
	{
		collisionBodies[i]->getPrimitive()->removeFromParent();
		owner->removeCollisionBody(collisionBodies.at(i)); // removes it from the 
	}
	owner = newOwner;

	for (int i = 0; i < collisionBodies.size(); i++) // adds the collision bodies to their new owner.
	{
		owner->getSprite()->addChild(collisionBodies.at(i)->getPrimitive());
		owner->addCollisionBody(collisionBodies.at(i));
	}

	// disableCollisionBodies(); // turns off the weapon collision bodies so that they aren't active when they shouldn't be.
}

// returns the owner of the weapon.
entity::Entity * entity::Weapon::getOwner() const { return owner; }

// returns 'true' if the entity has an owner, i.e. 'owner' is not a nullptr.
bool entity::Weapon::hasOwner() { return !(owner == nullptr); }

// the update loop
void entity::Weapon::update(float deltaTime)
{
	Inactive::update(deltaTime); // caused crashing.
}

