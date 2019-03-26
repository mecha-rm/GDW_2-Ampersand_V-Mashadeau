// used for storing ifnormation on the weapons the player uses
#pragma once
#include "entities/Inactive.h"

namespace entity
{
	class Weapon : public Inactive
	{
	public:
		
		Weapon(unsigned int WIN);
		~Weapon();

		// gets the weapon identification number
		unsigned int getWIN() const;

		// gets the damage the entity does.
		float getDamage() const;

		void update(float deltaTime);


	private:
		void createWeapon(unsigned int WIN); // creates a weapon with pre-set values

		// sets the damage of the weapon. It cannot be equal to or below 0. If a value below 0 is passed, then it is set to 1.0F;
		void setDamage(float damage);

		magic::MagicTypes * magic; // the magic type of the weapon.

		float damage = 1.0F;

	protected:

		unsigned int WIN; // the weapon identification number

		
	};
}


