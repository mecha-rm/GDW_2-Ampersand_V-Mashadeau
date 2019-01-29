#include "Area.h"

#include <iostream>

Area::Area()
{
	bg1 = Sprite::create();
	bg2 = Sprite::create();
	bg3 = Sprite::create();
	fg = Sprite::create();
	initLayers(Vec2(0.5, 0.5)); // initalizes with anchors of (0.5, 0.5)
}

// creates one background
Area::Area(std::string backgroundLayer, Vec2 anchour) : bg1(Sprite::create(backgroundLayer))
{
	// creates the unused sprites.
	bg2 = Sprite::create();
	bg3 = Sprite::create();
	fg = Sprite::create();

	// sets initial layer values
	initLayers(anchour);
}

// creates two backgrounds
Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, Vec2 anchour) : bg1(Sprite::create(backgroundLayer1)), bg2(Sprite::create(backgroundLayer2))
{
	// creates unused sprites.
	bg3 = Sprite::create();
	fg = Sprite::create();

	// sets initial layer values
	initLayers(anchour);
}

// creates three backgrounds
Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, Vec2 anchour) :
	bg1(Sprite::create(backgroundLayer1)), bg2(Sprite::create(backgroundLayer2)), bg3(Sprite::create(backgroundLayer3))
{
	// creates leftover sprites
	fg = Sprite::create();

	// sets initial layer values
	initLayers(anchour);
}


// creates three backgrounds, and a foreground
Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, std::string foregroundLayer, Vec2 anchour) :
	bg1(Sprite::create(backgroundLayer1)), bg2(Sprite::create(backgroundLayer2)), bg3(Sprite::create(backgroundLayer3)), fg(Sprite::create(foregroundLayer))
{
	// sets initial layer values
	initLayers(anchour);
}

// destructor
Area::~Area() {}

// initalizes the values of all layers
void Area::initLayers(Vec2 anchour)
{
	// Sets the anchour points and global z orders.
	bg1->setAnchorPoint(anchour);
	bg1->setGlobalZOrder(0.0F);

	bg2->setAnchorPoint(anchour);
	bg2->setGlobalZOrder(0.1F);

	bg3->setAnchorPoint(anchour);
	bg3->setGlobalZOrder(0.2F);

	fg->setAnchorPoint(anchour);
	fg->setGlobalZOrder(10.0F); // this should be in front of everything at all times.
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
	
	// adds all the backgrounds and foreground ot the draw list.
	if (bg1->getTexture() != nullptr)
		tempNode->addChild(bg1);
	
	tempNode->addChild(bg2);
	tempNode->addChild(bg3);
	tempNode->addChild(fg);

	return tempNode;
}

// sets the name of the area
std::string Area::getName() const { return name; }

// returns the location door 1 leads to.
std::string Area::getDoor1() { return door1; }

// returns the location door 2 leads to.
std::string Area::getDoor2() { return door2; }

// returns the location door 3 leads to.
std::string Area::getDoor3() { return door3; }

// returns the location door 4 leads to.
std::string Area::getDoor4() { return door4; }

// returns the location door 5 leads to.
std::string Area::getDoor5() { return door5; }

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

// sets the area's name.
void Area::setName(std::string name) { this->name = name; }



