#include "entities/Player.h"
#include <iostream>


entity::Player::Player(std::string texture, Vec2 position, Vec2 moveForce, float jump) : Active(texture, position)
{
	name = "Mashadeau"; // the player character's name
	description = "The shadow mage, Mashadeau!";

	sprite->setTextureRect(Rect(0.0F, 0.0F, 256.0F, 256.0F)); // setting the area of the sprite that's used
	sprite->setGlobalZOrder(2.0F); // sets the global Z order of the player.
	sprite->setTag(player);
	sprite->getPhysicsBody()->setTag(player); // setting the tag used for collision identification. This is currently not being used.

	// circles.push_back(new OOP::PrimitiveCircle(Vec2(0.0f, 0.0f), 29.0f));
	aabbs.push_back(new OOP::PrimitiveSquare(Vec2(sprite->getTextureRect().getMidX(), sprite->getTextureRect().getMidY()), 37.0F, 91.0F));
	// aabbs.at(0)->getPrimitive()->setGlobalZOrder(10.1F); // the z-order is now set upon initalization.
	aabbs.at(0)->setVisible(true);

	sprite->addChild(aabbs.at(0)->getPrimitive());

	capsules.push_back(new OOP::PrimitiveCapsule(Vec2(sprite->getTextureRect().getMidX(), sprite->getTextureRect().getMidY()), 91.0F, 37.0F / 2, 90.0F));
	// capsules.at(0)->getPrimitive()->setGlobalZOrder(10.1F); // the z-order is now set upon initalization.
	capsules.at(0)->setVisible(true);

	sprite->addChild(capsules.at(0)->getPrimitive());
	// sprite->addChild(circles.at(0)->getPrimitive());
	

	this->moveForce = moveForce; // sets the amount of force that gets applied for
	this->jump = jump;
	setDecelerate(Vec2(getDecelerate().x, 0.99F));
	setMass(1.0F);


	/* // Not being used currently.
	//sprite->getPhysicsBody()->createBox(Size(37.0F, 91.0F)); // adding a physics box to the entity.
	sprite->getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(37.0F, 91.0F)));
	sprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	sprite->getPhysicsBody()->setDynamic(false);
	// sprite->getPhysicsBody()->addShape(PhysicsShape::set)
	*/

	
}


entity::Player::~Player()
{
}

void entity::Player::update(float deltaTime)
{
	// addForce(moveForce); // adds the force of the player for movement.
	Active::update(deltaTime);
}
