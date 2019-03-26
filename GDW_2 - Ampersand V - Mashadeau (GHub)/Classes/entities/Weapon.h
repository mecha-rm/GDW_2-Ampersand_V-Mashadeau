// used for storing ifnormation on the weapons the player uses
#pragma once
#include "entities/Inactive.h"

namespace entity
{
	class Weapon : public Inactive
	{
	public:
		
		Weapon(unsigned int WIN);
		// ~Weapon();

		// gets the weapon identification number
		unsigned int getWIN();

		void update(float deltaTime);


	private:

		magic::MagicTypes * magic; // the magic type of the weapon.

		float damage = 1.0F;

	protected:

		void createWeapon(unsigned int WIN); // creates a weapon with pre-set values

		unsigned int WIN; // the weapon identification number

		
	};
}


