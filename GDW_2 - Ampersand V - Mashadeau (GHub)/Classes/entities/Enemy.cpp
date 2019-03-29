#include "entities/Enemy.h"


// This follows the same format as the Tile class.
entity::Enemy::Enemy(unsigned int EIN, char letter, const unsigned int COPY_UP, const unsigned int COPY_DOWN, const unsigned int COPY_LEFT, const unsigned int COPY_RIGHT, const bool OFFSET_BY_SPRITE_SIZE)
	: Active(), COPY_UP(COPY_UP), COPY_DOWN(COPY_DOWN), COPY_LEFT(COPY_LEFT), COPY_RIGHT(COPY_RIGHT), OFFSET_BY_SPRITE_SIZE(OFFSET_BY_SPRITE_SIZE)
{
	createEnemy(EIN, letter);
}


entity::Enemy::~Enemy() { }

// returns the EIN number of the enemy
const unsigned int entity::Enemy::getEIN() const { return EIN; }

// returns the letter atached to the enemy
const char entity::Enemy::getLetter() const { return LETTER; }

// creates the enemy by using inital values
void entity::Enemy::createEnemy(unsigned int EIN, char letter)
{
	std::string filePath = ""; // the name of the file for the sprite image.

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

	// Kraw-fly
	case 101:
		this->LETTER = 'a';

		setName("Kraw-Fly");
		setDescription("a banana fly creature.");

		setMaxHealth(1.0F);
		setHealth(getMaxHealth());
		setAttackPower(15.0F);

		filePath = "images/enemies/EIN_101.png"; // sets the file path for the enemy.
		frameSize = Rect(0.0F, 0.0F, 192.0F, 192.0F);
		sprite->setTexture(filePath);
		setTextureRect(frameSize);
		
		animations.push_back(new OOP::SpriteSheetAnimation(sprite, 0, true, 0.05F, true, true));

		for (int i = 0; i < 11; i++) // creates the animation for the krawFly
		{
			// adds a frame to the animation.
			animations.at(0)->add(new OOP::SpriteSheetAnimationFrame(Rect(0.0F + frameSize.getMaxX() * i, 0.0F + frameSize.getMaxY(), frameSize.getMaxX(), frameSize.getMaxY())));
		}

		currentAnimation = animations.at(0);
		currentAnimation->runAnimation();

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMaxX() / 2, frameSize.getMaxY() / 2), 68.0F, 82.0F, CLR_DEF));
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMaxX() / 2, frameSize.getMaxY() / 2), 68.0F, 82.0F, CLR_ATK));

		break;

	default: // default "DUMMY" enemy
		this->EIN = 0;
		this->LETTER = 'a';

		setName("Dummy");
		setDescription("If you're reading this description, it means the desired enemy couldn't be found, so you'll fight to 'Dummy' instead. Dummy likes hovering and staring contests.");

		setMaxHealth(10.0F);
		setHealth(getMaxHealth());
		setAttackPower(10.0F);

		filePath = "images/enemies/EIN_000.png";
		frameSize = Rect(0.0F, 0.0F, 40.0F, 40.0F);
		sprite->setTexture(filePath); // sets the enemy's image
		setTextureRect(frameSize); // sets the rectangle texture

		collisionBodies.push_back(new OOP::PrimitiveCircle(Vec2(20.0F, 20.0F), 20.0F, CLR_DEF));
		collisionBodies.push_back(new OOP::PrimitiveCircle(Vec2(20.0F, 20.0F), 20.0F, CLR_ATK));

		
		// moveForce = Vec2(10.0F, 0.0F);
	}

	for (OOP::Primitive * colShape : collisionBodies) // adds all of the collision shapes to the sprite.
	{
		colShape->getPrimitive()->setGlobalZOrder(10.1F);
		colShape->getPrimitive()->setVisible(shapesVisible);
		sprite->addChild(colShape->getPrimitive());
	}
}

// update loop
void entity::Enemy::update(float deltaTime)
{
	// setHealth(getHealth() - 1);
	addForce(moveForce); // adds to the force of the entity
	Active::update(deltaTime); // calls the 'Active' update loop

	
}