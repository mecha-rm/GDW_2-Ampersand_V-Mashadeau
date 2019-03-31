#pragma once
// used for projectiles made by the player.

#include "entities/Weapon.h"

namespace entity
{
	// creates a projectile.
	class Projectile : public entity::Weapon
	{
	public:
		Projectile(int WIN, entity::Entity * owner);
		~Projectile();

		// gets force applied to make the weapon move. Only non-zero value for projectiles.
		Vec2 getMoveForce() const;

		// gets the move force, rotated to give the proper direction.
		Vec2 getRotatedMoveForce();

		// gets the speed force of the projectile.
		float getSpeed() const;

		// sets the speed of the projectile. This cannot be at or below 0.
		// if you want to change the direction of the projectile, change the 'rotation factor' and turn on 'rotateAcceleration'
		void setSpeed(float spd);

		// updates the projectile.
		void update(float deltaTime);

	private:
		// force applied to make the weapon move. Only used for projectiles.
		void setMoveForce(Vec2 newMoveForce);

		Vec2 moveForce = Vec2(); // movement force

		float speed = 1.0F; // the 'speed' of the projectile.

	protected:

		// this is called by the main weapon class to initialize the projectile.
		void createWeapon(unsigned int WIN) override;

	};
}