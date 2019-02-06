#include "entities/Entity.h"



entity::Entity::Entity() : sprite(Sprite::create())
{
}


entity::Entity::~Entity()
{

}

// returns the length of time the entity has existed for.
float entity::Entity::getAge() { return age; }

// returns the entity's name.
std::string entity::Entity::getName() { return name; }

// Returns the entity's description.
std::string entity::Entity::getDescription() { return description; }

// returns the entity's sprite
Sprite * entity::Entity::getSprite() const { return sprite; }

// sets the entity's sprite
void entity::Entity::setSprite(Sprite * sprite) { this->sprite = sprite; }

// sets the entity's texture via an image path
void entity::Entity::setTexture(std::string image) { sprite->setTexture(image); }

// returns the sprite's texture (image)
Texture2D * entity::Entity::getTexture() const { return sprite->getTexture(); }

void entity::Entity::setPosition(Vec2 newPos) { sprite->setPosition(newPos); }

void entity::Entity::setPosition(float x, float y) { sprite->setPosition(Vec2(x, y)); }

// Gets the position of the sprite
Vec2 entity::Entity::getPosition() const { return sprite->getPosition(); }

void entity::Entity::setPositionX(float x) { sprite->setPositionX(x); }

// gets the sprite's x position.
float entity::Entity::getPositionX() const { return sprite->getPositionX(); }

void entity::Entity::setPositionY(float y) { sprite->setPositionY(y); }

// gets the sprite's y position.
float entity::Entity::getPositionY() const { return sprite->getPositionY(); }

// sets the opacity of the sprite via a percentage.
void entity::Entity::setOpacity(float opacity)
{
	// If an opacity greater than 100% (1.0) is provided, the variable is set to 1.0.
	if (opacity > 1.0F)
	{
		opacity = 1.0F;
	
	// If a negative opacity is provided, it is set to 0.
	}
	else if (opacity < 0.0F)
	{
		opacity = 0.0F;
	}

	sprite->setOpacity(255 * opacity); // sets the sprite's new opacity.
		
}

// gets the sprite's opacity as a percentage.
float entity::Entity::getOpacity() { return sprite->getOpacity() / 255; }

// Update Loop
void entity::Entity::update(float deltaTime)
{
	age += deltaTime; // counts how long an entity has existed for.
}
