#include "entities/Entity.h"



entity::Entity::Entity(std::string texture, Vec2 position) : sprite(Sprite::create())
{
	sprite->setAnchorPoint(Vec2(0.5, 0.5)); // anchour point is the middle of the sprite
	sprite->setPosition(position); // setting position
}

// releases the sprite 
entity::Entity::~Entity() { sprite->release(); }

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

// returns the sprite's texture (image)
Texture2D * entity::Entity::getTexture() const { return sprite->getTexture(); }

// sets the entity's texture via an image path
void entity::Entity::setTexture(std::string image) { sprite->setTexture(image); }

// returns hte texture rect used to crop the sprite's image
Rect entity::Entity::getTextureRect() const { return sprite->getTextureRect(); }

// sets the textureRect (cropped area) for the sprite
void entity::Entity::setTextureRect(Rect textureRect) { sprite->setTextureRect(textureRect); }

void entity::Entity::setTextureRect(float x, float y, float width, float height, const bool USE_CENTRE)
{
	// USE_CENTRE == TRUE -> if the user wants (x, y) to be the centre point of the tecture rect
	// USE_CENTRE == FALSE -> if the user wants (x, y) to be a corner point
	(USE_CENTRE) ? setTextureRect(Rect(x - width / 2, y - width / 2, width, height)) : setTextureRect(Rect(x, y, width, height));
}

// sets the entity's position
void entity::Entity::setPosition(Vec2 newPos) { sprite->setPosition(newPos); }

// sets the entity's position
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

// sets the mass of the entity; can't be below or equal to 0.
void entity::Entity::setMass(float mass) { (mass > 0.0F) ? this->mass = mass : this->mass; }

// returns the mass of the entity
float entity::Entity::getMass() const { return mass; }

// returns the force on both axes
Vec2 entity::Entity::getForce() const { return force; }

// returns the force on the x-axis
float entity::Entity::getForceX() const { return force.x; }

// returns the force on the y-axis
float entity::Entity::getForceY() const { return force.y; }

// sets the force for both axes
void entity::Entity::setForce(Vec2 force)
{
	this->force = force;
}

// adds to the entity's current force
void entity::Entity::addForce(Vec2 force) { this->force += force; }

// adds to the entity's current force
void entity::Entity::addForce(float forceX, float forceY) { force += Vec2(forceX, forceY); }

// Update Loop
void entity::Entity::update(float deltaTime)
{
	age += deltaTime; // counts how long an entity has existed for.
}
