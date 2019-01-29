// Stores utility functions
#include <cocos2d.h>
#include <string>

using namespace cocos2d;

#pragma once
namespace ustd
{
	// converts a whole string to lowercase
	static std::string toLower(std::string);

	// converts a whole string to uppercase
	static std::string toUpper(std::string);

	// capitalizes a string, making all but the first character lowercase.
	static std::string captialize(std::string);

	// checks if two strings are equal, ignoring case diffrences.
	static bool equalsIgnoreCase(std::string, std::string);

	// checks to see if a string is a number; needs reworking.
	static bool isNum(std::string);
}


namespace umath
{
	// calculates circle collision; returns true if collision or at least touching. The cocos version will likely be used instead.
	static bool circleCollision(Vec2 pos1, float radius1, Vec2 pos2, float radius2);

	// conversion from degrees to radians. 1 degree = pi/180 radians. 
	static float degreesToRadians(float degrees);
	// conversion from radians to degrees. 1 radian = 180/pi degrees.
	static float radiansToDegrees(float radians);

	// Returns a random number starting form 'lbound' upto ubound.
	// If 'includeUbound' is set to 'true', it's upto and including ubound; if false, it's upto but not including ubound. False by default.
	static int randInt(int lBound, int uBound, bool includeUBound = false);
}

