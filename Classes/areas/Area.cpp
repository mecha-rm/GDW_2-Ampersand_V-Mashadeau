#include "Area.h"

#include <iostream>

//
//Area::Area()
//{
//	/*
//	bg1 = Sprite::create();
//	bg2 = Sprite::create();
//	bg3 = Sprite::create();
//	fg = Sprite::create();
//	initLayers(Vec2(0.5, 0.5)); // initalizes with anchors of (0.5, 0.5)
//	*/
//}
//
//// creates one background
//Area::Area(std::string backgroundLayer, Vec2 anchour) : bg1(Sprite::create(backgroundLayer))
//{
//	/*
//	// creates the unused sprites.
//	bg2 = Sprite::create();
//	bg3 = Sprite::create();
//	fg = Sprite::create();
//
//	// sets initial layer values
//	initLayers(anchour);
//	*/
//}
//
//// creates two backgrounds
//Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, Vec2 anchour) : bg1(Sprite::create(backgroundLayer1)), bg2(Sprite::create(backgroundLayer2))
//{
//	// creates unused sprites.
//	bg3 = Sprite::create();
//	fg = Sprite::create();
//
//	// sets initial layer values
//	initLayers(anchour);
//}
//
//// creates three backgrounds
//Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, Vec2 anchour) :
//	bg1(Sprite::create(backgroundLayer1)), bg2(Sprite::create(backgroundLayer2)), bg3(Sprite::create(backgroundLayer3))
//{
//	// creates leftover sprites
//	fg = Sprite::create();
//
//	// sets initial layer values
//	initLayers(anchour);
//}


// creates three backgrounds, and a foreground
Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, std::string foregroundLayer, Vec2 anchour)
{

	bg1 = Sprite::create(backgroundLayer1); // creates background layer 1
	bg1->setAnchorPoint(anchour); // sets the anchour point of the 1st background layer.

	// For these backgrounds, if no image was provided, they're left as nullptrs. If an image is provided, then the sprites are created.
	// As with bg1, they all use the same anchour point.
	// Background Layer 2
	if (backgroundLayer2 != "")
	{
		bg2 = Sprite::create(backgroundLayer2);
		bg2->setAnchorPoint(anchour);
	}
	
	// Background Layer 3
	if (backgroundLayer3 != "")
	{
		bg3 = Sprite::create(backgroundLayer3);
		bg3->setAnchorPoint(anchour);
	}
		
	// Foreground Layer
	if (foregroundLayer != "")
	{
		fg = Sprite::create(foregroundLayer);
		fg->setAnchorPoint(anchour);
	}
}

// destructor; releases all sprites.
Area::~Area() 
{
	bg1->release();
	bg2->release();
	bg3->release();
	fg->release();
}

// Returns the background layers
Sprite * Area::getBackgroundLayer1() const { return bg1; }

Sprite * Area::getBackgroundLayer2() const { return bg2; }

Sprite * Area::getBackgroundLayer3() const { return bg3; }

Sprite * Area::getBackground(short int bg) const
{
	switch (bg)
	{
	case 1:
		return bg1;
		break;
	case 2:
		return bg2;
		break;
	case 3:
		return bg3;
		break;
	}

	return nullptr; // returns a null pointer if the value is out of range.
}

Sprite * Area::getForegroundLayer() const { return fg; }

// sets the positions of all background and foreground layers.
void Area::setAllLayerPositions(Vec2 position)
{
	bg1->setPosition(position);
	bg2->setPosition(position);
	bg3->setPosition(position);
	fg->setPosition(position);
}

// sets the anchour points of all layers.
void Area::setAllAnchourPoints(Vec2 anchour)
{
	// sets the new achour points for all sprites.
	bg1->setAnchorPoint(anchour);
	bg2->setAnchorPoint(anchour);
	bg3->setAnchorPoint(anchour);
	fg->setAnchorPoint(anchour);
}

// gets all layers as a single draw node.
Node * Area::getAsSingleNode()
{
	Node * tempNode = Node::create(); // temporary node
	
	// adds all the backgrounds and foreground to the draw node, checking for null pointers.
	if(bg1 != nullptr)
		tempNode->addChild(bg1);
	
	if (bg2 != nullptr)
		tempNode->addChild(bg2);
	
	if(bg3 != nullptr)
		tempNode->addChild(bg3);
	
	if(fg != nullptr)
		tempNode->addChild(fg);

	return tempNode;
}

// sets the name of the area
std::string Area::getName() const { return name; }

// returns the location exit 0 leads to.
std::string Area::getExit0() { return exit0; }

// returns the location exit 1 leads to.
std::string Area::getExit1() { return exit1; }

// returns the location exit 2 leads to.
std::string Area::getExit2() { return exit2; }

// returns the location exit 3 leads to.
std::string Area::getExit3() { return exit3; }

// returns the location exit 4 leads to.
std::string Area::getExit4() { return exit4; }

// gets the class data in bytes.
char * Area::toBytes() const
{
	char bytes[sizeof(Area)]; // size of the vec2 class
	memcpy(bytes, this, sizeof(Area)); // getting the current object in byte form

	return bytes;
}

// writes the level data to a file.
void Area::writeToFile() { writeToFile(fileName); }

// writes the level data to a file.
void Area::writeToFile(std::string fileName)
{

}

// loads level information from a file if the file isn't empty.
void Area::loadFromFile()
{
}

// sets the area's name.
void Area::setName(std::string name) { this->name = name; }



