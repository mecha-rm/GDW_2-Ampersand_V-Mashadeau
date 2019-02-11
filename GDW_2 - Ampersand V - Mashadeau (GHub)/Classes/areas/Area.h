// Stores the class that's used to create the level screens in the game.
#pragma once

// #include "PlatformManager.h"
#include "entities/Tile.h"
#include "entities/Enemy.h"

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

	// gets all graphic elements as a single drawNode.
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

	// returns spawn point 0.
	Vec2 getSpawn0();

	// returns spawn point 1.
	Vec2 getSpawn1();

	// returns spawn point 2.
	Vec2 getSpawn2();

	// returns spawn point 3.
	Vec2 getSpawn3();

	// returns spawn point 4.
	Vec2 getSpawn4();


	// gets the scene tiles
	std::vector<entity::Tile *> getSceneTiles();

	// gets the enemy vector
	std::vector<entity::Enemy *> getSceneEnemies();

	// returns the class in bytes.
	char * toBytes() const;

	// writes the class data to its desigated file.
	void writeToFile();

	// writes the class data to a specific file.
	void writeToFile(std::string fileName);

	// loads level data from a file if there is any.
	void loadFromFile();

	// updates the Area.
	void update(float deltaTime);

	// Background images
	Sprite * bg1 = nullptr; // the first background layer; it's the farthest back layer
	Sprite * bg2 = nullptr; // the second background layer; it's infront of bg1.
	Sprite * bg3 = nullptr; // the third background layer; it's in front of bg2.

	// Foreground image.
	Sprite * fg = nullptr; // a foreground layer; this would go in front of all other level assets.

private:
	std::string fileName; // the name of the file
	std::fstream file; // the file itself

protected:
	// setting bg1 layer
	void setBackgroundLayer1(std::string backgroundLayer1, Vec2 anchour = Vec2(0.5F, 0.5F));

	// setting bg2 layer
	void setBackgroundLayer2(std::string backgroundLayer2, Vec2 anchour = Vec2(0.5F, 0.5F));

	// setting bg3 layer
	void setBackgroundLayer3(std::string backgroundLayer3, Vec2 anchour = Vec2(0.5F, 0.5F));

	// setting the fg layer
	void setForegroundLayer(std::string foregroundLayer, Vec2 anchour = Vec2(0.5F, 0.5F));

	// sets the area's name
	void setName(std::string name);

	// the name of the area.
	std::string name = "";

	// saves what area file to switch to when the player leaves the area they're currently in.
	// format: AIN_###_#
	// * the last digital (after the second underscore) determines what spawn point to use.
	std::string exit0 = "";
	std::string exit1 = "";
	std::string exit2 = "";
	std::string exit3 = "";
	std::string exit4 = "";

	// Saves the spawning positions for each possible exit. When the user enters an exit, a specific spawning point is looking for.
	Vec2 spawn0 = Vec2{ 64.0F, 64.0F };
	Vec2 spawn1 = spawn0;
	Vec2 spawn2 = spawn1;
	Vec2 spawn3 = spawn2;
	Vec2 spawn4 = spawn3;

	// The size of the screen is 13 X 7.5 on full screen (i.e. 13 128 X 128 blocks along the x-axis, and 7.5 128 X 128 blocks along the y-axis.
	// The ROW_MAX and COL_MAX determines the maximum size of the area. They are currently 30 X 52 (13 * 4, 7.5 * 4)
	static const unsigned int ROW_MAX = 30; // maximum amount of rows
	static const unsigned int COL_MAX = 52; // maximum amount of columns
	static const float GRID_UNIT_SIZE; // the size of one square on the grid. Setting an inital value had to be done in the cpp file.

	std::vector<entity::Tile *> sceneTiles; // holds all tiles for the scene
	std::vector<entity::Enemy *> sceneEnemies; // holds all enemies for the scene
	// entity::Tile * tileGrid[ROW_MAX][COL_MAX];
};

