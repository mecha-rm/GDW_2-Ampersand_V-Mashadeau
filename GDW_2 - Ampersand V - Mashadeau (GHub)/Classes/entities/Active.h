#pragma once
#include "entities/Entity.h"

namespace entity
{
	class Active : public Entity
	{
	public:
		Active(std::string texture = "");
		~Active();
		
		// sets the entity's health
		void setHealth(float health);

		// gets the entity's health
		float getHealth() const;

		// gets the entity's maximum health;
		float getMaxHealth() const;
		
		// tells the program that the active entity has taken damage. Invincibility frames are started when this occures.
		virtual void gotHit();

		// if true, the entity is currently invincible.
		bool getInvincible();

		// gets the entity's attack power
		float getAttackPower() const;

		// gets the amount of force applied when the active entity moves.
		Vec2 getMoveForce() const;
		// gets the amount of force applied when the active entity moves (x-axis only)
		float getMoveForceX() const;
		// gets the amount of force applied when the active entity moves (y-axis only)
		float getMoveForceY() const;

		// adds 'move force' to the entity's force for movement on the upcoming update
		void addMoveForce();
		// adds only the 'X' value of moveForce to the force of the active entity
		void addMoveForceX();
		// adds only the 'Y' value of moveForce to the force of the active entity
		void addMoveForceY();

		// adds the force of the active entity's jump.
		void addJumpForce();

		// the update loop for the active entity.
		void update(float deltaTime);

	private:
		float health; // the entity's health
		
		float MAX_HEALTH; // the entity's maximum health
		
		float attackPower; // the entity's attack power

		bool invincible = false; // tells whether an entity is invincible or not.
		

	protected:
		// sets the maximum health of the entity
		void setMaxHealth(float maxHealth);

		// sets the entity's attack power
		void setAttackPower(float attackPower);

		// sets the amount of force applied when the entity moves.
		void setMoveForce(Vec2 moveForce);

		Vec2 moveForce; // the amount of force applied when the entity moves.
		float jump = 0.0F; // the fore applied when an active entity jumps

		float inviTime = 0; // the amount of time since the entity has taken damage
		float inviTimeMax = 0; // the amount of time an entity stays invincible for after getting hit.
	};
}


