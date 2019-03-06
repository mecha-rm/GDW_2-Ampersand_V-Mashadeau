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
		Player(std::string texture = "images/PLR_000.png", Vec2 moveForce = Vec2(200.0F, 200.0F), float jump = 10000.0F);
		~Player();

		void update(float deltaTime);

	private:

		std::vector<entity::Weapon *> weapons; // saves all of the weapons the player has.

	protected:
	};
}


