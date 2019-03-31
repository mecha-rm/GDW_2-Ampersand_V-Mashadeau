#include "entities/Weapon.h"
#include "entities/Projectile.h"


entity::Weapon::Weapon(unsigned int WIN, entity::Entity * owner) : Inactive(), owner(owner) { createWeapon(WIN); }

// this is a 'PROTECTED' constructor that's called by the projectile class since it has it's own 'createWeapon' function.
entity::Weapon::Weapon(entity::Entity * owner) : Inactive(), owner(owner) {};

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
	case 0: // WIN_000 (also default)
	default:
		this->WIN = 0;

		setName("Lite Dagger");
		setDescription("A weak dagger that the player starts with");
		setType(1);
		setTexture("images/weapons/WIN_000.png");
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
		setTextureRect(frameSize);

		setMagicType(magic::null);
		setDamage(5.0F);
		// setMagicUsage(10.0F);

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(152.0F, 63.0F), 63, 68, CLR_ATK));
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(187.0F, 71.0F), 37, 89, CLR_ATK));
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(167.0F, 130.0F), 53, 68, CLR_ATK));
		break;

	case 1: // staff of ice
		this->WIN = 1;
		setName("Staff of Ice");
		setDescription("A staff of ice.");
		setType(2);
		setTexture("images/weapons/WIN_001.png");
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);

		setMagicType(magic::water);
		setDamage(2.50);

		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;


	case 10: // Projectiles
	case 11:
	case 12:	
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
		*this = Projectile(WIN, owner); // creates the projectile, which has its own createWeapon() function.
		return;
		break;
	}

	owner->getSprite()->addChild(sprite); // the sprite's positon won't be saved unless this is done. This is just to ensure that the code doesn't crash from trying to get the sprite's position.
	sprite->setVisible(false);
	addPrimitivesToOwner();
	
}

// adds all the colision primitives to the owner, and chooses to either enable them, disable them, or do nothing to them.
void entity::Weapon::addPrimitivesToOwner(bool changeActive, bool activeBodies)
{
	Vector<Node *> ownerChildren = owner->getSprite()->getChildren(); // gets the children of the owner.

	for (int i = 0; i < collisionBodies.size(); i++)
	{
		for (int j = 0; j < ownerChildren.size(); j++)
		{
			// if the primitive's draw node is already attachted to the owner, it isn't attachted again.
			if (ownerChildren.at(j) == collisionBodies.at(i)->getPrimitive())
				continue;
			else
				owner->getSprite()->addChild(collisionBodies.at(i)->getPrimitive());
		}

		 // adds the drawNode to the owner's sprite.
		// owner->addCollisionBody(collisionBodies.at(i)); // adds the collision body to the owner's vector.
	}

	if (changeActive) // if the 'active' parameter should be changed.
		(activeBodies) ? enableCollisionBodies() : disableCollisionBodies(); // if 'true', then collisions are actived. If false, they're all deactivated.
}

// gets the damage done by the weapon
float entity::Weapon::getDamage() const { return damage; }

// sets the damage done by the wepaon
void entity::Weapon::setDamage(float damage) { this->damage = (damage <= 0.0F) ? 1.0F : damage; }

// sets the magic usage of the weapon. It cannot be below 0.
void entity::Weapon::setMagicUsage(float mgu)
{
	magicUsage = (mgu >= 0.0F) ? mgu : 0.0F;
}

// gets the type of the weapon.
int entity::Weapon::getType() const { return type; }

// sets the type of the weapon. It must be a number from 1 to 3.
void entity::Weapon::setType(int newType) { type = (newType >= 1 && newType <= 3) ? newType : 0; }


// gets the magic usage of the weapon.
float entity::Weapon::getMagicUsage() const { return magicUsage; }

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
	switch (WIN)
	{
	case 0:
		break;
	}

	Inactive::update(deltaTime);
}

