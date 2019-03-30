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

		/*
		Animations:
			0) static (no animation)
			1) spawn
			2) idle
			3) death
			4) run
			5) jump
			6) attack 1
		*/
		void runAction(unsigned int ani);

		// uses the current weapon.
		// void useWeapon();

		// gets weapon 1
		entity::Weapon * getWeapon1() const;

		// gets weapon 2
		entity::Weapon * getWeapon2() const;

		// gets weapon 3
		entity::Weapon * getWeapon3() const;
		
		// gets the current weapon equipped
		entity::Weapon * getCurrentWeapon() const;

		void update(float deltaTime);

		bool cancelUp = false;
		bool cancelDown = false;
		bool cancelLeft = false;
		bool cancelRight = false;

	private:

		std::vector<entity::Weapon *> weapons; // saves all of the weapons the player has.

		entity::Weapon * currentWeapon = nullptr;

		entity::Weapon * weapon1 = nullptr;
		entity::Weapon * weapon2 = nullptr;
		entity::Weapon * weapon3 = nullptr;

		bool usingWeapon = false;

	protected:
	};
}


