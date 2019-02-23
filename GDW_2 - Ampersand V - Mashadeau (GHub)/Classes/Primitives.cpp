
// Question 1: Primitive.h Creation
#include "2d/CCDrawNode.h"
#include "math/Mat4.h"
#include "Primitives.h"
#include <iostream>

///// SQUARE /////////////////////////////////////////////////////////////////////////////
// Question 3: initalization of the DrawNode (Square)
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition, const cocos2d::Color4F colour) 
	: m_Node(cocos2d::DrawNode::create()), m_WIDTH(abs((a_EndPosition - a_StartPosition).x)), m_HEIGHT(abs((a_EndPosition - a_StartPosition).y))
{
	m_Node->setAnchorPoint(cocos2d::Vec2(0.5F, 0.5F));
	m_Node->drawRect(a_StartPosition, a_EndPosition, colour);
	
	m_Position = a_StartPosition + (a_EndPosition - a_StartPosition) / 2; // gets the location of the primitive.
}

// creates a rect based on a position, length, and width provided by the user. This is based on the middle of the rect.
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 location, const float width, const float height, const cocos2d::Color4F colour)
	: m_Node(cocos2d::DrawNode::create()), m_WIDTH(width), m_HEIGHT(height)
{
	m_Node->drawRect(cocos2d::Vec2(location.x - width / 2, location.y - height / 2), cocos2d::Vec2(location.x + width / 2, location.y + height / 2), colour);
	m_Position = location; // saves the location of the square.
}

// creates a rect based on a given position and side length; this is guaranteed to be a square. This is based on the middle of the square.
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 location, const float sideLength, const cocos2d::Color4F colour) : PrimitiveSquare(location, sideLength, sideLength, colour) {}

// called when deleting the square
OOP::PrimitiveSquare::~PrimitiveSquare() { m_Node->release(); }

// Question 4: returns the square primitive
cocos2d::DrawNode * OOP::PrimitiveSquare::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
cocos2d::Vec2 OOP::PrimitiveSquare::getPosition() const { return m_Position; }

// sets the position of the primitive.
void OOP::PrimitiveSquare::setPosition(cocos2d::Vec2 position)
{
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	// m_Node->setPosition(m_Node->getPosition() - this->m_Position - position);
	if (m_Node == nullptr)
		std::cout << "What?" << std::endl;

	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	m_Position = position;
}

// returns the rectangle object representing the primitive graphic.
cocos2d::Rect OOP::PrimitiveSquare::getRect() const { return cocos2d::Rect(m_Position.x - m_WIDTH / 2, m_Position.y - m_HEIGHT / 2, m_WIDTH, m_HEIGHT); }

// sets the visibility of the primitive.
void OOP::PrimitiveSquare::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
void OOP::PrimitiveSquare::setVisible() { setVisible(!m_Node->isVisible()); }


///// CIRCLE /////////////////////////////////////////////////////////////////////////////
// initalizes the drawNode
OOP::PrimitiveCircle::PrimitiveCircle(cocos2d::Vec2 location, float radius, const cocos2d::Color4F colour) : m_Node(cocos2d::DrawNode::create()), m_RADIUS(abs(radius))
{
	m_Node->drawCircle(location, abs(radius), 20.0F, 30, false, cocos2d::Color4F(0.0, 0.0F, 1.0F, 1.0F));
	m_Position = location;
}

OOP::PrimitiveCircle::~PrimitiveCircle() { m_Node->release(); }

// Returns the circle primitive
cocos2d::DrawNode * OOP::PrimitiveCircle::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
cocos2d::Vec2 OOP::PrimitiveCircle::getPosition() const { return m_Position; }

// sets the position of the primitive.
void OOP::PrimitiveCircle::setPosition(cocos2d::Vec2 position)
{
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	this->m_Position = position;
}

// sets the visibility of the primitive.
void OOP::PrimitiveCircle::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
void OOP::PrimitiveCircle::setVisible() { setVisible(!m_Node->isVisible()); }


///// LINE ///////////////////////////////////////////////////////////////////////////////
// initalization of the DrawNode (Line)
OOP::PrimitiveLine::PrimitiveLine(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const cocos2d::Color4F colour)
	: m_Node(cocos2d::DrawNode::create()), m_DISTANCE(cocos2d::Vec2((endingPoint - startingPoint).x, (endingPoint - startingPoint).y)),
	m_LENGTH (sqrt(pow((endingPoint - startingPoint).x, 2) + pow((endingPoint - startingPoint).y, 2)))
{
	m_Node->drawLine(startingPoint, endingPoint, colour); // creating the line
	m_Position = startingPoint + (endingPoint - startingPoint) / 2; // gets the location of the primitive.
}

OOP::PrimitiveLine::~PrimitiveLine() { m_Node->release(); }

// Question 4: returns the line primitive
cocos2d::DrawNode * OOP::PrimitiveLine::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
cocos2d::Vec2 OOP::PrimitiveLine::getPosition() const { return m_Position; }

// sets the position of the primitive.
void OOP::PrimitiveLine::setPosition(cocos2d::Vec2 position)
{
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	this->m_Position = position;
}

// sets the visibility of the primitive.
void OOP::PrimitiveLine::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
void OOP::PrimitiveLine::setVisible() { setVisible(!m_Node->isVisible()); }



//// CAPSULE /////////////////////////////////////////////////////////////////////////////
// creates a capsule
OOP::PrimitiveCapsule::PrimitiveCapsule(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, float radius, const cocos2d::Color4F colour) : m_Node(cocos2d::DrawNode::create()), m_RADIUS(abs(radius))
{
	// Works when angle is greater than 3.14 rad, or when a 90 degree angle

	// The 'triangle' variable is used to save the three sides of a triangle that represents the distance between the starting point and ending point.
	/*
		* x: the 'x' distance between the two points. This is the base of the triangle.
		* y: the 'y' distance between the two points. This is the height of the traingle.
		* z: the distance between the starting point and ending point. This is the hypotenuse of the triangle.
	*/
	cocos2d::Vec3 triangle;

	float angle = 0.0F; // the angle of rotation used on the lines.
	cocos2d::Vec2 offset(0, radius); // used to offset the location of the lines. By default, lines are connected to the centres of the two circles.
	cocos2d::Vec2 tempVec; // a temporary vector used for swapping values.

	radius = abs(radius); // making the radius positive.

	// if the ending point is below te starting point, they're swapped so the calculation works.
	if (endingPoint.x < startingPoint.x)
	{
		tempVec = endingPoint;
		endingPoint = startingPoint;
		startingPoint = tempVec;
	}

	// gets the difference between the two points, i.e. an x distance and y distance. This results in a vector, and is used to form the triangle.
	triangle = cocos2d::Vec3(endingPoint.x - startingPoint.x, endingPoint.y - startingPoint.y, 0); // gets the base and height of the triangle.

	// gets the distance between the points via the Pythagorean theorem. This is saved as the 'z' value of the triangle (Vec3) variable.
	triangle.z = sqrt(pow(triangle.x, 2) + pow(triangle.y, 2));

	// uses trigonemtry (sine (SOH), cosine (CAH) and tangent (TOA)) to get the angle between the two circles, based on their centre points.
	angle = asinf(triangle.y / triangle.z); // gets the angle of the triangle

	// rotates the coordinate points using a rotation matrix. Well, it technically ISN'T using a matrix, but it's modeled after a rotation matirx.
	// This uses a rotation matrix setup, which is modeled below. With matricies, the calculation would be done in the way shown below, which is what was implemented.
	// [ cos a , -sin a] [x] = [ xcos a - ysin a ]
	// [ sin a ,  cos a] [y] = [ xsin a + ycos a ]

	// angle = M_PI - angle; // flips the angle to the adjacent quadrant. Used to move the centre lines.
	offset = cocos2d::Vec2(offset.x * (cosf(angle)) - offset.y * (sinf(angle)), offset.x * (sinf(angle)) + offset.y * (cosf(angle)));


	// drawing the starting and ending circles
	m_Node->drawCircle(startingPoint, radius, 0.0F, 30, false, colour);
	m_Node->drawCircle(endingPoint, radius, 0.0F, 30, false, colour);

	// drawing the two lines
	m_Node->drawLine(startingPoint + offset, endingPoint + offset, colour);
	m_Node->drawLine(startingPoint - offset, endingPoint - offset, colour);

	m_Position = startingPoint + (endingPoint - startingPoint) / 2; // saves the location of the primitive.

}

// destructor for a capsule
OOP::PrimitiveCapsule::~PrimitiveCapsule() { m_Node->release(); }

// returns the capsule primitive
cocos2d::DrawNode * OOP::PrimitiveCapsule::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
cocos2d::Vec2 OOP::PrimitiveCapsule::getPosition() const { return m_Position; }

// sets the position of the primitive.
void OOP::PrimitiveCapsule::setPosition(cocos2d::Vec2 position)
{
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	
	// changes the positions of the circles
	m_Circle1 += position - m_Position;
	m_Circle2 += position - m_Position;

	this->m_Position = position;
}

// gets the starting circle of the capsule
cocos2d::Vec2 OOP::PrimitiveCapsule::getCirclePosition1() const { return m_Circle1; }

// gets the ending circle of the capsule
cocos2d::Vec2 OOP::PrimitiveCapsule::getCirclePosition2() const { return m_Circle2; }

// sets the visibility of the primitive.
void OOP::PrimitiveCapsule::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
void OOP::PrimitiveCapsule::setVisible() { setVisible(!m_Node->isVisible()); }

///// GRID ///////////////////////////////////////////////////////////////////////////////
// creates a grid
OOP::PrimitiveGrid::PrimitiveGrid(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const float squareSize, const cocos2d::Color4F colour, const bool gridBox)
	: m_Node(cocos2d::DrawNode::create()), m_WIDTH(abs((startingPoint - endingPoint).x)), m_HEIGHT(abs((startingPoint - endingPoint).y)), m_SQUARE_SIZE(squareSize)
{
	cocos2d::Vec2 tempVec;
	m_Node->setAnchorPoint(cocos2d::Vec2(0.5F, 0.5F));

	if (startingPoint.x > endingPoint.x) // switches the start point and end point if the ending point is before the starting point.
	{
		tempVec = startingPoint;
		startingPoint = endingPoint;
		endingPoint = tempVec;
	}

	// draws horizontal lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.y + i < endingPoint.y; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(0.0F, i), cocos2d::Vec2(endingPoint.x, startingPoint.y + i), colour); // draws a horizontal line

	// vertical lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.x + i < endingPoint.x; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(i, 0.0F), cocos2d::Vec2(startingPoint.x + i, endingPoint.y), colour); // draws a vertical line


	// if 'gridBox' is 'true', then a quadrilateral is drawn around the whole grid.
	if (gridBox)
		m_Node->drawRect(startingPoint, endingPoint, colour);

	m_Position = startingPoint + (endingPoint - startingPoint) / 2; // gets the location of the primitive.
}

// creates a grid using a size and position instead of a starting point and ending point.
OOP::PrimitiveGrid::PrimitiveGrid(cocos2d::Vec2 position, cocos2d::Size size, const float squareSize, const cocos2d::Color4F colour, const bool gridBox)
{
	OOP::PrimitiveGrid(cocos2d::Vec2(position - (size / 2)), cocos2d::Vec2(position + (size / 2)), squareSize, colour, gridBox); // the position is based on the middle of the grid
}

// releases the grid node.
OOP::PrimitiveGrid::~PrimitiveGrid() { m_Node->release(); }

// returns the grid primitive.
cocos2d::DrawNode * OOP::PrimitiveGrid::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
cocos2d::Vec2 OOP::PrimitiveGrid::getPosition() const { return m_Position; }

// sets the position of the primitive.
void OOP::PrimitiveGrid::setPosition(cocos2d::Vec2 position)
{
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	this->m_Position = position;
}

// sets the visibility of the primitive.
void OOP::PrimitiveGrid::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
void OOP::PrimitiveGrid::setVisible() { setVisible(!m_Node->isVisible()); }

