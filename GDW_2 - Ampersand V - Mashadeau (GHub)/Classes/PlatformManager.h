// Used for making platforms; this likely will not be used.
// Object Oriented Programming - Lab 4 | Inheritance - Terrain Variability
// Question 1: PlatformManager.h Inclusion

#pragma once
#include "Primitives.h"
#include <vector>

#include "cocos/2d/CCScene.h"

namespace OOP
{
	// The Platform class; this is a hold over from a previous lab.
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

		// returns the square primtive
		OOP::PrimitiveSquare * getSquarePrimitive();

		// sets the position of the platform
		void setPosition(cocos2d::Vec2 position);

		// gets the position of the platform.
		cocos2d::Vec2 getPosition();

		// update function. Each platform class has its own update.
		virtual void update(float deltaTime) = 0; // Question 5: virtual update function

	private:
		OOP::PrimitiveSquare * m_Square; // Question 2: PrimitiveSquare variable.
		cocos2d::Vec2 position; // saves the position of the square.

	protected:

	};

	// Question 2: Vertical Moving Platform
	class VerticalMovingPlatform : public Platform
	{
	public:
		// Question 3: constructor - sets the starting position, ending position, width, and height of the platform, as well as the speed it moves at.
		VerticalMovingPlatform(const cocos2d::Vec2 STARTING_POS, const cocos2d::Vec2 ENDING_POS, float width, float height, const float SPEED = 1.0F);

		void update(float deltaTime); // Question 6: update function

	private:
		// Question 3: Vertically Moving Platform Member Variables
		const float SPEED; // the speed the platform goes that
		const cocos2d::Vec2 STARTING_POS; // the starting position of the platform
		const cocos2d::Vec2 ENDING_POS; // the ending position of the platform

		bool moveUp = true; // used so the program knows what direction the platform is going.

	protected:

	};

	// Question 2: Horizontally Moving Platform
	class HorizontallyMovingPlatform : public Platform
	{
	public:
		// Question 3: constuctor
		HorizontallyMovingPlatform(const cocos2d::Vec2 STARTING_POS, const cocos2d::Vec2 ENDING_POS, float width, float height, const float SPEED = 1.0F);

		void update(float deltaTime); // Question 6: update function

	private:
		// Question 3: Horizontally Moving Platform Member Variables
		const float SPEED; // the speed that the platform moves at.
		const cocos2d::Vec2 STARTING_POS; // the starting position of the platform
		const cocos2d::Vec2 ENDING_POS; // the ending position of the platform

		bool moveRight = true; // used so the program knows what direction the platform is moving.

	protected:

	};

	// Question 2: Rotating Platform
	class RotatingPlatform : public Platform
	{
	public:
		// sets the position, width, and height of the roating platform, as well as its speed, and its direction.
		// if CLOCKWISE is set to 'true', then the platform rotates clockwise. If set to false, it's counter clockwise.
		RotatingPlatform(cocos2d::Vec2 position, float width, float height, const float SPEED = 1.0F, const bool CLOCKWISE = false);

		void update(float deltaTime); // Question 7: update function

	private:

		// Question 4: Rotating Platform Member Variables
		const float SPEED; // the speed that the platform moves at
		const bool CLOCKWISE; // whether the platform is spinning clockwise or not

	protected:

	};

	// The Platform Manager
	class PlatformManager
	{
	public:
		PlatformManager();
		~PlatformManager(); // Destructor


		void Add(Platform *); // adds a platform to the platform manager

		void Subtract(Platform *); // subtracts a platform from the platform manager.

		void operator+=(Platform *); // (+) operator - adds in passed object

		void operator-=(Platform *); // (-) operator - removes passed object

		Platform * operator[](const unsigned int index); // ([]) operator - gets platform stored at provided index

		cocos2d::DrawNode * Generate(); // populates the platform vector (generating terrain)

		void Generate(cocos2d::Scene * scene); // populates the provided scene. This uses the generate function above.

		void update(float deltaTime); // Question 8: update function for Platform Manager

	private:
		std::vector<Platform *> m_Platforms; // platform pointer

	protected:
	};
}
