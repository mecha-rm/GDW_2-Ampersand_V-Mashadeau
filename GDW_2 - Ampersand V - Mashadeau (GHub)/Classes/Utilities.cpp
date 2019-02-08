#include "Utilities.h"

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

// checks to see if a string is a number; needs reworking.
bool ustd::isNum(std::string str)
{
	std::string arr[10] = { "1","2","3","4","5","6","7","8","9","0" };

	// Checks each index of the stirng, checking if it's a whole, numeric value.
	for (int x = 0; x < str.length(); x++) {
		for (int y = 0; y < 10; y++) {
			if (str.substr(x, 1) == arr[y]) {
				break;
			}
			else if (y == 9) {
				return false;
			}
		}
	}
	return true;
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
	// Reuses the other collison check.
	return umath::aabbCollision(Vec2(rect1->getMinX, rect1->getMinY), Vec2(rect1->getMaxX, rect1->getMaxY), Vec2(rect2->getMinX, rect2->getMinY), Vec2(rect2->getMaxX, rect2->getMaxY));
}

// converts from degrees to radians
float umath::degreesToRadians(float degrees) { return degrees * (M_PI / 180); }

// converts from radians to degrees
float umath::radiansToDegrees(float radians) { return radians * (180 / M_PI); }

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
