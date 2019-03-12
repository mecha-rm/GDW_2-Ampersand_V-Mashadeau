#include "entities/Enemy.h"


// This follows the same format as the Tile class.
entity::Enemy::Enemy(unsigned int EIN, char letter, const unsigned int COPY_UP, const unsigned int COPY_DOWN, const unsigned int COPY_LEFT, const unsigned int COPY_RIGHT, const bool OFFSET_BY_SPRITE_SIZE)
	: Active(), COPY_UP(COPY_UP), COPY_DOWN(COPY_DOWN), COPY_LEFT(COPY_LEFT), COPY_RIGHT(COPY_RIGHT), OFFSET_BY_SPRITE_SIZE(OFFSET_BY_SPRITE_SIZE)
{
	createEnemy(EIN, letter);
}


entity::Enemy::~Enemy() {}

// returns the EIN number of the enemy
const unsigned int entity::Enemy::getEIN() const { return EIN; }

// returns the letter atached to the enemy
const char entity::Enemy::getLetter() const { return LETTER; }

// creates the enemy by using inital values
void entity::Enemy::createEnemy(unsigned int EIN, char letter)
{
	sprite->setGlobalZOrder(3.0F); // the global z order of enemies
	sprite->setTag(enemy);

	this->EIN = EIN; // saving the EIN; will be changed if invalid.
	this->LETTER = letter; // saving the letter; will be changed if invalid.

	switch (EIN)
	{
	case 1:
		break;
	case 2:
		break;

	default: // default "DUMMY" enemy
		this->EIN = 0;
		this->LETTER = 'a';
		name = "Dummy";
		description = "If you're reading this description, it means the desired enemy couldn't be found, so you'll fight to 'Dummy' instead. Dummy likes hovering and staring contests.";

		setMaxHealth(10.0F);
		setHealth(getMaxHealth());
		setAttackPower(10.0F);

		sprite->setTexture("images/enemies/EIN_000.png"); // sets the enemy's image
		setTextureRect(0.0F, 0.0F, 40.0F, 40.0F); // sets the rectangle texture

		collisionShapes.push_back(new OOP::PrimitiveCircle(Vec2(20.0F, 20.0F), 20.0F, CLR_DEF));
		collisionShapes.at(0)->setVisible(true);
		collisionShapes.push_back(new OOP::PrimitiveCircle(Vec2(20.0F, 20.0F), 20.0F, CLR_ATK));
		collisionShapes.at(1)->setVisible(true);

		
		// moveForce = Vec2(10.0F, 0.0F);
	}

	for (int i = 0; i < collisionShapes.size(); i++) // adds all of the collision shapes to the sprite.
	{
		collisionShapes.at(i)->getPrimitive()->setGlobalZOrder(10.1F);
		// collisionShapes.at(i)->getPrimitive()->setVisible(true);
		sprite->addChild(collisionShapes.at(i)->getPrimitive());
	}

}

// update loop
void entity::Enemy::update(float deltaTime)
{
	addForce(moveForce); // adds to the force of the entity
	Active::update(deltaTime); // calls the 'Active' update loop
}