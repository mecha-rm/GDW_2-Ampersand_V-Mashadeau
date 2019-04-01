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

		/*
		 The type of the weapon is as follows:
			* [0]: unkown (shouldn't be used).
			* [1]: physical attack (short-range)
			* [2]: special attack (long-range)
			* [3]: non-offensive attack
		 */
		int getType() const;

		// gets the amount of magic usage of the weapon.
		float getMagicUsage() const;

		// sets the owner this weapon is attached to. It's who HAS the weapon.
		void setOwner(entity::Entity * newOwner);

		// gets the owner of this weapon. It's who HAS the weapon.
		entity::Entity * getOwner() const;

		// returns 'true' if this weapon has an owner (i.e. 'owner' is not a nullptr), false if it doesn't.
		bool hasOwner();

		// gets all of the weapons on top of a single node, positioned appr
		//vgetAsSingleNode();

		// called when a weapon is used. If the weapon creates a projectile, then a projectile vector will be sent.
		// if it's of size '0', then no projectiles were generated. DO NOT USE YET.
		// std::vector<entity::Projectile *> & useWeapon();

		// the update loop.
		void update(float deltaTime);

	private:
		entity::Entity * owner = nullptr; // the entity that has this weapon.
		
		float damage = 1.0F; // how much damage the weapon does.

		float magicUsage = 0.0F; // how much magic the weapon uses

		// used to determine what kind of animation to use. 
		int type = 0;

	protected:
		// this is a 'protected' constructor. This is for weapons in subclasses that shouldn't call the 'createWeapon' function in the Weapon class.
		Weapon(entity::Entity * owner);
		
		virtual void createWeapon(unsigned int WIN); // creates a weapon with pre-set values

		// adds all of the collision bodies to the owner. If 'changeActive' is true, then the 'Active' parameter of the bodies is changed. 
		// If 'activeBodies' is true, then the bodies are made active. If 'activeBodies' is false, then the bodies are deactived.
		// if changeActive is 'false', then the value of 'activeBodies' is irrelevant.
		void addPrimitivesToOwner(bool changeActive = true, bool activeBodies = false);

		// sets the type of the weapon. If a number from 1 - 3 is given, it's set to 0.
		/*
		 The type of the weapon is as follows:
			* [0]: unkown/unapplicable (shouldn't be used).
			* [1]: physical attack (short-range)
			* [2]: special attack (long-range)
			* [3]: non-offensive attack
		 */
		void setType(int newType);

		// sets the damage of the weapon. It cannot be equal to or below 0. If a value below 0 is passed, then it is set to 1.0F;
		void setDamage(float damage);

		void setMagicUsage(float mgu);


		unsigned int WIN; // the weapon identification number

		
	};
}


