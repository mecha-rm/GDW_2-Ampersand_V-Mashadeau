#include "Area.h"

#include <iostream>

// creates three backgrounds, and a foreground
Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, std::string foregroundLayer, Vec2 anchour)
{

	bg1 = Sprite::create(backgroundLayer1); // creates background layer 1
	bg1->setAnchorPoint(anchour); // sets the anchour point of the 1st background layer.
	bg1->setGlobalZOrder(0.0F);

	// For these backgrounds, if no image was provided, they're left as nullptrs. If an image is provided, then the sprites are created.
	// As with bg1, they all use the same anchour point.
	// Background Layer 2
	if (backgroundLayer2 != "")
	{
		bg2 = Sprite::create(backgroundLayer2);
		bg2->setAnchorPoint(anchour);
		bg2->setGlobalZOrder(0.1F);
	}
	
	// Background Layer 3
	if (backgroundLayer3 != "")
	{
		bg3 = Sprite::create(backgroundLayer3);
		bg3->setAnchorPoint(anchour);
		bg3->setGlobalZOrder(0.2F);
	}
		
	// Foreground Layer
	if (foregroundLayer != "")
	{
		fg = Sprite::create(foregroundLayer);
		fg->setAnchorPoint(anchour);
		fg->setGlobalZOrder(9.0F); // this should be above everything except the mouse label
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

// Returns the first background layer
Sprite * Area::getBackgroundLayer1() const { return bg1; }

// sets background layer 1
void Area::setBackgroundLayer1(std::string backgroundLayer1, Vec2 anchour)
{
	if (bg1 == nullptr) // if bg1 is a nullptr (which it should never be), then the create function is called.
	{
		bg1 = Sprite::create(backgroundLayer1);
	}
	else // changes texture.
	{
		bg1->setTexture(backgroundLayer1);
	}

	bg1->setAnchorPoint(anchour); // setting the anchour point.
}
// Returns the second background layer
Sprite * Area::getBackgroundLayer2() const { return bg2; }

// sets background layer 2
void Area::setBackgroundLayer2(std::string backgroundLayer2, Vec2 anchour)
{
	if (bg2 == nullptr) // if bg2 is a nullptr, then the create function is called.
	{
		bg2 = Sprite::create(backgroundLayer2);
		bg2->setGlobalZOrder(0.1F);
	}
	else // changes texture.
	{
		bg2->setTexture(backgroundLayer2);
	}

	bg2->setAnchorPoint(anchour); // setting the anchour point.
}

// Returns the third background layer
Sprite * Area::getBackgroundLayer3() const { return bg3; }

// sets background layer 3
void Area::setBackgroundLayer3(std::string backgroundLayer3, Vec2 anchour)
{
	if (bg3 == nullptr) // if bg3 is a nullptr, then the create function is called.
	{
		bg3 = Sprite::create(backgroundLayer3);
		bg3->setGlobalZOrder(0.2F);
	}
	else // changes texture.
	{
		bg3->setTexture(backgroundLayer3);
	}

	bg3->setAnchorPoint(anchour); // setting the anchour point.
}

// Returns a backgorund layer based on a value.
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

// gets the foreground layer.
Sprite * Area::getForegroundLayer() const { return fg; }

// sets foreground layer
void Area::setForegroundLayer(std::string foregroundLayer, Vec2 anchour)
{
	if (fg == nullptr) // if bg3 is a nullptr, then the create function is called.
	{
		fg = Sprite::create(foregroundLayer);
	}
	else // changes texture.
	{
		fg->setTexture(foregroundLayer);
	}

	fg->setAnchorPoint(anchour); // setting the anchour point.
}

// sets the positions of all background and foreground layers.
void Area::setAllLayerPositions(Vec2 position)
{
	if (bg1 != nullptr)
		bg1->setPosition(position);
	
	if (bg2 != nullptr)
		bg2->setPosition(position);
	
	if (bg3 != nullptr)
		bg3->setPosition(position);
	
	if (fg != nullptr)
	 fg->setPosition(position);
}

// sets the anchour points of all layers.
void Area::setAllAnchourPoints(Vec2 anchour)
{
	// sets the new achour points for all sprites.
	if (bg1 != nullptr)
		bg1->setAnchorPoint(anchour);
	
	if (bg2 != nullptr)
		bg2->setAnchorPoint(anchour);
	
	if (bg3 != nullptr)
		bg3->setAnchorPoint(anchour);
	
	if (fg != nullptr)
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



