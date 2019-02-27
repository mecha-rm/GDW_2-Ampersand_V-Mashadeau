// Used to create primitive objects; re-used lab assignment
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "cocos/base/ccTypes.h"
#include "cocos/math/Vec2.h"
#include "cocos/math/Vec3.h"
#include "cocos/2d/ccdrawnode.h"
#include "2d/CCDrawNode.h"

/*
// Using a namespace caused issues, so it is no longer used.
namespace cocos2d // includes specific classes from cocos2d
{
	class Vec2;
	class Vec3;
	class DrawNode;
}
*/

namespace OOP
{
	class PrimitiveSquare
	{
	public:
		// creates and initalizes drawNode for square.
		PrimitiveSquare(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// creates a square draw primitive. This is based on the middle of the rect.
		PrimitiveSquare(const cocos2d::Vec2 location, const float width, const float height, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// creates a square draw primitive. This reuses the constructor with the (cocos2d::vec2, float, float) parameter, but has the two floats be guaranteed to be the same value.
		// This is based on the middle of the square.
		PrimitiveSquare(const cocos2d::Vec2 location, const float sideLength, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// destructor is called when an object of type PrimitiveSquare is destroyed.
		~PrimitiveSquare();

		// returns square primitive
		cocos2d::DrawNode * getPrimitive() const;

		// gets the position of the vector.
		cocos2d::Vec2 getPosition() const;

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// returns a rect representing the primitive.
		cocos2d::Rect getRect() const;

		// turns on/off the visibility of the primitive.
		void setVisible(bool visible);

		// toggle for visible; it turns it on/off.
		void setVisible();

		// the width of the rectangle primitive.
		const float m_WIDTH;
		
		// the height of the rectangle primitive.
		const float m_HEIGHT;

	private:
		// we use this node to draw primitives
		cocos2d::DrawNode * m_Node; // drawNode member

		// the position of the primitive, based on its centre.
		cocos2d::Vec2 m_Position;
	};

	// Primitive Circle Class
	class PrimitiveCircle
	{
	public:
		// creates and initalizes drawNode
		PrimitiveCircle(cocos2d::Vec2 location, float radius, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// destructor for primitive circle
		~PrimitiveCircle();

		// returns circle primitive
		cocos2d::DrawNode * getPrimitive() const;

		// gets the position of the circle, based on its centre.
		cocos2d::Vec2 getPosition() const;

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// turns on/off the visibility of the primitive.
		void setVisible(bool visible);

		// toggle for visible; it turns it on/off.
		void setVisible();

		// the radius of the circle.
		const float m_RADIUS = 0.0F;

	private:
		cocos2d::DrawNode * m_Node; // Question 3: DrawNode member

		// the position of the primitive.
		cocos2d::Vec2 m_Position;
	};

	// Line Primiive Class
	class PrimitiveLine
	{
	public:
		// creates a line draw primitive
		PrimitiveLine(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const cocos2d::Color4F colour = cocos2d::Color4F::RED);
		// destructor
		~PrimitiveLine();

		// Question 4: returns line primitive
		cocos2d::DrawNode * getPrimitive() const;

		// gets the position of the line, based on its midpoint.
		cocos2d::Vec2 getPosition() const;

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// turns on/off the visibility of the primitive.
		void setVisible(bool visible);

		// toggle for visible; it turns it on/off.
		void setVisible();

		// the slope of the line.
		const cocos2d::Vec2 m_DISTANCE;

		// the length of the line.
		const float m_LENGTH;
	private:
		cocos2d::DrawNode * m_Node; // Question 3: DrawNode member

		cocos2d::Vec2 m_Position;
	};

	// Capsule Primitive Class
	class PrimitiveCapsule
	{
	public:
		// creates a capsule. The start and end points are where the circles are drawn.
		PrimitiveCapsule(cocos2d::Vec2 start, cocos2d::Vec2 end, float radius, const cocos2d::Color4F colour = cocos2d::Color4F::MAGENTA);
		// destructor for capsules
		~PrimitiveCapsule();

		// returns the capsule primitive
		cocos2d::DrawNode * getPrimitive() const;

		// gets the position of the capsule, based on its centre.
		cocos2d::Vec2 getPosition() const;

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// gets the position of the circle at one of the endings of the capsule. This should be at the beginning of the capsule.
		cocos2d::Vec2 getCirclePosition1() const;

		// gets the position of the circle at one of the endings of the capsule. This should be at the ending of the capsule.
		cocos2d::Vec2 getCirclePosition2() const;

		// turns on/off the visibility of the primitive.
		void setVisible(bool visible);

		// toggle for visible; it turns it on/off.
		void setVisible();

		// the radius of the capsule.
		const float m_RADIUS;

	private:
		cocos2d::DrawNode * m_Node; // DrawNode member

		cocos2d::Vec2 m_Position; // the position of the primitive (based on its centre).

		cocos2d::Vec2 m_Circle1; // saves the position of the starting circle of the capsule.

		cocos2d::Vec2 m_Circle2; // saves the position of the ending circle of the capsule.
	};

	// creates a grid of lines; not from original assignment
	class PrimitiveGrid
	{
	public:
		/*
		 * Creates a grid. Lines will keep being drawn until they exceed the bounds of the starting point and ending point.
		 *
		 * startingPoint: the starting corner of the grid.
		 * endingPoint: the ending corner of the grid.
		 * squareSize: the size of the grid spaces  (in pixels). It's the standard tile size (128.0F) by default.
		 * colour: the colour of the grid; black by default.
		 * gridBox: determines whether all the grid lines are put within a box. True by default.
		*/
		PrimitiveGrid(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const float squareSize = 128.0F, const cocos2d::Color4F colour = cocos2d::Color4F::BLACK, const bool gridBox = true);

		/*
		 * Creates a grid. Lines will keep being drawn until they exceed the bounds of the starting point and ending point.
		 *
		 * position: the position of the grid. It is the MIDDLE of the grid.
		 * size: the size of the grid overal
		 * squareSize: the size of the grid spaces (in pixels). It's the standard tile size (128.0F) by default.
		 * colour: the colour of the grid; black by default.
		 * gridBox: determines whether all the grid lines are put within a box. True by default.
		*/
		PrimitiveGrid(cocos2d::Vec2 position, cocos2d::Size size, const float squareSize = 128.0F, const cocos2d::Color4F colour = cocos2d::Color4F::BLACK, const bool gridBox = true);

		~PrimitiveGrid();

		// returns the grid primitive
		cocos2d::DrawNode * getPrimitive() const;

		// gets the position of the vector.
		cocos2d::Vec2 getPosition() const;

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// turns on/off the visibility of the primitive.
		void setVisible(bool visible);

		// toggle for visible; it turns it on/off.
		void setVisible();

		// the width of the grid. This is based on the passed parameters, and not the farthest left line and farthest right line.  As such, it assumes that all grid spaces are of equal size.
		float m_WIDTH;
		// the height of the grid. This is based on the passed parameters, and not the highest and lowest line. As such, it assumes that all grid spaces are of equal size.
		float m_HEIGHT;

		// stores the unit size (i.e. square size) of the grid.
		float m_SQUARE_SIZE; 

	private:

		cocos2d::DrawNode * m_Node; // DrawNode member

		cocos2d::Vec2 m_Position; // the position of the grid (based on its centre).

	};
}

#endif //!PRIMITIVES_H