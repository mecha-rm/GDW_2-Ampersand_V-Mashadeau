#pragma once
// used for projectiles made by the player.

#include "entities/Weapon.h"
class Projectile : public entity::Weapon
{
public:
	/*
	* 0 (default):
	* 1 : 
	*
	*/

	Projectile(int WIN, entity::Entity * owner);
	~Projectile();
	
	
	

private:

protected:

	void createWeapon(unsigned int WIN) override
	{

	}

};

