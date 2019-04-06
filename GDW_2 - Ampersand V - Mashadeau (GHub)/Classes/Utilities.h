/*
Project: Mashadeau: Sorcerer's Quest (Game Development Workshop II (INFR 1396U) Video Game)
Team: Ampersand V (&V)
	- Caleb Birnie (100699828)
	- Carter Menary (100700587)
	- Devin Fitzpatrick (100709082)
	- Nathan Tuck (100708651)
	- Roderick “R.J.” Montague (100701758)
	- Jason Lee (100698121)
		*Jason Lee was only part of this group for the purposes of Digital Game Design.
		*Jason is not in Essential Mathematics for Games II, Object Oriented Programming, or Game Development Workshop II.
Date: 04/03/2019
*/

// This namespace stores utility functions for general programming use. This is the header for this namespace.
#include "cocos2d.h"
#include <string>
#include <vector>

using namespace cocos2d;

#pragma once
namespace ustd // standard, non-specific utilities.
{
	// converts a whole string to lowercase.
	std::string toLower(std::string);

	// converts a whole string to uppercase.
	std::string toUpper(std::string);

	// capitalizes a string, making all but the first character lowercase.
	std::string captialize(std::string);

	// checks if two strings are equal, ignoring case diffrences.
	bool equalsIgnoreCase(std::string, std::string);

	// checks to see if a string is an integer.
	bool isInt(std::string str);

	// checks to see if a string is a decimal, which would be a 'float' or 'double'. However, the string is validated under the assumption it will become a double.
	bool isDecimal(std::string str);

	template<typename T>
	void addToVector(std::vector<T *> & vector, T * val) // adds an element to a pointer vector if it isn't already in there. Because this is a template, the definition is placed here.
	{
		for (T * item : vector) // if the vector already contains the pointer, it is not added.
		{
			if (item == val)
				return;
		}

		vector.push_back(val);
	}

	template<typename T>
	void removeFromVector(std::vector<T *> & vector, T * val) // removes an element from a vector if it is present. This is placed in the header because it is a template function.
	{
		for (int i = 0; i < vector.size(); i++)
		{
			if (vector.at(i) == val) // if the pointer has been found, it is removed.
			{
				vector.erase(vector.begin() + i);
				return;
			}
		}
	}
}


namespace umath // mathematic utilities.
{
	// calculates circle collision; returns true if collision, or at least touching.
	bool circleCollision(const Vec2 pos1, const float radius1, const Vec2 pos2, const float radius2);

	// collision between two rectangles (rectangle A and rectangle B). Takes the minimums and maximums of the two rectangles as Vec2s.
	bool aabbCollision(const Vec2 aMin, const Vec2 aMax, const Vec2 bMin, const Vec2 bMax);

	// calculates axis-aligned bounding box collision using the four corner points of both boxes.
	static bool aabbCollision(const Vec2 topLeftA, const Vec2 topRightA, const Vec2 bottomLeftA, const Vec2 bottomRightA, const Vec2 topLeftB, const Vec2 topRightB, const Vec2 bottomLeftB, const Vec2 bottomRightB);

	// gets two cocos2d rectangles and calculates AABB collision. There is a built-in algorithim for this, so our own math is not used.
	bool aabbCollision(const Rect * rect1, const Rect * rect2);

	// calculates obb collision between two rectangles; this assumes that the rotation angles are based on the middle of the rectangtles.
	// if 'inDegrees' is true, then the angles are converted from degrees to radians. This is because cocos2d uses degrees, but C++ by default uses radians, which is what's needed for our rotations.
	bool obbCollision(Rect & rect1, float angle1, Rect & rect2, float angle2, bool inDegrees = true);

	// calculates oriented bounding box collision. Rotation factor is in RADIANS.
	// if IS_ROTATED is true, the points passed have already had their rotation factor applied to them.
	// if IS_ROTATED is false, the points passed have not been rotated, and the function will automatically rotate them.
	bool obbCollision(const Vec2 topLeftA, const Vec2 topRightA, const Vec2 bottomLeftA, const Vec2 bottomRightA, const float thetaA, const Vec2 topLeftB, const Vec2 topRightB, const Vec2 bottomLeftB, const Vec2 bottomRightB, const float thetaB, const bool IS_ROTATED = false);

	// checks collision between an aabb and a circle using built-in cocos algorithms.
	bool aabbCircleCollision(const Rect & rect, const Vec2 circlePos, const float radius);

	// conversion from degrees to radians. 1 degree = pi/180 radians. 
	float degreesToRadians(float degrees);

	// conversion from radians to degrees. 1 radian = 180/pi degrees.
	float radiansToDegrees(float radians);

	// rotates the provided point. The value of 'inDegrees' determines whether the provided angle is in degrees, or in radians.
	// the angle needs to be in radians for the rotation to work, so if it is provided in degrees, a conversion is necessary.
	Vec2 rotate(Vec2 points, float angle, bool inDegrees = false);

	// Returns a random number starting form 'lbound' upto ubound.
	// If 'includeUbound' is set to 'true', it's upto and including ubound. If it's false, it's upto but not including ubound. False by default.
	int randInt(int lBound, int uBound, bool includeUBound = false);
}

