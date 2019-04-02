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
			6) attack
		*/
		void runAction(unsigned int ani);

		// gets weapon 1
		entity::Weapon * getWeapon1() const;

		// sets weapon 1; fails if the owner isn't the player.
		void setWeapon1(entity::Weapon * wpn);

		// gets weapon 2
		entity::Weapon * getWeapon2() const;

		// sets weapon 2; fails if the owner isn't the player.
		void setWeapon2(entity::Weapon * wpn);

		// gets weapon 3
		entity::Weapon * getWeapon3() const;

		// sets weapon 3; fails if the owner isn't the player.
		void setWeapon3(entity::Weapon * wpn);
		
		// gets the current weapon equipped
		entity::Weapon * getCurrentWeapon() const;

		// sets current weapon; fails if the owner isn't the player.
		void setCurrentWeapon(entity::Weapon * wpn);

		/*
		// gets the weapon based on a provided number. If the number is out of bounds, then a nullptr is returned.
		 * [0] = current weapon
		 * [1] = weapon 1
		 * [2] = weapon 2
		 * [3] = weapon 3
		*/
		entity::Weapon * getWeapon(unsigned short int weapon);

		/*
		// sets the weapon based on a provided number. If the number is out of bounds or the weapon does not already belong to the player, a nullptr is returned.
		 * [0] = current weapon
		 * [1] = weapon 1
		 * [2] = weapon 2
		 * [3] = weapon 3
		*/
		void setWeapon(entity::Weapon * wpn, unsigned int index);
		
		/*
		 * Switches the weapon. It can only be a value from 1 - 3
		 * [1]: switch to weapon 1
		 * [2]: switch to weapon 2
		 * [3]: switch to weapon 3
		*/
		void switchWeapon(short int weapon);

		// gives the player a weapon, returning the WIN of the weapon replaced. If no weapon was replaced, then a -1 is returned.
		int giveWeapon(unsigned int WIN);

		// removes a weapon from the player. Returns the 'WIN' number of the removed weapon.
		// [0] = current, [1] = weapon 1, [2] = weapon 2, [3] = weapon 3
		int removeWeapon(unsigned int index);

		// has the player use their weapon.
		void useWeapon();

		// adds to the player's maximum health.
		void addHealth(float hp);

		// adds to the player's maximum health. Use 'changeCurrent' if this should adjust the player's current health as well.
		void addMaxHealth(float hp, bool changeCurrent);

		// gets the magic power of the player
		float getMagicPower();

		// sets the magic power. If an mp less than 0 is given, then it's set to 0. If an mp greater than the max is given, then it's set to the max.
		void setMagicPower(float mp);

		// gets the maximum magic power the player has.
		float getMagicPowerMax();

		// sets the maximum magic power, which cannot be 0. The current amount of magic is adjusted accordingly.
		// if 'changeCurrent' is true, then the current amount of magic power is changed accordingly.
		void setMagicPowerMax(float mpm, bool changeCurrent);

		// adds to the magic power of the player. If this goes beyond the maximum magic power, it's set to max. If it goes below 0, it's set to 0.
		void addMagicPower(float mp);

		// adds to the maximum magic power, and changes the current magic power (only if 'changeCurrent' is true)
		void addMagicPowerMax(float mpm, bool changeCurrent);

		// called when the player is hit.
		void gotHit();

		void update(float deltaTime);

		// becomes 'true' to tell the program that the player wishes to move in a certain direction.
		bool moveUp = false;
		bool moveDown = false;
		bool moveLeft = false;
		bool moveRight = false;
		bool jump = false;

		// cancelers for moving in certain directions.
		bool cancelUp = false;
		bool cancelDown = false;
		bool cancelLeft = false;
		bool cancelRight = false;

	private:

		// gives the player a new weapon. If the player has all of their weapon slots filled, it replaces the current weapon.
		// the weapon that got prepalced is returned. If no weapon was replaced, then a nullptr is returned.
		// gives the player a weapon, returning the WIN of the weapon replaced. If no weapon was replaced, then a -1 is returned.
		int giveWeapon(entity::Weapon * newWeapon);

		std::vector<entity::Weapon *> weapons; // saves all of the weapons the player has.

		// a total of 4 weapons can be held at a time (1 current weapon, and the rest our 'in the backpack' if you will)
		entity::Weapon * currentWeapon = nullptr; // current weapon equipped

		entity::Weapon * weapon1 = nullptr;
		entity::Weapon * weapon2 = nullptr;
		entity::Weapon * weapon3 = nullptr;

		bool usingWeapon = false;

		float magicPower = 0.0F;
		float magicPowerMax = 0.0F;

		bool hpRefill = true; // if true, restore health periodically
		bool mpRefill = true; // if false, restore mp periodically.

		// bool hpRegen = false; // becomes 'true' when health should regenerate.
		float hpAdd = 5.0F; // adds to the player's HP when the timer runs out.
		float hprTimer = 0.0F; // counts down to 0 from hprTimerMax. When it hits 0, the playe gets back some health.
		float hprTimerMax = 5.0F; // how long it takes for the player's health to regenerate.

		// bool mpRegen = false; // becomes 'true' when magic should regenerate.
		float mpAdd = 5.0F; // adds to the player's MP when the timer runs out.
		float mprTimer = 0.0F; // counts down to 0 from mprTimerMax. When it hits 0, the playe gets back some health.
		float mprTimerMax = 5.0F; // how long it takes for the player's magic to regenerate.

	protected:

	};
}


