#include "entities/Player.h"
#include <iostream>


entity::Player::Player() : Active("images/PLR_000.png")
{
	OOP::SpriteSheetAnimation * tempAnimate = nullptr; // a temporary animation

	setName("Mashadeau"); // the player character's name
	setDescription("The shadow mage, Mashadeau!");
	frameSize = Rect(0.0F, 0.0F, 256.0F, 256.0F);

	setMagicType(magic::shadow);

	sprite->setTextureRect(frameSize); // setting the area of the sprite that's used
	sprite->setGlobalZOrder(2.0F); // sets the global Z order of the player.
	sprite->setTag(player);

	// collisionShapes.push_back(new OOP::PrimitiveCircle(Vec2(0.0f, 0.0f), 29.0f));
	collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(sprite->getTextureRect().getMidX(), sprite->getTextureRect().getMidY()), 53.0F, 185.0F, CLR_DEF));
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
	setJumpForce(13000.0F);
	setDecelerate(Vec2(getDecelerate().x, 0.99F));
	setMass(0.5F);

	setMaxHealth(100.0F);
	setHealth(getMaxHealth());
	inviTimeMax = 3.0F;

	setMagicPowerMax(100.0F, false);
	setMagicPower(getMagicPowerMax());

	weapon1 = new entity::Weapon(0, this);
	currentWeapon = weapon1;
	weapons.push_back(weapon1);

	// no animation (0); 1 frame
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, true, true);
	tempAnimate->setName("static");
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(frameSize));
	animations.push_back(tempAnimate);

	currentAnimation = tempAnimate;

	// attack animation 1 (tag = 6) : 3 frames
	tempAnimate = new OOP::SpriteSheetAnimation(sprite, 0, false, 0.0F, true, false); // new animation
	tempAnimate->setTag(6); // sets the tag
	
	// tempAnimate->getFrames().at(getFrames()->)
	
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 0, 0.0F + frameSize.getMaxY() * 1, frameSize.getMaxX(), frameSize.getMaxY()))); // frame 1
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 1, 0.0F + frameSize.getMaxY() * 1, frameSize.getMaxX(), frameSize.getMaxY()))); // frame 2
	tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * 2, 0.0F + frameSize.getMaxY() * 1, frameSize.getMaxX(), frameSize.getMaxY()))); // frame 3
	// tempAnimate->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX(), 0.0F + frameSize.getMaxY(), frameSize.getMaxX(), frameSize.getMaxY())));
	animations.push_back(tempAnimate);
	
	// runAction(0);

	// currentAnimation->runAnimation();

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
			6) attack 1
*/
void entity::Player::runAction(unsigned int ani)
{
	runAnimationByTag(ani);

	if (ani == 6 || ani == 7)
		currentWeapon->enableCollisionBodies();

}

entity::Weapon * entity::Player::getWeapon1() const { return weapon1; }

entity::Weapon * entity::Player::getWeapon2() const { return weapon2; }

entity::Weapon * entity::Player::getWeapon3() const { return weapon3; }

// returns the current weapon
entity::Weapon * entity::Player::getCurrentWeapon() const { return currentWeapon; }

/*
 * Switches the weapon. It can only be a value from 1 - 3
 * [1]: weapon 1
 * [2]: weapon 2
 * [3]: weapon 3
*/
void entity::Player::switchWeapon(short int weapon)
{
}

// gets the magic power of the player.
float entity::Player::getMagicPower() { return magicPower; }

// gets the maximum magic power of the player.
float entity::Player::getMagicPowerMax() { return magicPowerMax; }

// sets the magic power.
void entity::Player::setMagicPower(float mp)
{
	magicPower = (mp > magicPowerMax) ? magicPowerMax : (mp < 0.0F) ? 0.0F : mp;
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
void entity::Player::addMagicPower(float mp) { setMagicPower(magicPower + mp); }

// adds to the maximum magic power.
void entity::Player::addMagicPowerMax(float mpm, bool changeCurrent) { setMagicPowerMax(magicPowerMax + mpm, changeCurrent); }

void entity::Player::update(float deltaTime)
{
	if (!runningAnimation()) // if no animation is running right now.
	{
		switch (currentAnimation->getTag()) // checks the tag of the animation that just finished.
		{
		case 6: // attack 1
			runAction(0); // switches back to idle once animation is done.
			currentWeapon->disableCollisionBodies(); // turns off the weapon collisions.
			break;
		}

	}
	// addForce(moveForce); // adds the force of the player for movement.
	Active::update(deltaTime);

	for (entity::Weapon * w : weapons)
		w->update(deltaTime);

}

