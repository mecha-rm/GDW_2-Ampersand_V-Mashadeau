// Used for making platforms; this likely will not be used.
#include "PlatformManager.h"
#include "cocos/math/Vec2.h"
#include "cocos/2d/CCDrawNode.h"

// Platform Class

// creates a platform and initalizes the m_Square object using a starting point and ending point.
OOP::Platform::Platform(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint) : m_Square(new OOP::PrimitiveSquare(startPoint, endPoint))
{
	position = (startPoint + endPoint) / 2; // saves the position of the square.
}

// creates a platform and initalizes the m_Square object using a position (based on sprite centre), width, and height.  This also saves the postiion of the platform.
OOP::Platform::Platform(cocos2d::Vec2 position, float width, float height) : m_Square(new OOP::PrimitiveSquare(position, width, height)) { this->position = position; }

// creates a platform and initalizes m_Square with a position (based on sprite centre), and a side length. This also saves the postiion of the platform.
OOP::Platform::Platform(cocos2d::Vec2 position, float sideLength) : m_Square(new OOP::PrimitiveSquare(position, sideLength)) { this->position = position; }

OOP::Platform::~Platform() {}

OOP::PrimitiveSquare * OOP::Platform::getSquarePrimitive() { return m_Square; } // returns the square primitive

// sets the position of the platform
void OOP::Platform::setPosition(cocos2d::Vec2 position)
{
	cocos2d::Vec2 offset = position - this->position; // gets the difference between the new position and the old position.

	// moves the square primitive. This needs to be done since the location of the drawNode is not the same as the actual platform.
	m_Square->getPrimitive()->setPosition(m_Square->getPrimitive()->getPosition() + offset);

	this->position = position; // saves the platform's new position.
}

// returns the position of the platform.
cocos2d::Vec2 OOP::Platform::getPosition() { return position; }



OOP::VerticalMovingPlatform::VerticalMovingPlatform(const cocos2d::Vec2 STARTING_POS, const cocos2d::Vec2 ENDING_POS, float width, float height, const float SPEED)
	: Platform(STARTING_POS, width, height), SPEED(SPEED), STARTING_POS(STARTING_POS), ENDING_POS(ENDING_POS) {}

// Question 6: vertical moving platform update function
void OOP::VerticalMovingPlatform::update(float deltaTime)
{
	short int direc = (moveUp == true) ? 1 : -1; // saves whether the platform is moving up or down.

	// sets and saves the platform's new position, as well as moving the platform graphic.
	setPosition(getPosition() + cocos2d::Vec2(0.0F, 100.0F) * SPEED * deltaTime * direc);

	if (getPosition().y >= ENDING_POS.y) // If the ending position is met, or has been surpassed.
		moveUp = false; // becomes false so that the platform will now move down.

	else if (getPosition().y <= STARTING_POS.y) // if the starting position has been reached, then the platform starts to move up again.
		moveUp = true; // becomes true so that the platform will move up.

}

// Question 3: constructor
OOP::HorizontallyMovingPlatform::HorizontallyMovingPlatform(const cocos2d::Vec2 STARTING_POS, const cocos2d::Vec2 ENDING_POS, float width, float height, const float SPEED)
	: Platform(STARTING_POS, width, height), STARTING_POS(STARTING_POS), ENDING_POS(ENDING_POS), SPEED(SPEED) {}

void OOP::HorizontallyMovingPlatform::update(float deltaTime)
{
	short int direc = (moveRight == true) ? 1 : -1; // saves whether the platform is moving right or left.

	// sets and saves the platform's new position, as well as moving the platform graphic.
	setPosition(getPosition() + cocos2d::Vec2(100.0F, 0.0F) * SPEED * deltaTime * direc);

	if (getPosition().x >= ENDING_POS.x) // If the ending position is met, or has been surpassed.
		moveRight = false; // becomes false so that the platform will now move left.

	else if (getPosition().x <= STARTING_POS.x) // if the starting position has been reached, then the platform starts to move up again.
		moveRight = true; // becomes true so that the platform will move right.

}


// rotating platform update
OOP::RotatingPlatform::RotatingPlatform(cocos2d::Vec2 position, float width, float height, const float SPEED, const bool CLOCKWISE)
	: Platform(cocos2d::Vec2(0.0F, 0.0F), width, height), SPEED(SPEED), CLOCKWISE(CLOCKWISE)
{
	// In order for rotations to work properly, the shape needs to be placed at (0, 0), and the drawNode position needs to be set to the place where the graphic should actually be drawn.
	// This allows the centre of the graphic to be the origin of the drawNode, and thus allow the shape to rotate around its centre. This is the only one of the platforms that works like this.
	getSquarePrimitive()->getPrimitive()->setPosition(position);
}

// update for rotating platforms.
void OOP::RotatingPlatform::update(float deltaTime)
{
	int rDirec = (CLOCKWISE) ? 1 : -1; // sets the rotation direction based on whether the platform rotates clockwise or not.
	getSquarePrimitive()->getPrimitive()->setRotation(getSquarePrimitive()->getPrimitive()->getRotation() + 10.0 * SPEED * deltaTime * rDirec);
}


//// Platform Manager Class ////////////////////////////////////////////
OOP::PlatformManager::PlatformManager() {}

// Question 3: deletes the memory the vector points to.
OOP::PlatformManager::~PlatformManager() { m_Platforms.clear(); }

// adds a platform to the platform manager
void OOP::PlatformManager::Add(Platform * platform) { *this += platform; }

// subtracts a platform from the platform manager.
void OOP::PlatformManager::Subtract(Platform * platform) { *this -= platform; }

void OOP::PlatformManager::operator+=(Platform * platform) // Question 4: operator +; adds a platform object to the vector
{
	// check to see if the passed platform exists in the vector. If it doesn't, add it in.
	for each(Platform * vecPlatform in m_Platforms)
	{
		if (vecPlatform == platform) // returns void if the platformer exists in the vector
			return;
	}

	m_Platforms.push_back(platform); // adds the platform into the vector if it isn't in there already.
}

void OOP::PlatformManager::operator-=(Platform * platform) // Question 5: operator -; removes a platform object from the vector
{
	// look for the object in the vector, and if found, subtract it from the vector.
	for (int i = 0; i < m_Platforms.size(); i++)
	{
		if (m_Platforms.at(i) == platform) // if the passed platform is found, it's erased by the vector.
		{
			m_Platforms.erase(m_Platforms.begin() + i);
			return; // returns 'void' since the check is done.
		}
	}

	// if the passed object wasn't found, then nothing happens.
}

OOP::Platform * OOP::PlatformManager::operator[](const unsigned int index) // Question 6: getting the index of a platform *
{
	// index validation; if the index is out of bounds, a nullptr is returned.
	if (index >= m_Platforms.size())
		return nullptr;

	// Returns the platform in the vector if the index is valid.
	return m_Platforms.at(index);
}

cocos2d::DrawNode * OOP::PlatformManager::Generate() // Question 3: populates platform vector
{
	cocos2d::DrawNode * tileNode(cocos2d::DrawNode::create());

	for (int i = 0; i < m_Platforms.size(); i++)
		tileNode->addChild(m_Platforms.at(i)->getSquarePrimitive()->getPrimitive()); // adds the square to the drawNode.


	return tileNode; // returns a pointer to the draw node so that it can be added to the scene.
}

// adds the drawNode to the provided scene.
void OOP::PlatformManager::Generate(cocos2d::Scene * scene) { scene->addChild(Generate()); }

// Question 8: updates all platforms
void OOP::PlatformManager::update(float deltaTime)
{
	for each(OOP::Platform * platform in m_Platforms) // updates every platform
		platform->update(deltaTime);
}