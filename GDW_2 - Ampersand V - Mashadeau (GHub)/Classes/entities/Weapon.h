// used for storing ifnormation on the weapons the player uses
#pragma once
#include "entities/Inactive.h"

namespace entity
{
	class Weapon : public Inactive
	{
	public:
		
		// creates a weapon, and adds it to an entity that is considered its owner.
		Weapon(unsigned int WIN, entity::Entity * owner);
		~Weapon();

		// gets the weapon identification number
		unsigned int getWIN() const;

		// gets the damage the entity does.
		float getDamage() const;

		// gets the amount of magic usage of the weapon.
		float getMagicUsage() const;

		// sets the owner this weapon is attached to. It's who HAS the weapon.
		void setOwner(entity::Entity * newOwner);

		// gets the owner of this weapon. It's who HAS the weapon.
		entity::Entity * getOwner() const;

		// returns 'true' if this weapon has an owner (i.e. 'owner' is not a nullptr), false if it doesn't.
		bool hasOwner();
		
		// gets force applied to make the weapon move. Only non-zero value for projectiles.
		Vec2 getMoveForce();

		// force applied to make the weapon move. Only used for projectiles.
		void setMoveForce(Vec2 newMoveForce);

		// the update loop.
		void update(float deltaTime);

		Vec2 moveForce = Vec2();

	private:
		// sets the damage of the weapon. It cannot be equal to or below 0. If a value below 0 is passed, then it is set to 1.0F;
		void setDamage(float damage);

		void setMagicUsage(float mgu);

		entity::Entity * owner = nullptr; // the entity that has this weapon.
		
		float damage = 1.0F; // how much damage the weapon does.

		float magicUsage = 0.0F; // how much magic the weapon uses

	protected:
		virtual void createWeapon(unsigned int WIN); // creates a weapon with pre-set values

		unsigned int WIN; // the weapon identification number

		
	};
}


