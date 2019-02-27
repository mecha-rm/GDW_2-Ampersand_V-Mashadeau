// used for storing ifnormation on the weapons the player uses
#pragma once
#include "entities/Entity.h"

namespace entity
{
	class Weapon : public Entity
	{
	public:
		
		Weapon(unsigned int WIN);
		~Weapon();

		// gets the weapon identification number
		unsigned int getWIN();

	private:

	protected:

		void createWeapon(unsigned int WIN); // creates a weapon with pre-set values

		unsigned int WIN; // the weapon identification number
	};
}

