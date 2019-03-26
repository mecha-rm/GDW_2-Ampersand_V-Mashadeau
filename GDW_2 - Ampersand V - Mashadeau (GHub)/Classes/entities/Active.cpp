#include "entities/Active.h"


entity::Active::Active(std::string texture) : entity::Entity(texture) {}

entity::Active::~Active() {}

// gets the health of the active entity.
float entity::Active::getHealth() const { return health; }

// sets the health of hte active entity.
void entity::Active::setHealth(float health)
{
	// if the health being passed is negative, then the entity's health is set to 0.
	(health >= 0.0F) ? this->health = health : this->health = 0.0F;
}

// returns the active entity's maximum health
float entity::Active::getMaxHealth() const { return MAX_HEALTH; }

// sets the entity's maximum health
void entity::Active::setMaxHealth(float maxHealth)
{
	// if the  maxHealth being passed is less than or equal to 0, then it is set to 1.0F.
	(maxHealth > 0.0F) ? this->MAX_HEALTH = maxHealth : this->MAX_HEALTH = 1.0F;
}

// returns the attack strength of the enemy
float entity::Active::getAttackPower() const { return attackPower; }

// sets the attack strength of the enemy
void entity::Active::setAttackPower(float attackPower)
{
	// if the attack power passed is negative, it's just set to 0.
	this->attackPower = (attackPower > 0.0F) ? attackPower : 0.0F;
}

// gets the movement force applied to the entity when it moves
Vec2 entity::Active::getMoveForce() const { return moveForce; }

// returns the movement force that gets applied on the x-axis
float entity::Active::getMoveForceX() const { return moveForce.x; }

// returns the movement force that gets applied on the y-axis
float entity::Active::getMoveForceY() const { return moveForce.y; }

// adds 'move force' to the entity's force for movement for the upcoming update
void entity::Active::addMoveForce() { addForce(moveForce);  }

// adds 'move force' to the entity's force for movement for the upcoming update (x-axis only)
void entity::Active::addMoveForceX() { addForce(moveForce.x, 0.0F); }

// adds 'move force' to the entity's force for movement for the upcoming update (y-axis only)
void entity::Active::addMoveForceY() { addForce(0.0F, moveForce.y); }

// sets the amount of force applied when the entity moves.
void entity::Active::setMoveForce(Vec2 moveForce) { this->moveForce = moveForce; }

// adds the jump force to the active entity.
void entity::Active::addJumpForce() { addForce(Vec2(0.0F, jump)); }

// the entity has gotten hit, so it should now be invincible.
void entity::Active::gotHit() 
{
	invincible = true;
	setOpacity(0.5F); // makes the sprite transparent to convey it's in its invincibility period.
}

// checks to see if the entity is invincible
bool entity::Active::getInvincible() { return invincible; }


// the update loop for active entities
void entity::Active::update(float deltaTime)
{
	if (invincible) // if the entity is currently invincible.
	{
		inviTime+= deltaTime; // adds to the invincibility timer to tell how long the entity has been invincible for.
		
		(getOpacity() < 1.0F) ? setOpacity(1.0F) : setOpacity(0.5F);

		if (inviTime >= inviTimeMax)
		{
			setOpacity(1.0F); // makes the sprite completely opaque.
			inviTime = 0.0F;
			invincible = false;
		}
	}

	Entity::update(deltaTime); // calls the entity update loop.
}