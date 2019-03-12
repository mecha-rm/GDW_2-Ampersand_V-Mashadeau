#pragma once
#include "entities/Active.h"
#include "entities/Weapon.h"

namespace entity
{
	class Player : public Active
	{
	public:
		// default player image, default position of (0.0F, 0.0F), and the amount of force that's applied when a button is pressed.
		// for the player, moveForce.x will be applied when horizontal movement is activated, and moveForce.y will be applied when vertical movement is requested.
		Player();
		~Player();

		void update(float deltaTime);

		bool cancelUp = false;
		bool cancelDown = false;
		bool cancelLeft = false;
		bool cancelRight = false;

	private:

		std::vector<entity::Weapon *> weapons; // saves all of the weapons the player has.

	protected:
	};
}


