#include "Utilities.h"
#include <math.h>

/// STRING AND GENERAL FUNCTIONS //////////////////////////////////////////////////////
std::string ustd::toLower(std::string str)
{
	// returns the string if its of length zero.
	if (str.length() == 0)
		return str;

	std::string strL; // temporary string
	strL.assign(str); // copies original string

	for (int i = 0; i < strL.length(); i++)
	{
		strL.at(i) = tolower(strL.at(i)); // converts each 'char' to its lowercase version if applicable
	}

	return strL;
}

// converts a whole string to uppercase
std::string ustd::toUpper(std::string str)
{
	// returns the string if its of length zero.
	if (str.length() == 0)
		return str;

	std::string strL; // temporary string
	strL.assign(str); // copies original string

	for (int i = 0; i < strL.length(); i++)
	{
		strL.at(i) = toupper(strL.at(i)); // converts each 'char' to its uppercase version if applicable
	}

	return strL;
}

// capitalizes a string.
std::string ustd::captialize(std::string str)
{
	// returns the string if its of length zero.
	if (str.length() == 0)
		return str;

	std::string strL; // temporary string
	strL.assign(str); // copies original string

	str = toLower(str); // makes the string all lowercase
	str.at(0) = toupper(str.at(0)); // capitalizes the first letter

	return strL;
}

// checks if two strings are equal, ignoring case diffrences.
bool ustd::equalsIgnoreCase(std::string str1, std::string str2)
{
	// making both strings lowercase
	str1 = toLower(str1);
	str2 = toLower(str2);
	return str1 == str2; // returning whether the two are equal
}

// checks if a string is an integer.
bool ustd::isInt(std::string str)
{
	int strInt; // gets the string as an int.
	std::stringstream ss(str); // creates a string stream for converting the string to an integer.

	ss >> strInt; // puts the string stream into the integer. If non-int values exist, then the int is truncated.

	return std::to_string(strInt) == str; // returns 'true' if all values were carried over from the string.
}

// checks if a string is a decimal number (specifically a double).
bool ustd::isDecimal(std::string str)
{
	double strDbl; // gets the string as an float
	std::stringstream ss(str); // creates a string stream for converting the string to an integer.

	ss >> strDbl; // puts the string stream into the double. If non-int values exist, then the doubleis truncated.

	return std::to_string(strDbl) == str; // returns 'true' if all values were carried over from the string.
}

/// MATH /////////////////////////////////////////////////////////////////////////////

// returns true if two circles are colliding or touching.
bool umath::circleCollision(Vec2 pos1, float radius1, Vec2 pos2, float radius2)
{
	int dist = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2)); // calculates the distance between the two circles.
	return (dist <= radius1 + radius2);	
}

// calculates AABB collision with two rectangles based on a passed minimum and maximum value for both.
// Takes the minimum and maximum of the two rectangles.
bool umath::aabbCollision(const Vec2 aMin, Vec2 aMax, Vec2 bMin, Vec2 bMax)
{
	// booleans for collision checks
	bool xCol, yCol;

	// xCol gets the result of this collision check. If the projection on the x-axis shows collision, then xCol is set to true.
	xCol = ((bMin.x > aMin.x && bMin.x < aMax.x) ^ (aMin.x > bMin.x && aMin.x < bMax.x));

	//  yCol gets the result of this collision check. If the projection on the y-axis shows collision, yCol is set to true.
	yCol = ((bMin.y > aMin.y && bMin.y < aMax.y) ^ (aMin.y > bMin.y && aMin.y < bMax.y));

	// if the x-collision and y-collision return positive, then there is collision.
	return (xCol && yCol);
}

// calculates rectnagle collision using two cocos2d rectangles
bool umath::aabbCollision(const Rect * rect1, const Rect * rect2)
{
	return rect1->intersectsRect(*rect2);
	// Reuses the other collison check.
	//return umath::aabbCollision(Vec2(rect1->getMinX(), rect1->getMinY()), Vec2(rect1->getMaxX(), rect1->getMaxY()), Vec2(rect2->getMinX(), rect2->getMinY()), Vec2(rect2->getMaxX(), rect2->getMaxY()));
}

// calculates obb collision between two rectangles; this assumes that the rotation angles are based on the middle of the rectanges.
//  The angle is IN RADIANS.
bool umath::obbCollision(Rect rectA, float angleA, Rect rectB, float angleB)
{
	float theta = angleB - angleA; // gets the difference between the two angles.
	
	bool collision(false);

	Rect tempRect; // a temporary rectangle used to check for collisions.
	Vec2 tempPos; // saves the position of a rectangle temporarily, which would be their midX and midY values.
	
	Vec2 rectVerts[4]; // saves the 4 corner points of rectangle 2
	Vec2 minXY; // saves the minimum vertex points of rectangle 2
	Vec2 maxXY; // saves the maximum vertex points of rectangle 2

	for (int check = 1; check <= 2; check++) // does the two checks to see if there is collision. This requires two check total.
	{
		tempPos = Vec2(rectB.getMidX(), rectB.getMidY()); // gets the position of rect2 (based on its centre)

		// gets the corners of the rectangle.
		rectVerts[0] = Vec2(rectB.getMinX(), rectB.getMaxY()); // top left corner
		rectVerts[1] = Vec2(rectB.getMaxX(), rectB.getMaxY()); // top right corner
		rectVerts[2] = Vec2(rectB.getMinX(), rectB.getMinY()); // bottom left corner
		rectVerts[3] = Vec2(rectB.getMaxX(), rectB.getMinY()); // bottom right corner

		// rotates the four corner points after offsetting them by their position.
		rectVerts[0] = rotate(rectVerts[0] - tempPos, theta);
		rectVerts[1] = rotate(rectVerts[1] - tempPos, theta);
		rectVerts[2] = rotate(rectVerts[2] - tempPos, theta);
		rectVerts[3] = rotate(rectVerts[3] - tempPos, theta);

		// puts the rectangle back where it was before.
		rectVerts[0] += tempPos;
		rectVerts[1] += tempPos;
		rectVerts[2] += tempPos;
		rectVerts[3] += tempPos;

		// these would normally be the min and max values of an unrotated rectangle. However, it still needs to be checked.
		minXY = rectVerts[2];
		maxXY = rectVerts[1];

		// gets the minimum x and y points of the rotated rectB
		for (int i = 0; i < 4; i++)
		{
			if (rectVerts[i].x < minXY.x)
				minXY.x = rectVerts[i].x;

			if (rectVerts[i].y < minXY.y)
				minXY.y = rectVerts[i].y;
		}

		// gets the maximum x and y points of the rotated rectB
		for (int i = 0; i < 4; i++)
		{
			if (rectVerts[i].x > maxXY.x)
				maxXY.x = rectVerts[i].x;

			if (rectVerts[i].y > maxXY.y)
				maxXY.y = rectVerts[i].y;
		}

		// checks to see if the two rectangles are colliding.
		collision = aabbCollision(Vec2(rectA.getMinX(), rectA.getMinY()), Vec2(rectA.getMaxX(), rectA.getMaxY()), minXY, maxXY);

		if (collision == false) // if the collision is set to 'false', then there is no need to do another check; there is no collision.
			return false;

		// switches the rectangles around so that the check can be done again.
		tempRect = rectA;
		rectA = rectB;
		rectB = tempRect;
	}

	return collision;
}

// checks collision between an aabb and a circle using built in cocos algorithms.
bool umath::aabbCircleCollision(const Rect * rect, Vec2 circlePos, float radius) { return rect->intersectsCircle(circlePos, radius); }

// converts from degrees to radians
float umath::degreesToRadians(float degrees) { return degrees * (M_PI / 180); }

// converts from radians to degrees
float umath::radiansToDegrees(float radians) { return radians * (180 / M_PI); }

// a rotation function. While it doesn't use a rotation matrix, it's modeled after how one would be used for a rotation.
//  The angle is IN RADIANS.
Vec2 umath::rotate(Vec2 points, float angle)
{
	// rotates the coordinate points using a rotation matrix. Well, it technically ISN'T using a matrix, but it's modeled after how two matrices would be multiplied with one another.
	// This uses a rotation matrix setup, which is modeled below. With matricies, the calculation would be done in the way shown below, which is what was harcoded below.
	// [ cos a , -sin a] [x] = [ xcos a - ysin a ]
	// [ sin a ,  cos a] [y] = [ xsin a + ycos a ]
	return cocos2d::Vec2(points.x * (cosf(angle)) - points.y * (sinf(angle)), points.x * (sinf(angle)) + points.y * (cosf(angle)));
}

// generates a random integer
int umath::randInt(int lBound, int uBound, bool includeUBound)
{
	int tempInt(0);
	int randInt(0);
	// If the upper and lower bounds on the same, it returns the lBound
	if (lBound == uBound)
	{
		return lBound;
	}
	// If the lower bound is greater than the upper bound, they are swapped
	else if (lBound > uBound)
	{
		tempInt = lBound;
		lBound = uBound;
		uBound = tempInt;
	}

	// If the upperbound is positive, the values can be used as is.
	// If the upperbound and lowerbound are both negative, then a randomizer is run to get their absoluted range, then another randomizer is run to make it positive or negative.

	randInt = (uBound > 0) ? rand() % (uBound - lBound + includeUBound) + lBound : (abs(uBound) - abs(lBound) + includeUBound) + abs(lBound);

	// If the number must be negative, it is multiplied by -1 to make it so.
	if (lBound < 0 & uBound < 0)
		randInt *= -1;
	randInt = rand() % (uBound - lBound + includeUBound) + lBound;

	return randInt;
}
