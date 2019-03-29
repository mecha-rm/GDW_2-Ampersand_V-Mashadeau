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

		// sets the owner this weapon is attached to. It's who HAS the weapon.
		void setOwner(entity::Entity * newOwner);

		// gets the owner of this weapon. It's who HAS the weapon.
		entity::Entity * getOwner() const;

		// returns 'true' if this weapon has an owner (i.e. 'owner' is not a nullptr), false if it doesn't.
		bool hasOwner();

		void update(float deltaTime);


	private:
		void createWeapon(unsigned int WIN); // creates a weapon with pre-set values

		// sets the damage of the weapon. It cannot be equal to or below 0. If a value below 0 is passed, then it is set to 1.0F;
		void setDamage(float damage);

		entity::Entity * owner = nullptr; // the entity that has this weapon.
		float damage = 1.0F;

	protected:

		unsigned int WIN; // the weapon identification number

		
	};
}


