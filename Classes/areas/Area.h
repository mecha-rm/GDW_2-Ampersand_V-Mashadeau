// Stores the class that's used to create the level screens in the game.
#pragma once

#include "2d/CCSprite.h"

#include <string>
#include <fstream> // used for file reading and writing
using namespace cocos2d;

class Area
{
public:

	/*
	 * creates the area with three background layers and one foreground layer; background layer 1 is behind background layer 2, which is behind background layer 3.
	 * The foreground layer gets put in front of everything else in the scene, unless something else has a higher global z order.
	 * The anchour point parameter controls the point that all positionings and transformations work around. By default, it's the middle of the sprite for all layers.
	 *
	 * Any unitialized layer will be set to have the same default contents as
	*/
	Area(std::string backgroundLayer1, std::string backgroundLayer2 = "", std::string backgroundLayer3 = "", std::string foregroundLayer = "", Vec2 anchour = Vec2(0.5F, 0.5F));

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

	// sets the position of all background and foreground layers to be the same.
	void setAllLayerPositions(Vec2 position);

	// sets the anchour points of all layers.
	void setAllAnchourPoints(Vec2 anchour);

	// gets all layers as a single draw node.
	Node * getAsSingleNode();

	// gets the name of the area
	std::string getName() const;

	// gets exit 0, being an exit point in the scene; this holds where the area exits to.
	std::string getExit0();

	// gets exit 1, being an exit point in the scene; this holds where the area exits to.
	std::string getExit1();

	// gets exit 2, being an exit point in the scene; this holds where the area exits to.
	std::string getExit2();

	// gets exit 3, being an exit point in the scene; this holds where the area exits to.
	std::string getExit3();

	// gets exit 4, being an exit point in the scene; this holds where the area exits to.
	std::string getExit4();

	// returns the class in bytes.
	char * toBytes() const;

	// writes the class data to its desigated file.
	void writeToFile();

	// writes the class data to a specific file.
	void writeToFile(std::string fileName);

	// loads level data from a file if there is any.
	void loadFromFile();

	// Background images
	Sprite * bg1; // the first background layer; it's the farthest back layer
	Sprite * bg2; // the second background layer; it's infront of bg1.
	Sprite * bg3; // the third background layer; it's in front of bg2.

	// Foreground image.
	Sprite * fg; // a foreground layer; this would go in front of all other level assets.

private:
	std::string fileName; // the name of the file
	std::fstream file; // the file itself

protected:
	// sets the area's name
	void setName(std::string name);

	// the name of the area.
	std::string name = "";

	// saves what area file to switch to when the player leaves the area they're currently in.
	std::string exit0 = "";
	std::string exit1 = "";
	std::string exit2 = "";
	std::string exit3 = "";
	std::string exit4 = "";

	// Saves the spawning positions for each 
	Vec2 spawn0 = { 0.0F, 0.0F };
	Vec2 spawn1 = { 0.0F, 0.0F };
	Vec2 spawn2 = { 0.0F, 0.0F };
	Vec2 spawn3 = { 0.0F, 0.0F };
	Vec2 spawn4 = { 0.0F, 0.0F };

};

