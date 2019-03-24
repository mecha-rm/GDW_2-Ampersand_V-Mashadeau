#include "entities/Player.h"
#include <iostream>


entity::Player::Player() : Active("images/PLR_000.png")
{
	setName("Mashadeau"); // the player character's name
	setDescription("The shadow mage, Mashadeau!");
	frameSize = Rect(0.0F, 0.0F, 256.0F, 256.0F);

	sprite->setTextureRect(frameSize); // setting the area of the sprite that's used
	sprite->setGlobalZOrder(2.0F); // sets the global Z order of the player.
	sprite->setTag(player);

	// collisionShapes.push_back(new OOP::PrimitiveCircle(Vec2(0.0f, 0.0f), 29.0f));
	collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(sprite->getTextureRect().getMidX(), sprite->getTextureRect().getMidY()), 53.0F, 185.0F, CLR_DEF));
	collisionBodies.at(0)->getPrimitive()->setGlobalZOrder(10.1F); // the z-order is now set upon initalization.
	collisionBodies.at(0)->setVisible(shapesVisible);

	sprite->addChild(collisionBodies.at(0)->getPrimitive());


	// collisionShapes.push_back(new OOP::PrimitiveCapsule(Vec2(frameSize.getMidX(), frameSize.getMidY() + 185.0F / 2), Vec2(frameSize.getMidX(), frameSize.getMidY() - 185.0F / 2), 53.0F / 2, CLR_DEF));
	collisionBodies.push_back(new OOP::PrimitiveCapsule(Vec2(frameSize.getMidX(), frameSize.getMidY()), 185.0F, 53.0F / 2, 90.0F, CLR_DEF));
	collisionBodies.at(1)->getPrimitive()->setGlobalZOrder(10.1F); // the z-order is now set upon initalization.
	collisionBodies.at(1)->setVisible(shapesVisible);

	sprite->addChild(collisionBodies.at(1)->getPrimitive());
	// sprite->addChild(circles.at(0)->getPrimitive());

	
	this->moveForce = Vec2(200.0F, 200.0F); // sets the amount of force that gets applied for
	this->jump = 14000.0F;
	setDecelerate(Vec2(getDecelerate().x, 0.99F));
	setMass(1.0F);

	setMaxHealth(20.0F);
	setHealth(getMaxHealth());

	// setHealth(19.0F);
	
	// Animation().
}


entity::Player::~Player() {}

void entity::Player::update(float deltaTime)
{
	// addForce(moveForce); // adds the force of the player for movement.
	Active::update(deltaTime);
}
