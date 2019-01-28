// Stores the class that's used to create the level screens in the game.
#pragma once

#include "2d/CCSprite.h"

#include <string>
#include <fstream> // used for file reading and writing
using namespace cocos2d;

class Area
{
public:
	// creates the area with a single background layer
	// the anchour point parameter controls the point that all positionings and transformations work around. By default, it's the middle of the sprite.
	Area(std::string backgroundLayer, Vec2 anchour = Vec2(0.5F, 0.5F));

	// creates the area with two background layers; background layer 1 is behind background layer 2
	// the anchour point parameter controls the point that all positionings and transformations work around. By default, it's the middle of all the sprites.
	Area(std::string backgroundLayer1, std::string backgroundLayer2, Vec2 anchour = Vec2(0.5F, 0.5F));

	// creates the area with three background layers; background layer 1 is behind background layer 2, which is behind background layer 3
	// the anchour point parameter controls the point that all positionings and transformations work around. By default, it's the middle of all the sprites.
	Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, Vec2 anchour = Vec2(0.5F, 0.5F));

	// creates the area with three background layers and one foreground layer; background layer 1 is behind background layer 2, which is behind background layer 3.
	// the foreground layer gets put in front of everything else in the scene, unless something else has a higher global order.
	// the anchour point parameter controls the point that all positionings and transformations work around. By default, it's the middle of all the sprites.
	Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, std::string foregroundLayer, Vec2 anchour = Vec2(0.5F, 0.5F));

	~Area();

	// returns background layer 1 
	Sprite * getBackgroundLayer1() const;

	// returns background layer 2
	Sprite * getBackgroundLayer2() const;

	// returns background layer 3
	Sprite * getBackgroundLayer3() const;

	// gets a background based on a passed value.
	Sprite * getBackground(short int bg) const;

	// returns the foreground layer
	Sprite * getForegroundLayer() const;

	// gets the name of the area
	std::string getName() const;

	// gets door 1, being an exit point in the scene; this holds where the area exits to.
	std::string getDoor1();						  
												  
	// gets door 2, being an exit point in the scene; this holds where the area exits to.
	std::string getDoor2();						  
												  
	// gets door 3, being an exit point in the scene; this holds where the area exits to.
	std::string getDoor3();						  
												  
	// gets door 4, being an exit point in the scene; this holds where the area exits to.
	std::string getDoor4();

	// gets door 5, being an exit point in the scene; this holds where the area exits to.
	std::string getDoor5();

	// returns the class in bytes.
	char * toBytes() const;

	// writes the class data to its desigated file.
	void writeToFile();

	// writes the class data to a specific file.
	void writeToFile(std::string fileName);

protected:
	// sets the area's name
	void setName(std::string name);

	// the name of the area.
	std::string name = "";
	
	// Background images
	Sprite * bg1; // the first background layer; it's the farthest back layer
	Sprite * bg2; // the second background layer; it's infront of bg1.
	Sprite * bg3; // the third background layer; it's in front of bg2.

	// Foreground image.
	Sprite * fg; // a foreground layer; this would go in front of all other level assets.

	// saves what area file to switch to when the player leaves the area they're currently in.
	// A negative number is used to denote when the program should switch to another area, which is what these variables save.
	std::string door1;
	std::string door2;
	std::string door3;
	std::string door4;
	std::string door5;

private:
	std::string fileName; // the name of the file
	std::fstream file; // the file itself

};

