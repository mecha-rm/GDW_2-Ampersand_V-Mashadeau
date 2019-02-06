// Used to create primitive objects; re-used lab assignment
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

namespace cocos2d // includes specific classes from cocos2d
{
	class Vec2;
	class DrawNode;
}


namespace OOP
{
	class PrimitiveSquare
	{
	public:
		// creates and initalizes drawNode for square.
		PrimitiveSquare(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// creates a square draw primitive. This is based on the middle of the square.
		PrimitiveSquare(const cocos2d::Vec2 location, const float width, const float height, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// creates a square draw primitive. This reuses the constructor with the (cocos2d::vec2, float, float) parameter, but has the two floats be guaranteed to be the same value.
		PrimitiveSquare(const cocos2d::Vec2 location, const float sideLength, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// destructor is called when an object of type PrimitiveSquare is destroyed.
		~PrimitiveSquare();

		// returns square primitive
		cocos2d::DrawNode * getPrimitive() const;
	
	private:
		// we use this node to draw primitives
		cocos2d::DrawNode * m_Node; // Question 3: DrawNode member
	};

	// Primitive Circle Class
	class PrimitiveCircle
	{
	public:
		// creates and initalizes drawNode
		PrimitiveCircle(cocos2d::Vec2 location, float radius, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// destructor for primitive circle
		~PrimitiveCircle();

		// Question 4: returns circle primititve
		cocos2d::DrawNode * getPrimitive() const;

	private:
		cocos2d::DrawNode * m_Node; // Question 3: DrawNode member
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
	private:
		cocos2d::DrawNode * m_Node; // Question 3: DrawNode member
	};

	// Capsule Primitive Class
	class PrimitiveCapsule
	{
	public:
		// Question 3: creates and initalizes drawNode
		PrimitiveCapsule(cocos2d::Vec2 start, cocos2d::Vec2 end, float radius);
		// destructor for capsules
		~PrimitiveCapsule();

		// returns the capsule primitive
		cocos2d::DrawNode * getPrimitive() const;

	private:
		cocos2d::DrawNode * m_Node; // DrawNode member
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

	private:

		cocos2d::DrawNode * m_Node; // DrawNode member
	};
}

#endif //!PRIMITIVES_H

