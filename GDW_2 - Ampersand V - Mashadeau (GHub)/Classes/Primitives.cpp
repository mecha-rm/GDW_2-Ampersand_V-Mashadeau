
// Question 1: Primitive.h Creation
// #include "2d/CCDrawNode.h"
// #include "math/Mat4.h"
#include "Primitives.h"
#include "Utilities.h"
#include <iostream>



///// GENERAL PRIMITIVE //////////////////////////////////////////////////////////////////////////
OOP::Primitive::Primitive() : m_Node(cocos2d::DrawNode::create()) 
{ 
	m_Node->setGlobalZOrder(10.1F); // since primitives are treated as collision shapes, they have the global z order of  10.1F.
	m_Node->setVisible(false); // hides the draw node from view.
}

// releases the drawNode. This was originally done in every destructor, but now only happens here.
OOP::Primitive::~Primitive() { m_Node->release(); }

// returns the primitive.
cocos2d::DrawNode * OOP::Primitive::getPrimitive() const { return m_Node; }

// gets the position of the drawNode.
cocos2d::Vec2 OOP::Primitive::getPosition() const { return m_Node->getPosition(); }

// sets the rotation of the primitive IN DEGREES.
void OOP::Primitive::setRotation(float rotation) { m_Node->setRotation(rotation); }

// returns the rotation factor of the primitive IN DEGREES.
float OOP::Primitive::getRotation() { return m_Node->getRotation(); }

// sets the visibility of the collision shape.
void OOP::Primitive::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the collision shape.
void OOP::Primitive::setVisible() { setVisible(!m_Node->isVisible()); }

// gets the visibility of the m_Node
bool OOP::Primitive::isVisible() const { return m_Node->isVisible(); }

///// SQUARE /////////////////////////////////////////////////////////////////////////////
// Question 3: initalization of the DrawNode (Square)
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition, const cocos2d::Color4F colour) 
	: /*m_Node(cocos2d::DrawNode::create()),*/ m_WIDTH(abs((a_EndPosition - a_StartPosition).x)), m_HEIGHT(abs((a_EndPosition - a_StartPosition).y))
{
	// draws the rectangle
	m_Node->drawRect(cocos2d::Vec2(0.0F, 0.0F) - cocos2d::Vec2(m_WIDTH / 2, m_HEIGHT / 2), cocos2d::Vec2(0.0F, 0.0F) + cocos2d::Vec2(m_WIDTH / 2, m_HEIGHT / 2), colour);
	m_Node->setPosition((a_StartPosition + a_EndPosition) / 2); // sets the position to be the middle of the two corners of the quadrilateral.

	//m_Node->setAnchorPoint(cocos2d::Vec2(0.5F, 0.5F));
	//m_Node->drawRect(a_StartPosition, a_EndPosition, colour);
	//m_Position = a_StartPosition + (a_EndPosition - a_StartPosition) / 2; // gets the location of the primitive.
}

// creates a rect based on a position, length, and width provided by the user. This is based on the middle of the rect.
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 position, const float width, const float height, const cocos2d::Color4F colour)
	: /*m_Node(cocos2d::DrawNode::create()),*/ m_WIDTH(width), m_HEIGHT(height)
{
	// draws the rectangle at location (0, 0).
	m_Node->drawRect(cocos2d::Vec2(0.0F, 0.0F) - cocos2d::Vec2(width / 2, height / 2), cocos2d::Vec2(0.0F, 0.0F) + cocos2d::Vec2(width / 2, height / 2), colour);
	m_Node->setPosition(position); // sets the position of the node to be where the rectangle should be.

	// m_Node->drawRect(cocos2d::Vec2(position.x - width / 2, position.y - height / 2), cocos2d::Vec2(position.x + width / 2, position.y + height / 2), colour);
	// m_Position = position; // saves the location of the square.
}

// creates a rect based on a given position and side length; this is guaranteed to be a square. This is based on the middle of the square.
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 position, const float sideLength, const cocos2d::Color4F colour) : PrimitiveSquare(position, sideLength, sideLength, colour) {}

// called when deleting the square. The release of the node now happens in the base class.
OOP::PrimitiveSquare::~PrimitiveSquare() { /*m_Node->release();*/ }

// Question 4: returns the square primitive
cocos2d::DrawNode * OOP::PrimitiveSquare::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
// cocos2d::Vec2 OOP::PrimitiveSquare::getPosition() const { return m_Node->getPosition(); }

// sets the position of the primitive.
void OOP::PrimitiveSquare::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position); // changes the node's position.

	/*
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	// m_Node->setPosition(m_Node->getPosition() - this->m_Position - position);
	if (m_Node == nullptr)
		std::cout << "What?" << std::endl;

	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	m_Position = position;
	*/
}

// returns the rectangle object representing the primitive graphic.
cocos2d::Rect OOP::PrimitiveSquare::getRect() const { return cocos2d::Rect(m_Node->getPositionX() - m_WIDTH / 2, m_Node->getPositionY() - m_HEIGHT / 2, m_WIDTH, m_HEIGHT); }

// sets the visibility of the primitive.
// void OOP::PrimitiveSquare::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
// void OOP::PrimitiveSquare::setVisible() { setVisible(!m_Node->isVisible()); }


///// CIRCLE /////////////////////////////////////////////////////////////////////////////
// initalizes the drawNode
OOP::PrimitiveCircle::PrimitiveCircle(cocos2d::Vec2 location, float radius, const cocos2d::Color4F colour) : /*m_Node(cocos2d::DrawNode::create()),*/ m_RADIUS(abs(radius))
{
	m_Node->drawCircle(cocos2d::Vec2(0.0F, 0.0F), abs(radius), 20.0F, 30, false, cocos2d::Color4F(0.0, 0.0F, 1.0F, 1.0F)); // draws the circle at location (0, 0).
	m_Node->setPosition(location); // moves the circle to where it shoudld be.
	// m_Node->drawCircle(location, abs(radius), 20.0F, 30, false, cocos2d::Color4F(0.0, 0.0F, 1.0F, 1.0F));
	// m_Position = location;
}

OOP::PrimitiveCircle::~PrimitiveCircle() { /*m_Node->release();*/ }

// Returns the circle primitive
// cocos2d::DrawNode * OOP::PrimitiveCircle::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
// cocos2d::Vec2 OOP::PrimitiveCircle::getPosition() const { return m_Node->getPosition(); }

// sets the position of the primitive.
void OOP::PrimitiveCircle::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position); // changes the position of the draw node.
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	// m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	//this->m_Position = position;
}

// sets the visibility of the primitive.
// void OOP::PrimitiveCircle::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
// void OOP::PrimitiveCircle::setVisible() { setVisible(!m_Node->isVisible()); }


///// LINE ///////////////////////////////////////////////////////////////////////////////
// initalization of the DrawNode (Line)
OOP::PrimitiveLine::PrimitiveLine(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const cocos2d::Color4F colour)
	: /*m_Node(cocos2d::DrawNode::create()),*/ m_DISTANCE(cocos2d::Vec2(endingPoint - startingPoint)),
	m_LENGTH (sqrt(pow((endingPoint - startingPoint).x, 2) + pow((endingPoint - startingPoint).y, 2)))
{
	// draws the line with its centre at position (0.0F, 0.0F).
	m_Node->drawLine(cocos2d::Vec2(0.0F - abs(m_DISTANCE.x / 2), 0.0F - abs(m_DISTANCE.y / 2)), cocos2d::Vec2(0.0F + abs(m_DISTANCE.x / 2), 0.0F + abs(m_DISTANCE.y / 2)), colour);
	m_Node->setPosition((startingPoint + endingPoint) / 2); // sets the position of the node to where the shape should be.

	// m_Node->drawLine(startingPoint, endingPoint, colour); // creating the line
	// m_Position = startingPoint + (endingPoint - startingPoint) / 2; // gets the location of the primitive.
}


OOP::PrimitiveLine::~PrimitiveLine() { /*m_Node->release();*/ }

// Question 4: returns the line primitive
// cocos2d::DrawNode * OOP::PrimitiveLine::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
// cocos2d::Vec2 OOP::PrimitiveLine::getPosition() const { return m_Node->getPosition(); }

// sets the position of the primitive.
void OOP::PrimitiveLine::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position); // sets the position of the node.

	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	// m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	// this->m_Position = position;
}

// sets the visibility of the primitive.
// void OOP::PrimitiveLine::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
// void OOP::PrimitiveLine::setVisible() { setVisible(!m_Node->isVisible()); }


//// CAPSULE /////////////////////////////////////////////////////////////////////////////
// creates a capsule
OOP::PrimitiveCapsule::PrimitiveCapsule(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, float radius, const cocos2d::Color4F colour) : /*m_Node(cocos2d::DrawNode::create()),*/ m_RADIUS(abs(radius))
{
	// Works when angle is greater than 3.14 rad, or when a 90 degree angle

	// The 'triangle' variable is used to save the three sides of a triangle that represents the distance between the starting point and ending point.
	/*
		* x: the 'x' distance between the two points. This is the base of the triangle.
		* y: the 'y' distance between the two points. This is the height of the traingle.
		* z: the distance between the starting point and ending point. This is the hypotenuse of the triangle.
	*/
	cocos2d::Vec2 position; // saves where the capsule should be drawn. Remove this if you want to go back to the way it was before.
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

	position = (startingPoint + endingPoint) / 2; // gets the position of the capsule.

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
	
	/*
	// revised version. This is meant to draw an axis-aligned capsule that then gets rotated to where it should be. It doesn't work...
	m_Node->drawCircle(cocos2d::Vec2((startingPoint - position).x, 0.0F), radius, 0.0F, 30, false, colour);
	m_Node->drawCircle(cocos2d::Vec2((endingPoint - position).x, 0.0F), radius, 0.0F, 30, false, colour);

	m_Node->drawLine(startingPoint + offset - position, cocos2d::Vec2((endingPoint + offset - position).x, (startingPoint + offset - position).y), colour);
	m_Node->drawLine(startingPoint - offset - position, cocos2d::Vec2((endingPoint - offset - position).x, (startingPoint - offset - position).y), colour);
	*/

	// original drawLines
	// drawing the starting and ending circles. These now subtract the position of the capsule so that the centre is at (0, 0).
	m_Node->drawCircle(startingPoint - position, radius, 0.0F, 30, false, colour);
	m_Node->drawCircle(endingPoint - position, radius, 0.0F, 30, false, colour);

	// drawing the two lines.  These now subtract the position of the capsule so that the centre is at (0, 0).
	m_Node->drawLine(startingPoint + offset - position, endingPoint + offset - position, colour);
	m_Node->drawLine(startingPoint - offset - position, endingPoint - offset - position, colour);

	m_Node->setPosition(position); // sets the position of the drawNode to where the capsule should be.
	// m_Node->setRotation(m_theta);
	m_Circle1 = startingPoint; // saves the location of the starting point as the location of the first circle.
	m_Circle2 = endingPoint; // saves the location of the ending circle as the endingPoint of the capsule, which is where the circle was drawn.

	// m_Position = startingPoint + (endingPoint - startingPoint) / 2; // saves the location of the primitive.
	m_theta = angle; // saves the angle in degrees
}

// creates a capsule with a different way, re-using the other constructor. The angle is in DEGREES.
// This basically calculates where the ending points would be with the capsule the user is making.
OOP::PrimitiveCapsule::PrimitiveCapsule(cocos2d::Vec2 position, float length, float radius, const float angle, const cocos2d::Color4F colour)
	: PrimitiveCapsule(
		position + umath::rotate(cocos2d::Vec2(position.x - (abs(length) - abs(radius) / 2) / 2, position.y) - position, umath::degreesToRadians(angle)), 
		position + umath::rotate(cocos2d::Vec2(position.x + (abs(length) - abs(radius) / 2) / 2, position.y) - position, umath::degreesToRadians(angle)),
		radius, colour)
{
	// the code below is a more readiable way of how the calculation works.
	/*
	cocos2d::Vec2 capPos = position; // saves the position of the capsule.

	cocos2d::Vec2 startingPos{ capPos.x - (abs(length) - abs(radius)) / 2, capPos.y }; // calculates the starting position (i.e. the location of the first circle).
	cocos2d::Vec2 endingPos{ capPos.x + (abs(length) - abs(radius)) / 2, capPos.y }; // calculates the ending position (i.e. the location of the second circle).

	startingPos -= capPos; // moves the starting position (i.e. position of circle 1) so that it's proportional to the origin of the drawNode (0.0F, 0.0F).
	endingPos -= capPos; // moves the ending position (i.e. position of circle 2) so that it's proportional to the origin of the drawNode (0.0F, 0.0F).

	startingPos = umath::rotate(startingPos, angle); // rotates the startingPosition
	endingPos = umath::rotate(endingPos, angle); // rotates the endingPosition

	startingPos += capPos; // moves the capsule to where it should be.
	endingPos += capPos; // moves the capsule to where it should be.
	*/
}

// destructor for a capsule
OOP::PrimitiveCapsule::~PrimitiveCapsule() { /*m_Node->release();*/ }

// returns the capsule primitive
// cocos2d::DrawNode * OOP::PrimitiveCapsule::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
// cocos2d::Vec2 OOP::PrimitiveCapsule::getPosition() const { return m_Node->getPosition(); }

// sets the position of the primitive.
void OOP::PrimitiveCapsule::setPosition(cocos2d::Vec2 position)
{
	cocos2d::Vec2 oldPos = m_Node->getPosition(); // gets the old position of the capsule.

	m_Node->setPosition(position);
	m_Circle1 += position - oldPos; // gets the location of the new circle by offsetting it by how much the capsule moved.
	m_Circle2 += position - oldPos; // gets the location of the new circle by offsetting it by how much the capsule moved.

	/*
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	
	// changes the positions of the circles
	m_Circle1 += position - m_Position;
	m_Circle2 += position - m_Position;

	this->m_Position = position;
	*/
}

// gets the starting circle of the capsule
cocos2d::Vec2 OOP::PrimitiveCapsule::getCirclePosition1() const { return m_Circle1; }

// gets the ending circle of the capsule
cocos2d::Vec2 OOP::PrimitiveCapsule::getCirclePosition2() const { return m_Circle2; }

// sets the rotation factor of the capsule.
void OOP::PrimitiveCapsule::setRotation(float newTheta)
{
	float nodeTheta = m_Node->getRotation(); // gets the rotation factor of the drawNode (in degrees).
	float netTheta = newTheta - m_theta; // gets the net change in the capsule's rotation factor.

	m_Node->setRotation(m_Node->getRotation() + netTheta); // sets the node's rotation based on what the orientation of the capsule should be.
	m_theta = newTheta; // saves the rotation factor of the capsule.
}


// gets the rotation factor of the capsule.
float OOP::PrimitiveCapsule::getRotation() { return m_theta; }

// sets the visibility of the primitive.
// void OOP::PrimitiveCapsule::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
// void OOP::PrimitiveCapsule::setVisible() { setVisible(!m_Node->isVisible()); }

///// GRID ///////////////////////////////////////////////////////////////////////////////
// creates a grid
OOP::PrimitiveGrid::PrimitiveGrid(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const float squareSize, const cocos2d::Color4F colour, const bool gridBox)
	: /*m_Node(cocos2d::DrawNode::create()),*/ m_WIDTH(abs((startingPoint - endingPoint).x)), m_HEIGHT(abs((startingPoint - endingPoint).y)), m_SQUARE_SIZE(squareSize)
{
	const cocos2d::Vec2 POSITION = (startingPoint + endingPoint) / 2; // gets the position of the grid.
	cocos2d::Vec2 tempVec1;
	cocos2d::Vec2 tempVec2;

	if (startingPoint.x > endingPoint.x) // switches the start point and end point if the ending point is before the starting point.
	{
		tempVec1 = startingPoint;
		startingPoint = endingPoint;
		endingPoint = tempVec1;
	}

	tempVec1 = cocos2d::Vec2(0.0F, 0.0F) - cocos2d::Vec2((endingPoint - startingPoint) / 2); // gets the starting point of the graph with its centre at (0.0F, 0.0F)
	tempVec2 = cocos2d::Vec2(0.0F, 0.0F) + cocos2d::Vec2((endingPoint - startingPoint) / 2); // gets the ending point of the graph with its centre at (0.0F, 0.0F)

	startingPoint = tempVec1; // overrides the startingPoint so that it's in reference to the drawNode's origin (0.0F, 0.0F).
	endingPoint = tempVec2; // overrides the endingPoint so that it's in reference to the drawNode's origin (0.0F, 0.0F).

	// draws horizontal lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.y + i < endingPoint.y; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(0.0F, i), cocos2d::Vec2(endingPoint.x, startingPoint.y + i), colour); // draws a horizontal line

	// vertical lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.x + i < endingPoint.x; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(i, 0.0F), cocos2d::Vec2(startingPoint.x + i, endingPoint.y), colour); // draws a vertical line


	// if 'gridBox' is 'true', then a quadrilateral is drawn around the whole grid.
	if (gridBox)
		m_Node->drawRect(startingPoint, endingPoint, colour);

	m_Node->setPosition(POSITION); // sets the node to the position of the grid.
	m_Node->setGlobalZOrder(10.3F); // sets the global z order of the grid. This is different from the global z order of other primitives.

	/*
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
	*/
}

// creates a grid using a size and position instead of a starting point and ending point.
OOP::PrimitiveGrid::PrimitiveGrid(cocos2d::Vec2 position, cocos2d::Size size, const float squareSize, const cocos2d::Color4F colour, const bool gridBox)
{
	OOP::PrimitiveGrid(cocos2d::Vec2(position - (size / 2)), cocos2d::Vec2(position + (size / 2)), squareSize, colour, gridBox); // the position is based on the middle of the grid
}

// releases the grid node.
OOP::PrimitiveGrid::~PrimitiveGrid() { /*m_Node->release();*/ }

// returns the grid primitive.
// cocos2d::DrawNode * OOP::PrimitiveGrid::getPrimitive() const { return m_Node; }

// gets the position of the primitive square
// cocos2d::Vec2 OOP::PrimitiveGrid::getPosition() const { return m_Node->getPosition(); }

// sets the position of the primitive.
void OOP::PrimitiveGrid::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position);
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	//m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	//this->m_Position = position;
}

// sets the visibility of the primitive.
// void OOP::PrimitiveGrid::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the primitive on/off.
// void OOP::PrimitiveGrid::setVisible() { setVisible(!m_Node->isVisible()); }