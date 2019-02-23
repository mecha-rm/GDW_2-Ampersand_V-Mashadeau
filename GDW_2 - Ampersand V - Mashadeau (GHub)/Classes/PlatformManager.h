// Used for making platforms; this likely will not be used.
#pragma once
#include "Primitives.h"
#include <vector>

namespace OOP
{
	// Question 2: Platform Class
	class Platform
	{
	public:
		// makes a platform based on a provided starting and ending point
		Platform(cocos2d::Vec2 startPoint, cocos2d::Vec2 endPoint);

		 // makes a platform based on a provided position, width, and height. The position is based on the centre of the sprite.
		Platform(cocos2d::Vec2 position, float width, float height);

		// creates a platform with a providied position and side length. Position is based on the middle of the sprite.
		Platform(cocos2d::Vec2 position, float sideLength);

		~Platform();

		// returns the square primtiive
		OOP::PrimitiveSquare * getSquarePrimitive();


	private:
		OOP::PrimitiveSquare * m_Square; // Question 2: PrimitiveSquare variable.

	protected:


	};


	class PlatformManager
	{
	public:
		PlatformManager();
		~PlatformManager(); // Question 3: Destructor

		void operator+=(Platform *); // Question 4: (+) operator - adds in passed object
		
		void operator-=(Platform *); // Question 5: (-) operator - removes passed object
		
		Platform * operator[](const unsigned int index); // Question 6: ([]) operator - gets platform stored at provided index
		
		cocos2d::DrawNode * Generate(); // Question 3: populates the platform vector (generating terrain)

	private:
		std::vector<Platform *> m_Platforms; // Question 2: platform pointer

	protected:
	};
}
