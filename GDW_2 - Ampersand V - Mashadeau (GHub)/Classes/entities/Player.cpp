#include "entities/Player.h"



entity::Player::Player(std::string texture, Vec2 position, Vec2 moveForce) : Active(texture, position)
{
	sprite->setTextureRect(Rect(0.0F, 0.0F, 256.0F, 256.0F)); // setting the area of the sprite that's used
	sprite->setGlobalZOrder(2.0F); // sets the global Z order of the player.

	this->moveForce = moveForce; // sets the amount of force that gets applied for
}


entity::Player::~Player()
{
}

void entity::Player::update(float deltaTime)
{
	// addForce(moveForce); // adds the force of the player for movement.
	Active::update(deltaTime);
}
