// This is an import of the platform manager from Roderick (R.J.)'s assignment.

// Object Oriented Programming - Lab 5 | Pure Virtual Functions - Terrain Variability
// Question 1: PlatformManager.h Inclusion

#pragma once
#include "Primitives.h"
#include "cocos/2d/CCScene.h"

#include <vector>
#include <string>

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
		
		// gets the position of the platform.
		cocos2d::Vec2 getPosition();

		// Question 2: a pure virtual setPosition() function
		virtual void setPosition(cocos2d::Vec2 position) = 0; // sets the position of the platform

		// Question 2: a pure virtual toString() function.
		virtual std::string toString() = 0; // pure virtual toString() function

		// Question 2: pure virutal function
		virtual void update(float deltaTime) = 0; // changed into pure virtual

	private:
		OOP::PrimitiveSquare * m_Square; // PrimitiveSquare variable.
		
	protected:
		

	};
	
	// Vertical Moving Platform
	class VerticalMovingPlatform : public Platform
	{
	public:
		// constructor - sets the starting position, ending position, width, and height of the platform, as well as the speed it moves at.
		VerticalMovingPlatform(const cocos2d::Vec2 STARTING_POS, const cocos2d::Vec2 ENDING_POS, float width, float height, const float SPEED = 1.0F);

		void setPosition(cocos2d::Vec2 position) override; // Question 4: a position setter for the vertical moving platform

		std::string toString() override; // Question 3: toString for vertical moving platform

		void update(float deltaTime) override; // update function

	private:
		// Vertically Moving Platform Member Variables
		const float SPEED; // the speed the platform goes that
		cocos2d::Vec2 STARTING_POS; // the starting position of the platform
		cocos2d::Vec2 ENDING_POS; // the ending position of the platform

		bool moveUp = true; // used so the program knows what direction the platform is going.

	protected:
		
	};

	// Horizontally Moving Platform
	class HorizontallyMovingPlatform : public Platform
	{
	public:
		// constuctor
		HorizontallyMovingPlatform(const cocos2d::Vec2 STARTING_POS, const cocos2d::Vec2 ENDING_POS, float width, float height, const float SPEED = 1.0F);
		
		void setPosition(cocos2d::Vec2 position) override; // Question 4: a position setter for the horizontal moving platform

		std::string toString() override; // Question 3: toString for horizontal moving platform

		void update(float deltaTime) override; // update function

	private:
		// Horizontally Moving Platform Member Variables
		const float SPEED; // the speed that the platform moves at.
		cocos2d::Vec2 STARTING_POS; // the starting position of the platform
		cocos2d::Vec2 ENDING_POS; // the ending position of the platform

		bool moveRight = true; // used so the program knows what direction the platform is moving.

	protected:
		
	};

	// Rotating Platform
	class RotatingPlatform : public Platform
	{
	public:
		// sets the position, width, and height of the roating platform, as well as its speed, and its direction.
		// if CLOCKWISE is set to 'true', then the platform rotates clockwise. If set to false, it's counter clockwise.
		RotatingPlatform(cocos2d::Vec2 position, float width, float height, const float SPEED = 1.0F, const bool CLOCKWISE = false);

		void setPosition(cocos2d::Vec2 position) override; // Question 4: a position setter for the rotating platform

		std::string toString() override; // Question 3: toString for rotating platform

		void update(float deltaTime) override; // update function

	private:

		// Rotating Platform Member Variables
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

		void update(float deltaTime); // update function for Platform Manager

	private:
		std::vector<Platform *> m_Platforms; // platform pointer

	protected:
	};
}
