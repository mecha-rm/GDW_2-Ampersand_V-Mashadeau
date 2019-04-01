#include "entities/Projectile.h"

// calls the protected constructor for the weapon.
entity::Projectile::Projectile(int WIN, entity::Entity * owner) : Weapon(owner) { createWeapon(WIN); }


entity::Projectile::~Projectile() {}

void entity::Projectile::createWeapon(unsigned int WIN) // creates the projectile.
{
	setDamage(1.0F); // projectiles should have their damage changed based on the weapon used, but this is a default value.

	this->WIN = WIN;

	switch(this->WIN)
	{
		case 10: // Null Sphere Small (default)
		default:
			// this->WIN = 10;
			// break;
		case 11: // Null Sphere Medium
		case 12:
			this->WIN = 11;
			setName("Null Sphere Medium");
			setDescription("A null energy ball");
			setTexture("images/weapons/WIN_011.png");
			frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
			setTextureRect(frameSize);
			
			setMagicType(magic::null);
			setDamage(5.0F);
			setMagicUsage(1.0F);
			
			collisionBodies.push_back(new OOP::PrimitiveCircle(Vec2(128.0F, 128.0F), 50.0F, CLR_ATK));
			moveForce = Vec2(100.0F, 0.0F);

			break;

		case 13: // Shadow Sphere Small
		case 14: // Shadow Sphere Medium
		case 15: // Shadow Sphere Large
			this->WIN = 14;
			setName("Shadow Sphere Medium");
			setDescription("A shadow energy ball");
			setTexture("images/weapons/WIN_014.png");
			frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
			setTextureRect(frameSize);

			setMagicType(magic::shadow);
			setDamage(5.0F);
			setMagicUsage(1.0F);

			collisionBodies.push_back(new OOP::PrimitiveCircle(Vec2(128.0F, 128.0F), 50.0F, CLR_ATK));
			moveForce = Vec2(100.0F, 0.0F);

			break;

		case 16: // Fire Sphere Small
		case 17: // Fire Sphere Medium
		case 18: // Fire Sphere Large
			this->WIN = 17;
			break;

		case 19: // Water Sphere Small
		case 20: // Water Sphere Medium
		case 21: // Water Sphere Large
			this->WIN = 20;
			break;

		case 22: // Earth Sphere Small
		case 23: // Earth Sphere Medium
		case 24: // Earth Sphere Large
			this->WIN = 23;
			break;

		case 25: // Air Sphere Small
		case 26: // Air Sphere Medium
		case 27: // Air Sphere Large
			this->WIN = 26;

			break;
	
	}

	// adds the primitives to the owner.
	addPrimitivesToOwner(true, false);
}

// gets the movement force of the weapon. If not applicable, it will just be 0.
Vec2 entity::Projectile::getMoveForce() const { return moveForce; }

// sets the movement force of te weapon.
void entity::Projectile::setMoveForce(Vec2 newMoveForce) { moveForce = newMoveForce; }

// gets the movement force of the projectile, rotated.
Vec2 entity::Projectile::getRotatedMoveForce() { return umath::rotate(moveForce, getRotationInDegrees(), true); }

// gets the speed of the projectile.
float entity::Projectile::getSpeed() const { return speed; }

// sets the speed of the projectile. Cannot be negative.
void entity::Projectile::setSpeed(float spd) { speed = (spd > 0.0F) ? spd : 1.0F; }

// the update loop for the projectile.
void entity::Projectile::update(float deltaTime)
{
	addForce(moveForce * speed); // for projectiles, a movement force exists. This adds said movement force.

	Weapon::update(deltaTime);
}
