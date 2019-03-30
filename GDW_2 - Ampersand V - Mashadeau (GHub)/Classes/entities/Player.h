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

		// gets the magic power of the player
		float getMagicPower();

		// adds to the magic power of the player. If this goes beyond the maximum magic power, it's set to max. If it goes below 0, it's set to 0.
		void addMagicPower(float mp);

		// adds to the maximum magic power, and changes the current magic power (only if 'changeCurrent' is true)
		void addMagicPowerMax(float mpm, bool changeCurrent);

		void update(float deltaTime);

		bool cancelUp = false;
		bool cancelDown = false;
		bool cancelLeft = false;
		bool cancelRight = false;

	private:

		

		std::vector<entity::Weapon *> weapons; // saves all of the weapons the player has.

		entity::Weapon * currentWeapon = nullptr; // current weapon equipped

		entity::Weapon * weapon1 = nullptr;
		entity::Weapon * weapon2 = nullptr;
		entity::Weapon * weapon3 = nullptr;

		bool usingWeapon = false;

		float magicPower = 0.0F;
		float magicPowerMax = 0.0F;

	protected:

		// sets the magic power. If an mp less than 0 is given, then it's set to 0. If an mp greater than the max is given, then it's set to the max.
		void setMagicPower(float mp);

		// sets the maximum magic power, which cannot be 0. The current amount of magic is adjusted accordingly.
		// if 'changeCurrent' is true, then the current amount of magic power is changed accordingly.
		void setMagicPowerMax(float mpm, bool changeCurrent);

	};
}


