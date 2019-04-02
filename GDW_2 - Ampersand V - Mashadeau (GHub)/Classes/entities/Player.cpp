#include "entities/Player.h"
#include <iostream>


entity::Player::Player() : Active("images/PLR_000.png")
{
	OOP::SpriteSheetAnimation * tempAnimate = nullptr; // a temporary animation

	setName("Mashadeau"); // the player character's name
	setDescription("The shadow mage, Mashadeau!");
	frameSize = Rect(0.0F, 0.0F, 256.0F, 256.0F);

	setMagicType(magic::shadow);

	sprite->setTextureRect(Rect(0.0F + frameSize.getMaxX() * 0.0F, 0.0F + frameSize.getMaxY() * 1, frameSize.getMaxX(), frameSize.getMaxY())); // setting the area of the sprite that's used
	sprite->setGlobalZOrder(2.0F); // sets the global Z order of the player.
	sprite->setTag(player);

	// collisionShapes.push_back(new OOP::PrimitiveCircle(Vec2(0.0f, 0.0f), 29.0f));
	collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 53.0F, 185.0F, CLR_DEF));
	collisionBodies.at(0)->getPrimitive()->setGlobalZOrder(10.1F); // the z-order is now set upon initalization.
	collisionBodies.at(0)->setVisible(shapesVisible);


	// collisionShapes.push_back(new OOP::PrimitiveCapsule(Vec2(frameSize.getMidX(), frameSize.getMidY() + 185.0F / 2), Vec2(frameSize.getMidX(), frameSize.getMidY() - 185.0F / 2), 53.0F / 2, CLR_DEF));
	collisionBodies.push_back(new OOP::PrimitiveCapsule(Vec2(frameSize.getMidX(), frameSize.getMidY()), 185.0F, 53.0F / 2, 90.0F, CLR_DEF));
	collisionBodies.at(1)->getPrimitive()->setGlobalZOrder(10.1F); // the z-order is now set upon initalization.
	collisionBodies.at(1)->setVisible(shapesVisible);
	// sprite->addChild(circles.at(0)->getPrimitive());

	
	this->moveForce = Vec2(200.0F, 200.0F); // sets the amount of force that gets applied for
	
	// old, floaty physics
	// setJumpForce(14000.0F);
	// setDecelerate(Vec2(getDecelerate().x, 0.99F));
	// setMass(1.0F);
	
	// Final game gravity?
	setJumpForce(3200.0f);
	setDecelerate(Vec2(getDecelerate().x, 0.99F));
	setMass(0.5F);

	setMaxHealth(100.0F);
	setHealth(100.0F);
	inviTimeMax = 3.0F;

	setMagicPowerMax(100.0F, false);
	setMagicPower(getMagicPowerMax());

	currentWeapon = new entity::Weapon(0, this);
	// weapon1 = new entity::Weapon(1, this);
	weapons.push_back(currentWeapon);
	weapons.push_back(weapon1);
	weapons.push_back(weapon2);
	weapons.push_back(weapon3);

	// no animation (0); 1 frame
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, true, 0.25F, true);
	tempAnimate->setName("static");
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 0.0F, 0.0F + frameSize.getMaxY() * 1, frameSize.getMaxX(), frameSize.getMaxY())));
	animations.push_back(tempAnimate);

	// currentAnimation = tempAnimate;

	// idle animation (2): 5 frames
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, true, 0.2F, false, true);
	tempAnimate->setName("idle");
	tempAnimate->setTag(2);

	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 0.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 20.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 1.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 2.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 3.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 4.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));
																															 
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 3.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 3.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 2.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 1.0F, 0.0F + frameSize.getMaxY() * 1.0f, frameSize.getMaxX(), frameSize.getMaxY()), 0.0F));

	animations.push_back(tempAnimate);
	currentAnimation = tempAnimate;

	// death (3): 17 frames
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, false, 0, true, false);
	tempAnimate->setName("death");
	tempAnimate->setTag(3);

	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 0.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 1.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 2.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 3.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));

	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 4.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 5.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 6.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 7.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));

	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 8.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 9.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 10.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 11.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));


	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 12.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 13.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 14.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 15.0F, 0.0F + frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));

	animations.push_back(tempAnimate);

	// run (4): 7 frames
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, true, 0.1F, true, false); // new animation
	tempAnimate->setName("run");
	tempAnimate->setTag(4); // sets the tag

	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 0.0F, 0.0F + frameSize.getMaxY() * 3.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 1.0F, 0.0F + frameSize.getMaxY() * 3.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 2.0F, 0.0F + frameSize.getMaxY() * 3.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 3.0F, 0.0F + frameSize.getMaxY() * 3.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));

	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 4.0F, 0.0F + frameSize.getMaxY() * 3.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 5.0F, 0.0F + frameSize.getMaxY() * 3.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 6.0F, 0.0F + frameSize.getMaxY() * 3.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.0F));

	animations.push_back(tempAnimate);

	// jump(5)
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, true, 0.0F, false, false); // new animation
	tempAnimate->setName("jump");
	tempAnimate->setTag(5);

	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 0.0F, 0.0F + frameSize.getMaxY() * 4.0F, frameSize.getMaxX(), frameSize.getMaxY()), 2.0F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 1.0F, 0.0F + frameSize.getMaxY() * 4.0F, frameSize.getMaxX(), frameSize.getMaxY()), 1.5F));
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 2.0F, 0.0F + frameSize.getMaxY() * 4.0F, frameSize.getMaxX(), frameSize.getMaxY()), 2.0F));

	animations.push_back(tempAnimate);

	// attack (6):
	// tempAnimate->getFrames().at(getFrames()->)
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, false, 0.5F, true, false); // new animation
	tempAnimate->setName("attack");
	tempAnimate->setTag(6);
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 1, 0.0F + frameSize.getMaxY() * 5.0F, frameSize.getMaxX(), frameSize.getMaxY()))); // frame 1
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 2, 0.0F + frameSize.getMaxY() * 5.0F, frameSize.getMaxX(), frameSize.getMaxY()))); // frame 2
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 3, 0.0F + frameSize.getMaxY() * 5.0F, frameSize.getMaxX(), frameSize.getMaxY()))); // frame 3
	// tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX(), 0.0F + frameSize.getMaxY(), frameSize.getMaxX(), frameSize.getMaxY())));
	animations.push_back(tempAnimate);

	for (OOP::Primitive * prim : collisionBodies)
		sprite->addChild(prim->getPrimitive());
}


entity::Player::~Player() {}

// uses a specific animation.
/*
		Animations:
			0) static (no animation)
			1) spawn
			2) idle
			3) death
			4) run
			5) jump
			6) attack 1 (physical)
			7) attack 2 (specia)
			8) attack 3 (non-offensive)
*/
void entity::Player::runAction(unsigned int ani)
{
	getCurrentAnimation()->stopAnimation();
	runAnimationByTag(ani);

	if (ani == 6 || ani == 7 || ani == 8)
		currentWeapon->enableCollisionBodies();

}

// returns weapon 1
entity::Weapon * entity::Player::getWeapon1() const { return weapon1; }

// sets weapon 1
void entity::Player::setWeapon1(entity::Weapon * wpn)
{
	setWeapon(wpn, 1);
}

entity::Weapon * entity::Player::getWeapon2() const { return weapon2; }

void entity::Player::setWeapon2(entity::Weapon * wpn)
{
	setWeapon(wpn, 2);
}

entity::Weapon * entity::Player::getWeapon3() const { return weapon3; }

void entity::Player::setWeapon3(entity::Weapon * wpn)
{
	setWeapon(wpn, 3);
}

// returns the current weapon
entity::Weapon * entity::Player::getCurrentWeapon() const { return currentWeapon; }

void entity::Player::setCurrentWeapon(entity::Weapon * wpn)
{
	setWeapon(wpn, 0);
}

// gets the weapon via an provided number. Can be 0 - 3, and returns a nullptr if a value outside of this range is given.
// [0]: current, [1]: weapon 1, [2]: weapon 2, [3]: weapon 3
entity::Weapon * entity::Player::getWeapon(unsigned short int weapon)
{
	switch (weapon)
	{
	case 0:
		return currentWeapon;
		break;

	case 1:
		return weapon1;
		break;

	case 2:
		return weapon2;
		break;

	case 3:
		return weapon3;
		break;
	}

	return nullptr;
}


// sets the player's weapon.
void entity::Player::setWeapon(entity::Weapon * wpn, unsigned int index)
{
	entity::Weapon * oldWeapon = nullptr;

	switch (index)
	{
	case 0: // weapon 0
		oldWeapon = currentWeapon;
		weapons.at(index) = wpn;
		currentWeapon = wpn;
		ustd::addToVector(weapons, oldWeapon); // moves the old weapon to the back.

		break;
	case 1: // weapon 1
		oldWeapon = weapon1;
		weapons.at(index) = wpn;
		weapon1 = wpn;
		ustd::addToVector(weapons, oldWeapon); // moves the old weapon to the back.

		break;
	case 2: // weapon 2

		oldWeapon = weapon2;
		weapons.at(index) = wpn;
		weapon2 = wpn;
		ustd::addToVector(weapons, oldWeapon); // moves the old weapon to the back.

		break;
	case 3: // weapon 3
		oldWeapon = weapon3;
		weapons.at(index) = wpn;
		weapon3 = wpn;
		ustd::addToVector(weapons, oldWeapon); // moves the old weapon to the back.
	}
}

/*
 * Switches the weapon. It can only be a value from 1 - 3
 * [1]: switch to weapon 1
 * [2]: switch to weapon 2
 * [3]: switch to weapon 3
*/
void entity::Player::switchWeapon(short int weapon)
{
	entity::Weapon * tempWeapon = currentWeapon;
	int anime = getCurrentAnimation()->getTag(); // gets the tag of the current animation.

	if (tempWeapon == nullptr || getWeapon(weapon) == nullptr) // if the weapon is nullptr, then nothing happens.
		return;

	if (anime == 6 || anime == 7 || anime == 8) // if it's an attack animation, it is stopped.
	{
		getCurrentAnimation()->stopAnimation(true);
	}

	currentWeapon->disableCollisionBodies();

	// switches around the weapons.
	currentWeapon = getWeapon(weapon);
	switch (weapon)
	{
	case 1:
		weapon1 = tempWeapon;
		break;
	case 2:
		weapon2 = tempWeapon;
		break;
	case 3:
		weapon3 = tempWeapon;
		break;
	}
}

int entity::Player::giveWeapon(unsigned int WIN)
{
	if (WIN == 0) // the player cannot get another null blade
		return -1;
	else
		return giveWeapon(new entity::Weapon(WIN, this));
}

// gives the player a new weapon. If the player has all of their weapon slots filled, it replaces the current weapon.
int entity::Player::giveWeapon(entity::Weapon * newWeapon)
{
	entity::Weapon * oldWeapon; // the previous weapon.
	int WIN = -1; // the 'WIN' number of the replaced weaon.

	if (newWeapon == nullptr)
		return WIN;

	// newWeapon->setOwner(this);

	if (weapon1 == nullptr) // weapon 1 is empty
	{
		oldWeapon = weapon1;
		weapon1 = newWeapon;
	}
	else if (weapon2 == nullptr) // weapon 2 is empty
	{
		oldWeapon = weapon2;
		weapon2 = newWeapon;
	}
	else if (weapon3 == nullptr) // weapon 3 is empty
	{
		oldWeapon = weapon3;
		weapon3 = newWeapon;
	}
	else // replaces weapon 1 and returns its number
	{	
		WIN = getWeapon1()->getWIN();

		if (WIN == 0) // if it's the null blade, the removal doesn't happen.
			return newWeapon->getWIN();

		removeWeapon(1); // removes weapon 1
		giveWeapon(newWeapon);
		
		// weapons.push_back(oldWeapon);

		// oldWeapon = removeWeapon(0);
		// currentWeapon = newWeapon;
	}

	return WIN; // returns the weapon that has been replaced.
}

// removes a weapon from the player's set
int entity::Player::removeWeapon(unsigned int index)
{
	int WIN = -1;

	if (index > 3)
		return WIN;
	
	if (getWeapon(index) == nullptr || getWeapon(index)->getWIN() == 0) // the null blade cannot be removed.
		return WIN;


	WIN = getWeapon(index)->getWIN(); // gets the number of the weapon being removed.
	delete getWeapon(index);
	weapons.at(index) = nullptr;

	switch (index)
	{
	case 0:
		currentWeapon = nullptr;
		break;
	case 1:
		weapon1 = nullptr;
		break;
	case 2:
		weapon2 = nullptr;
		break;
	case 3:
		weapon3 = nullptr;
		break;
	}
	
	return WIN; // returns the number of the weapon being remvoed.
}

// uses a weapon.
void entity::Player::useWeapon()
{
	entity::Projectile * proj = nullptr;

	if (currentWeapon == nullptr)
		return;

	runAction(6);

	//switch (currentWeapon->getType()) // runs the action to use the we
	//{
	//case 1: // short-ranged.
	//default:
	//	runAction(6);
	//	break;

	//case 2: // long-ranged
	//	runAction(7);

	//	//switch (currentWeapon->getMagic_T()) // generates a projectile if applicable.
	//	//{
	//	//case magic::null:
	//	//default:
	//	//	proj = new entity::Projectile(11, this);
	//	//	break;
	//	//case magic::shadow:
	//	//	proj = new entity::Projectile(14, this);
	//	//	break;
	//	//case magic::fire:
	//	//	proj = new entity::Projectile(17, this);
	//	//	break;
	//	//case magic::water:
	//	//	proj = new entity::Projectile(20, this);
	//	//		break;
	//	//case magic::earth:
	//	//	proj = new entity::Projectile(23, this);
	//	//	break;
	//	//case magic::air:
	//	//	proj = new entity::Projectile(26, this);
	//	//	break;
	//	//}

	//	//proj->getSprite()->setVisible(true);
	//	//projectiles.push_back(proj); 

	//	break;

	//case 3: // other
	//	runAction(8);
	//	break;
	//}
}

// adds to the player's current health.
void entity::Player::addHealth(float hp)
{
	if(getHealth() + hp <= getMaxHealth()) // the player shouldn't get more health than their limit.
		setHealth(getHealth() + hp); 
}

// adds to the player's maximum health
void entity::Player::addMaxHealth(float hp, bool changeCurrent)
{
	float oldMax = getMaxHealth(); // saves the previous amount of health

	setMaxHealth(getMaxHealth() + hp);

	if (changeCurrent) // if true, the current health is proportionally changed.
		setHealth(getHealth() + (getHealth() / oldMax) * getMaxHealth());
}

// gets the magic power of the player.
float entity::Player::getMagicPower() { return magicPower; }

// gets the maximum magic power of the player.
float entity::Player::getMagicPowerMax() { return magicPowerMax; }

// sets the magic power.
void entity::Player::setMagicPower(float mp)
{
	magicPower = (mp > magicPowerMax) ? magicPowerMax : (mp < 0.0F) ? 0.0F : mp;
	mprTimer = mprTimerMax; // resets the magic restore timer.
}

// sets the maximum magic power which cannot be 0. The current amount of magic is adjusted accordingly.
void entity::Player::setMagicPowerMax(float mpm, bool changeCurrent)
{
	float oldMax = magicPowerMax;

	if (mpm <= 0.0F)
	{
		magicPowerMax = 0.0F;
		
		if(changeCurrent)
			magicPower = magicPowerMax;
	}
	else
	{
		if (changeCurrent)
			magicPower = (magicPower / magicPowerMax) * mpm; // sets the magic power proportionally to the maximum health the player now has.
		
		magicPowerMax = mpm; // sets the maximum magic power.
	}
}


// adds to the magic power of the player.
void entity::Player::addMagicPower(float mp)
{
	if(magicPower + mp <= magicPowerMax) // the player shouldn't get more than their maximum amount of magic
		setMagicPower(magicPower + mp);
}

// adds to the maximum magic power.
void entity::Player::addMagicPowerMax(float mpm, bool changeCurrent) { setMagicPowerMax(magicPowerMax + mpm, changeCurrent); }

// called when the player gets hit.
void entity::Player::gotHit()
{
	hprTimer = hprTimerMax; // times how long it will be until the player gets healed.
	Active::gotHit();
}

void entity::Player::update(float deltaTime)
{
	if (!runningAnimation()) // if no animation is running right now.
	{
		switch (currentAnimation->getTag()) // checks the tag of the animation that just finished.
		{
		case 6: // attack 1
			runAction(2); // switches back to idle once animation is done.
			currentWeapon->disableCollisionBodies(); // turns off the weapon collisions.
			break;
		}

	}
	// addForce(moveForce); // adds the force of the player for movement.
	

	//for (int i = 0; i < weapons.size(); i++)
	//{
	//	if (weapons.at(i) == nullptr)
	//		continue;

	//	if (i <= 3)
	//	{
	//		weapons.at(i)->update(deltaTime);
	//	}
	//	else
	//	{
	//		for (OOP::Primitive * p : weapons[i]->getCollisionBodies()) // removing all of the primitives from their parents for the tiles.
	//			p->getPrimitive()->removeFromParent();

	//		weapons[i]->getSprite()->removeFromParent(); // removes the tile's sprite.
	//		weapons.erase(weapons.begin() + i); // erases the pointer and other tile data.
	//	}
	//}

	if (hpRefill)
	{
		hprTimer -= deltaTime;
		if (hprTimer <= 0.0F) // the timer has been set to 0.
		{
			addHealth(hpAdd); // adds health to the player.
			hprTimer = hprTimerMax;
		}
	}

	if (mpRefill)
	{
		mprTimer -= deltaTime;
		if (mprTimer <= 0.0F) // the timer has been set to 0.
		{
			addMagicPower(mpAdd); // adds health to the player.
			mprTimer = mprTimerMax;
		}
	}

	for (entity::Weapon * w : weapons)
	{
		if (w != nullptr)
			w->update(deltaTime);
	 }

	/*for (entity::Projectile* p : projectiles)
	{
		if (p != nullptr)
			p->update(deltaTime);
	}*/
	Active::update(deltaTime);

}

