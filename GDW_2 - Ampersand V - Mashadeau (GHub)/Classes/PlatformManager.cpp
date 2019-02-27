// Used for making platforms; this likely will not be used.
#include "PlatformManager.h"

// Platform Class

// creates a platform and initalizes the m_Square object using a starting point and ending point.
OOP::Platform::Platform(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint) : m_Square(new OOP::PrimitiveSquare(startPoint, endPoint)) {}

// creates a platform and initalizes the m_Square object using a position (based on sprite centre), width, and height.
OOP::Platform::Platform(cocos2d::Vec2 position, float width, float height) : m_Square(new OOP::PrimitiveSquare(position, width, height)) {}

// creates a platform and initalizes m_Square with a position (based on sprite centre), and a side length.
OOP::Platform::Platform(cocos2d::Vec2 position, float sideLength) : m_Square(new OOP::PrimitiveSquare(position, sideLength)) {}

OOP::Platform::~Platform() {}

OOP::PrimitiveSquare * OOP::Platform::getSquarePrimitive() { return m_Square; } // returns the square primitive

// Platform Manager Class
OOP::PlatformManager::PlatformManager() {}

// Question 3: deletes the memory the vector points to.
OOP::PlatformManager::~PlatformManager() { m_Platforms.clear(); }

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
	cocos2d::DrawNode * tileNode (cocos2d::DrawNode::create());

	for (int i = 0; i < m_Platforms.size(); i++)
		tileNode->addChild(m_Platforms.at(i)->getSquarePrimitive()->getPrimitive()); // adds the square to the drawNode.
	

	return tileNode; // returns a pointer to the draw node so that it can be added to the scene.
}