// Stores the class that's used to create the level screens in the game.
#pragma once

// #include "PlatformManager.h"
#include "entities/Tile.h"
#include "entities/Enemy.h"

#include "2d/CCSprite.h"
#include <string>
#include <fstream> // used for file reading and writing
using namespace cocos2d;

namespace world
{

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
		Area(std::string backgroundLayer1, std::string backgroundLayer2 = "", std::string backgroundLayer3 = "", std::string foregroundLayer = "");

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
		std::string getExit0() const;

		// gets exit 1, being an exit point in the scene; this holds where the area exits to.
		std::string getExit1() const;

		// gets exit 2, being an exit point in the scene; this holds where the area exits to.
		std::string getExit2() const;

		// gets exit 3, being an exit point in the scene; this holds where the area exits to.
		std::string getExit3() const;

		// gets exit 4, being an exit point in the scene; this holds where the area exits to.
		std::string getExit4() const;

		// returns an exit based on a passed number. If the exit does not exist, a "" string is returned.
		// only numbers from 0 through 4 are allowed.
		std::string getExit(unsigned int exit) const;

		// returns spawn point 0.
		Vec2 getSpawn0() const;

		// returns spawn point 1.
		Vec2 getSpawn1() const;

		// returns spawn point 2.
		Vec2 getSpawn2() const;

		// returns spawn point 3.
		Vec2 getSpawn3() const;

		// returns spawn point 4.
		Vec2 getSpawn4() const;

		// returns a spawn point based on a passed number. If a number greater than 4 is passed, a vector of (0, 0) is returned.
		Vec2 getSpawn(unsigned short int spawn) const;

		// gets the strength of the gravity in the area.
		float getGravity() const;

		// sets the strength of gravity in the area; it cannot be less than or equal to 0.
		void setGravity(float gravity);

		// gets the scene tiles
		std::vector<entity::Tile *> * getAreaTiles();
	
		/*
		* adds an array to the area tiles vector. The maximum size of the array is the value of ROW_MAX and COL_MAX.
		* to end the vector additions early, the user can put in a custom row and column size, but if it exceeds the size limit, it will get cut off at the size limit.
	
		* VARIABLES:
			* flipY: flips the locations of the tiles along the y-axis. This determines whether platforms are positioned as the array looks, or how the array actually is.
			* the 'bottom' of the array above is technically the top of it, and vice-versa. When flipY is true, the 'bottom' of the array is treated as the 'top' of the array for printing purposes.
			* when flipY is false, the first row of tiles will be at the bottom of the screen, and the final row will be the top of the screen.
			* when flipY is true, the first row of tiles will be at the top of the screen, and the final row will be at the bottom of the screen.
		*/
		void tileArrayToVector(entity::Tile * tileGrid[][52], const bool flipY = false, int rowMax = ROW_MAX, int colMax = COL_MAX);

		// adds a tile to the area
		void operator+=(entity::Tile *);

		// subtracts a tile from the area
		void operator-=(entity::Tile *);

		// gets the enemy vector
		std::vector<entity::Enemy *> * getAreaEnemies();

		/*
		 * adds an array to the area enemiesvector. The maximum size of the array is the value of ROW_MAX and COL_MAX.
		 * to end the vector additions early, the user can put in a custom row and column size, but if it exceeds the size limit, it will get cut off at the size limit.
	
		 * VARIABLES:
			* flipY: flips the locations of the tiles along the y-axis. This determines whether platforms are positioned as the array looks, or how the array actually is.
			* the 'bottom' of the array above is technically the top of it, and vice-versa. When flipY is true, the 'bottom' of the array is treated as the 'top' of the array for printing purposes.
			* when flipY is false, the first row of tiles will be at the bottom of the screen, and the final row will be the top of the screen.
			* when flipY is true, the first row of tiles will be at the top of the screen, and the final row will be at the bottom of the screen.
		*/
		void enemyArrayToVector(entity::Enemy * enemyGrid[][52], const bool flipY = false, int rowMax = ROW_MAX, int colMax = COL_MAX);

		// adds an ememy to the area
		void operator+=(entity::Enemy *);

		// subtracts an enemy from the area
		void operator-=(entity::Enemy *);

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

		Node * mergedNode; // a node that saves the whole area on a single node (see getAsSingleNode())

	private:
		float gravity = 100.0F; // the level of gravity in the area. f
		// float gravity = 600.0F; // final game gravity?

		std::string fileName; // the name of the file
		std::fstream file; // the file itself

	protected:
		// setting bg1 layer
		void setBackgroundLayer1(std::string backgroundLayer1);

		// setting bg2 layer
		void setBackgroundLayer2(std::string backgroundLayer2);

		// setting bg3 layer
		void setBackgroundLayer3(std::string backgroundLayer3);

		// setting the fg layer
		void setForegroundLayer(std::string foregroundLayer);

		// sets the area's name
		void setName(std::string name);

		// the name of the area.
		std::string name = "";

		// saves what area file to switch to when the player leaves the area they're currently in. This just has to be the name of the file.
		// format: AIN_###_#
		// - the last digit (after the second underscore) determines what spawn point to use.
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

		std::vector<entity::Tile *> areaTiles; // holds all tiles for the scene
		std::vector<entity::Enemy *> areaEnemies; // holds all enemies for the scene
		// entity::Tile * tileGrid[ROW_MAX][COL_MAX];
	};
}
