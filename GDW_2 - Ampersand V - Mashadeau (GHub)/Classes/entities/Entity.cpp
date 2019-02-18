#include "entities/Entity.h"

float * entity::Entity::areaGravity = new float(1.0F); // the default level of gravity for all entities.

entity::Entity::Entity(std::string texture, Vec2 position, float globalZOrder) : sprite(Sprite::create())
{
	sprite->setTexture(texture);
	sprite->setAnchorPoint(Vec2(0.5, 0.5)); // anchour point is the middle of the sprite
	sprite->setPosition(position); // setting position
	sprite->setGlobalZOrder(globalZOrder);
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

// sets the textureRect(cropped area) for the sprite
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

// gets the sprite's opacity as a percentage.
float entity::Entity::getOpacity() { return sprite->getOpacity() / 255; }

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

// returns the mass of the entity
float entity::Entity::getMass() const { return mass; }

// sets the mass of the entity; can't be below or equal to 0.
void entity::Entity::setMass(float mass) { (mass > 0.0F) ? this->mass = mass : this->mass; }

// returns the force on both axes
Vec2 entity::Entity::getForce() const { return force; }

// returns the force on the x-axis
float entity::Entity::getForceX() const { return force.x; }

// returns the force on the y-axis
float entity::Entity::getForceY() const { return force.y; }

// sets the force for both axes
void entity::Entity::setForce(Vec2 force) { this->force = force; }

// sets the force for both axes
void entity::Entity::setForce(float x, float y) { setForce(Vec2(x, y)); }

// adds to the entity's current force
void entity::Entity::addForce(Vec2 force) { this->force += force; }

// adds to the entity's current force
void entity::Entity::addForce(float forceX, float forceY) { force += Vec2(forceX, forceY); }

// gets the maixmum velocity of the entity
Vec2 entity::Entity::getMaxVelocity() { return maxVelocity; }

// sets the maximum velocity; it cannot be below 0.
void entity::Entity::setMaxVelocity(Vec2 maxVelocity)
{
	// sets the maximum velocity of the entity. Comparisons use the absolute value of the entity, hence why it must be above 0.
	if (maxVelocity > Vec2(0.0F, 0.0F))
		this->maxVelocity = maxVelocity;
}

// returns the deceleration rate of the entity.
float entity::Entity::getDecelerate() const { return decelerate; }

// sets the deceleration rate of the entity.
void entity::Entity::setDecelerate(float decelerate)
{
	// if the deceleration rate passed is greater than 0, and less than 1.0 (since this would cause no deceleration).
	if (decelerate > 0.0F && decelerate < 1.0F)
		this->decelerate = decelerate;
}

// returns at what point the entity comes to a complete stop.
float entity::Entity::getForceStop() const { return forceStop; }

// sets the threshold the entity's velocity must pass (i.e. value the entity's velocity must fall below) to be brought into a complete stop.
void entity::Entity::setForceStop(float forceStop)
{
	// the provided forceStop must be greater than 0.0F, since a value cannot be divided to become 0.
	// forceStop must also be positive, as it uses the absolute value of the entity's velocity to check if they're below 'forceStop' or not.
	if (forceStop > 0.0F)
		this->forceStop = forceStop;
}

// returns whether the entity has a constant velocity or not.
bool entity::Entity::getConstVelocity() const { return constVelocity; }

// returns the current bool of 'anti gravity', which determines if the entity is affected by gravity or not.
bool entity::Entity::getAntiGravity() const { return antiGravity; }

// sets whether the entity has anti gravity or not.
void entity::Entity::setAntiGravity(float antiGravity) { this->antiGravity = antiGravity; }

// toggles anti gravity on/off.
void entity::Entity::setAntiGravity() { antiGravity = !antiGravity; }

// sets whether the entity has a constant velocity (i.e. the velocity is either '0', or some value) or not.
void entity::Entity::setConstVelocity(bool constVelocity) { this->constVelocity = constVelocity; }

// toggles the 'constVelocity' variable.
void entity::Entity::setConstVelocity() { setConstVelocity(!constVelocity); }

// Update Loop
void entity::Entity::update(float deltaTime)
{
	Vec2 position = getPosition(); // gets the entity's current position
	Vec2 acceleration; // the enemy's current acceleration

	acceleration = force / mass; // gets the force to be applied, divided by the entity's mass.

	if(antiGravity == false)  // applies gravity to the entity if anti gravity is turned off.
		acceleration.y -= *areaGravity / mass;

	velocity += acceleration * deltaTime; // adds the acceleration to the entity's velocity
	
	// Capping Velocity (x, y)
	// if the entity has gone over its maximum velocity, their speed is set to their maximum velocity (x-axis ver.).
	if (abs(velocity.x * deltaTime) > maxVelocity.x)
		(velocity.x > 0.0F) ? velocity.x = maxVelocity.x / deltaTime : velocity.x = -maxVelocity.x / deltaTime; // checks the direction of the entity to see whether its new velocity should be positive or negative.

	// if the entity has gone over its maximum velocity, their speed is set to their maximum velocity (y-axis ver.).
	if (abs(velocity.y * deltaTime) > maxVelocity.y)
		(velocity.y > 0.0F) ? velocity.y = maxVelocity.y / deltaTime : velocity.y = -maxVelocity.y / deltaTime; // checks the direction of the entity to see whether its new velocity should be positive or negative.


	// Slowing Down (x, y)
	// if the entity does NOT have a constant velocity, currently has a non-zero x-velocity, and has no force being applied to it on the x-axis, it starts to slow down.
	if (velocity.x != 0.0F && force.x == 0.0F)
		velocity.x *= decelerate; // multiplied by the deceleration rate

	// if the entity does NOT have a constant velocity, currently has a non-zero y-velocity, and has no force being applied to it on the y-axis, it starts to slow down.
	if (velocity.y != 0.0F && force.y == 0.0F)
		velocity.y *= decelerate; // multiplied by the deceleration rate


	// Stopping the Entity (x, y)
	// if the entity does not have a constant velocity, it has no force being applied, has a non-zero x-velocity, and has fallen below 'forceStop' on the x-axis, its x velocity is set to 0.
	if (constVelocity == false && force.x == 0.0F && velocity.x != 0.0F && (velocity.x * deltaTime) < forceStop)
		velocity.x = 0.0F;

	// if the entity does not have a constant velocity, it has no force being applied, has a non-zero y-velocity, and has fallen below 'forceStop' on the y-axis, its y velocity is set to 0.
	if (constVelocity == false && force.y == 0.0F && velocity.y != 0.0F && abs(velocity.y * deltaTime) < forceStop)
		velocity.y = 0.0F;
	
	position += velocity * deltaTime; // adds the velocity to the entity's position.

	setPosition(position); // sets the entity's new position
	setForce(Vec2(0.0F, 0.0F)); // returns the force back to a value of 0.

	if (constVelocity) // if the entity has a constant velocity, the velocity is reset to '0', so values don't carry over.
		velocity = Vec2(0.0F, 0.0F);

	age += deltaTime; // counts how long an entity has existed for.
}
