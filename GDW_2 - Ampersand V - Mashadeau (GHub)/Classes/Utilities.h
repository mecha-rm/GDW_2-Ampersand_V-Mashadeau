// Stores utility functions
#include "cocos2d.h"
#include <string>

using namespace cocos2d;

#pragma once
namespace ustd
{
	// converts a whole string to lowercase
	std::string toLower(std::string);

	// converts a whole string to uppercase
	std::string toUpper(std::string);

	// capitalizes a string, making all but the first character lowercase.
	std::string captialize(std::string);

	// checks if two strings are equal, ignoring case diffrences.
	bool equalsIgnoreCase(std::string, std::string);

	// checks to see if a string is an integer; this is improved from isNum.
	bool isInt(std::string str);

	// checks to see if a string is a decimal, which would be a float or double. However, it is validated under the assumption it will become a double.
	bool isDecimal(std::string str);
}


namespace umath
{
	// calculates circle collision; returns true if collision or at least touching. The cocos version will likely be used instead.
	bool circleCollision(const Vec2 pos1, const float radius1, const Vec2 pos2, const float radius2);

	// collision between two rectangles (rectangle A and rectangle B)
	// Takes the minimum and maximum of the two rectangles as Vec2s.
	bool aabbCollision(const Vec2 aMin, const Vec2 aMax, const Vec2 bMin, const Vec2 bMax);

	// gets two cocos2d rectangles and calculates AABB collision
	bool aabbCollision(const Rect * rect1, const Rect * rect2);

	// calculates obb collision between two rectangles; this assumes that the rotation angles are based on the middle of the rectanges.
	//  The angle is IN RADIANS.
	bool obbCollision(Rect rect1, float angle1, Rect rect2, float angle2);

	// checks collision between an aabb and a circle using built in cocos algorithms.
	bool aabbCircleCollision(const Rect * rect, Vec2 circlePos, float radius);

	// conversion from degrees to radians. 1 degree = pi/180 radians. 
	float degreesToRadians(float degrees);

	// conversion from radians to degrees. 1 radian = 180/pi degrees.
	float radiansToDegrees(float radians);

	// rotates the provided points. The angle is IN RADIANS.
	Vec2 rotate(Vec2 points, float angle);

	// Returns a random number starting form 'lbound' upto ubound.
	// If 'includeUbound' is set to 'true', it's upto and including ubound; if false, it's upto but not including ubound. False by default.
	int randInt(int lBound, int uBound, bool includeUBound = false);
}

