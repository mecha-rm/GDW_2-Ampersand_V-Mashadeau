#include "Area.h"

#include <iostream>

const unsigned int world::Area::ROW_MAX; // maximum row amount
const unsigned int world::Area::COL_MAX; // maximum column amount
const float world::Area::GRID_UNIT_SIZE = 128.0F; // grid square size

// creates three backgrounds, and a foreground
world::Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, std::string foregroundLayer)
{

	entity::Entity::areaGravity = &gravity; // sets the gravity for all entities to the gravity in the area.

	// creates the sprites
	bg1 = Sprite::create();
	bg2 = Sprite::create();
	bg3 = Sprite::create();
	fg = Sprite::create();

	// sets the global z order of all backgrounds.
	bg1->setGlobalZOrder(0.0F);
	bg2->setGlobalZOrder(0.1F);
	bg3->setGlobalZOrder(0.2F);
	fg->setGlobalZOrder(9.0F);

	// creates all the backgrounds and foregrounds
	setBackgroundLayer1(backgroundLayer1);
	setBackgroundLayer2(backgroundLayer2);
	setBackgroundLayer3(backgroundLayer3);
	setForegroundLayer(foregroundLayer);

}

// destructor; releases all sprites.
world::Area::~Area()
{
	if (bg1 != nullptr)
		bg1->removeFromParent();

	if (bg2 != nullptr)
		bg2->removeFromParent();

	if (bg3 != nullptr)
		bg3->removeFromParent();

	if (fg != nullptr)
		fg->removeFromParent();
}

// Returns the first background layer
Sprite * world::Area::getBackgroundLayer1() const { return bg1; }

// sets background layer 1
void world::Area::setBackgroundLayer1(std::string backgroundLayer1)
{
	if (backgroundLayer1 == "") // if the layer is blank, then the texture isn't changed.
		return;

	bg1->setTexture(backgroundLayer1);
}

// Returns the second background layer
Sprite * world::Area::getBackgroundLayer2() const { return bg2; }

// sets background layer 2
void world::Area::setBackgroundLayer2(std::string backgroundLayer2)
{
	if (backgroundLayer2 == "") // if the layer is blank, then the texture isn't changed.
		return;

	bg2->setTexture(backgroundLayer2);
}

// Returns the third background layer
Sprite * world::Area::getBackgroundLayer3() const { return bg3; }

// sets background layer 3
void world::Area::setBackgroundLayer3(std::string backgroundLayer3)
{
	if (backgroundLayer3 == "") // if the layer is blank, then the texture isn't changed.
		return;

	bg3->setTexture(backgroundLayer3);
}

// Returns a backgorund layer based on a value.
Sprite * world::Area::getBackground(short int bg) const
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
Sprite * world::Area::getForegroundLayer() const { return fg; }

// sets foreground layer
void world::Area::setForegroundLayer(std::string foregroundLayer)
{
	if (foregroundLayer == "") // if the layer is blank, then the texture isn't changed.
		return;

	fg->setTexture(foregroundLayer);
}

// sets the positions of all background and foreground layers.
void world::Area::setAllLayerPositions(Vec2 position)
{
	bg1->setPosition(position);
	bg2->setPosition(position);
	bg3->setPosition(position);
	fg->setPosition(position);
}

// sets the anchour points of all layers.
void world::Area::setAllAnchourPoints(Vec2 anchour)
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

// gets all graphic elements as a single node.
Node * world::Area::getAsSingleNode()
{
	float gz = 0.0F;
	Node * tempNode = Node::create(); // temporary node

	// ParallaxNode * gscl = ParallaxNode::create();
	// gscl->addChild(bg1, bg1->getGlobalZOrder(), Vec2(1.0F, 1.0F), Vec2::ZERO);

	// adds all the backgrounds and foreground to the draw node, checking for null pointers.
	tempNode->addChild(bg1);
	tempNode->addChild(bg2);
	tempNode->addChild(bg3);
	tempNode->addChild(fg);
	
	for (int i = 0; i < areaTiles.size(); i++) // adds all the tiles from the tile vector
	{
		gz = areaTiles.at(i)->getSprite()->getGlobalZOrder();
		tempNode->addChild(areaTiles.at(i)->getSprite());
	}

	for (int i = 0; i < areaEnemies.size(); i++) // adds all the enemies from the enemy vector
		tempNode->addChild(areaEnemies[i]->getSprite());
	
	// bg2->setGlobalZOrder(0.0F);
	mergedNode = tempNode;
	return tempNode;
}

// sets the name of the area
std::string world::Area::getName() const { return name; }

// sets the area's name.
void world::Area::setName(std::string name) { this->name = name; }

// returns the location exit 0 leads to.
std::string world::Area::getExit0() const { return exit0; }

// returns the location exit 1 leads to.
std::string world::Area::getExit1() const { return exit1; }

// returns the location exit 2 leads to.
std::string world::Area::getExit2() const { return exit2; }

// returns the location exit 3 leads to.
std::string world::Area::getExit3() const { return exit3; }

// returns the location exit 4 leads to.
std::string world::Area::getExit4() const { return exit4; }

// gets an exit based on a passed number.
std::string world::Area::getExit(unsigned int exit) const
{
	switch (exit) // returns an exit if a valid number was given.
	{
	case 0:
		return getExit0();
		break;

	case 1:
		return getExit1();
		break;

	case 2:
		return getExit2();
		break;

	case 3:
		return getExit3();
		break;

	case 4:
		return getExit4();
		break;
	}

	return std::string("");
}

// returns spawn point #0
Vec2 world::Area::getSpawn0() const { return spawn0; }

// returns spawn point #1
Vec2 world::Area::getSpawn1() const { return spawn1; }

// returns spawn point #2
Vec2 world::Area::getSpawn2() const { return spawn2; }

// returns spawn point #3
Vec2 world::Area::getSpawn3() const { return spawn3; }

// returns spawn point #4
Vec2 world::Area::getSpawn4() const { return spawn4; }

// returns a spawn point based on a passed value.
Vec2 world::Area::getSpawn(unsigned short int spawn) const
{
	switch (spawn) // returns a specific spawn point.
	{
	case 0:
		return getSpawn0();
		break;

	case 1:
		return getSpawn1();
		break;

	case 2:
		return getSpawn2();
		break;

	case 3:
		return getSpawn3();
		break;

	case 4:
		return getSpawn4();
		break;
	}

	return Vec2(0.0F, 0.0F); // returns a vector of (0, 0) if no spawn point was found.
}

// gets the strength of the gravity in the area.
float world::Area::getGravity() const { return gravity; }

// sets the strength of gravity in the area; it cannot be less than or equal to 0. If a value less than 0 is passed, then the gravity stays the same.
void world::Area::setGravity(float gravity) 
{ 
	(gravity > 0.0f) ? this->gravity = gravity : this->gravity = this->gravity;
}

// returns the tiles in the area.
std::vector<entity::Tile*> * world::Area::getAreaTiles() { return &areaTiles; }

// takes a array of entity tiles and puts it into the vector. The values of ROW_MAX and COL_MAX are the limits for it.
void world::Area::tileArrayToVector(entity::Tile * tileGrid[][52], const bool flipY, int rowMax, int colMax)
{
	float offset = 0.0F; // used to offset copies of the element

	// if the provided row or column amounts go above the limits of the program, they are cut off at the size limit.
	if (rowMax > ROW_MAX)
		rowMax = ROW_MAX;
	
	if (colMax > COL_MAX)
		colMax = COL_MAX;

	for (int row = 0; row < ROW_MAX; row++)
	{
		for (int col = 0; col < COL_MAX; col++)
		{
			if (tileGrid[row][col] == nullptr) // if the location is a nullptr, the program skips it
				continue;

			if (areaTiles.size() >= ROW_MAX * COL_MAX) // if the vector is full.
				return;

			
			tileGrid[row][col]->setPosition(64.0F + GRID_UNIT_SIZE * col, 64.0F + GRID_UNIT_SIZE * row); // sets the position of the current tile, based on its position in the array.
			if (flipY)
				tileGrid[row][col]->setPositionY(GRID_UNIT_SIZE * ROW_MAX - tileGrid[row][col]->getPositionY());

			areaTiles.push_back(tileGrid[row][col]); // adds the tile to the scene.

			// if the tile is a spawn point, then the location is saved to the variable, and the spawn point isn't added in.
			if (tileGrid[row][col]->getTIN() >= 5 && tileGrid[row][col]->getTIN() <= 9)
			{
				switch (tileGrid[row][col]->getTIN()) // sets the spawn point locations.
				{
				case 5:
					spawn0 = tileGrid[row][col]->getPosition();
					break;
				case 6:
					spawn1 = tileGrid[row][col]->getPosition();
					break;
				case 7:
					spawn2 = tileGrid[row][col]->getPosition();
					break;
				case 8:
					spawn3 = tileGrid[row][col]->getPosition();
					break;
				case 9:
					spawn4 = tileGrid[row][col]->getPosition();
					break;
				}

				continue; // there shouldn't be any copies of spawn points, so the program just moves on to the next index.
			}

			if (tileGrid[row][col]->COPY_UP > 0) // Copies Upwards
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_UP; i++) // loops while there are still copies left to be made.
				{
					areaTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					areaTiles.at(areaTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX(), tileGrid[row][col]->getPositionY() + offset * i); // makes a tile one square above the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_DOWN > 0) // Copies  Down
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_DOWN; i++) // loops while there are still copies left to be made.
				{
					areaTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					areaTiles.at(areaTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX(), tileGrid[row][col]->getPositionY() - offset * i); // makes a tile one square below the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_LEFT > 0) // Copies left
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_LEFT; i++) // loops while there are still copies left to be made.
				{
					areaTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					areaTiles.at(areaTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX() - offset * i, tileGrid[row][col]->getPositionY()); // makes a tile one square below the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_RIGHT > 0) // Copies Right
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_RIGHT; i++) // loops while there are still copies left to be made.
				{
					areaTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					areaTiles.at(areaTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX() + offset * i, tileGrid[row][col]->getPositionY()); // makes a tile one square below the previous tile.
				}
			}

		}
	}
}

// adds a tile to the area
void world::Area::operator+=(entity::Tile * tile)
{
	// check to see if the passed tile already exists in the vector. If it doesn't, it will get added in.
	for each(entity::Tile * vecTile in areaTiles)
	{
		if (vecTile == tile) // returns void if the tile already exists in the vector.
			return;
	}

	areaTiles.push_back(tile); // adds the tile into the vector if it isn't in there already.
}

// subtracts a tile from the area
void world::Area::operator-=(entity::Tile * tile)
{
	// looks to see if the tile exists in the tiles vector
	for (int i = 0; i < areaTiles.size(); i++)
	{
		if (areaTiles.at(i) == tile) // if the passed tile has been found, it is then deleted.
		{
			areaTiles.erase(areaTiles.begin() + i);
			return; // returns 'void' since the check is done.
		}
	}
}

// returns the enemies in the scene
std::vector<entity::Enemy*> * world::Area::getAreaEnemies() { return &areaEnemies; }

// takes a array of entity enemies and puts it into the vector. The values of ROW_MAX and COL_MAX are the limits for it.
void world::Area::enemyArrayToVector(entity::Enemy * enemyGrid[][52], const bool flipY, int rowMax, int colMax)
{
	float offset = 0.0F; // used to offset copies of the element

	// if the provided row or column amounts go above the limits of the program, they are cut off at the size limit.
	if (rowMax > ROW_MAX)
		rowMax = ROW_MAX;

	if (colMax > COL_MAX)
		colMax = COL_MAX;

	for (int row = 0; row < ROW_MAX; row++)
	{
		for (int col = 0; col < COL_MAX; col++)
		{
			if (enemyGrid[row][col] == nullptr) // if the location is a nullptr, the program skips it
				continue;

			enemyGrid[row][col]->setPosition(64.0F + GRID_UNIT_SIZE * col, 64.0F + GRID_UNIT_SIZE * row); // sets the position of the current enemy, based on its position in the array.

			if (flipY) // flipping the enemy's position if flipY is true
				enemyGrid[row][col]->setPositionY(GRID_UNIT_SIZE * ROW_MAX - enemyGrid[row][col]->getPositionY());


			areaEnemies.push_back(enemyGrid[row][col]); // adds the enemy to the scene.

			if (enemyGrid[row][col]->COPY_UP > 0) // Copies Upwards
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_UP; i++) // loops while there are still copies left to be made.
				{
					areaEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					areaEnemies.at(areaEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX(), enemyGrid[row][col]->getPositionY() + offset * i); // makes a enemy one unit above the previous enemy.
				}
			}

			if (enemyGrid[row][col]->COPY_DOWN > 0) // Copies  Down
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_DOWN; i++) // loops while there are still copies left to be made.
				{
					areaEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					areaEnemies.at(areaEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX(), enemyGrid[row][col]->getPositionY() - offset * i); // makes a enemy one square below the previous tile.
				}
			}

			if (enemyGrid[row][col]->COPY_LEFT > 0) // Copies left
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_LEFT; i++) // loops while there are still copies left to be made.
				{
					areaEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					areaEnemies.at(areaEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX() - offset * i, enemyGrid[row][col]->getPositionY()); // makes a enemy one square below the previous tile.
				}
			}

			if (enemyGrid[row][col]->COPY_RIGHT > 0) // Copies Right
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_RIGHT; i++) // loops while there are still copies left to be made.
				{
					areaEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					areaEnemies.at(areaEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX() + offset * i, enemyGrid[row][col]->getPositionY()); // makes a enemy one square below the previous tile.
				}
			}

		}
	}
}

// adds an enemy to the area
void world::Area::operator+=(entity::Enemy * enemy)
{
	// check to see if the passed enemy already exists in the vector. If it doesn't, it will get added in.
	for each(entity::Enemy * vecEnemy in areaEnemies)
	{
		if (vecEnemy == enemy) // returns void if the enemy already exists in the vector.
			return;
	}

	areaEnemies.push_back(enemy); // adds the enemy into the vector if it isn't in there already.
}

// subtracts an enemy from the area
void world::Area::operator-=(entity::Enemy * enemy)
{
	// looks to see if the tile exists in the enemy vector
	for (int i = 0; i < areaEnemies.size(); i++)
	{
		if (areaEnemies[i] == enemy) // if the passed enemy has been found, it is then deleted.
		{
			areaEnemies.erase(areaEnemies.begin() + i);
			return; // returns 'void' since the check is done.
		}
	}
}

// gets the class data in bytes.
char * world::Area::toBytes() const
{
	char bytes[sizeof(Area)]; // size of the vec2 class
	memcpy(bytes, this, sizeof(Area)); // getting the current object in byte form

	return bytes;
}

// writes the level data to a file.
void world::Area::saveToFile() { saveToFile("dats/AIN_" + getName() + ".dat", this); }

// writes the level data to a file.
void world::Area::saveToFile(std::string fileName, world::Area * area)
{
	std::ofstream file;
	file.open(fileName, std::ios::out); // creates the file for output to it

	// validity check
	try
	{
		if (!file)
			throw "Failed to open file for saving. Information saving failed";
	}
	catch (const char * ex)
	{
		std::cout << ex << std::endl;
		return;
	}
	catch (...)
	{
		std::cout << "Error encountered. Unable to write to file" << std::endl;
		return;
	}

	// writes information to file.
	file.write(reinterpret_cast<const char *>(area), sizeof(world::Area));

	file.close();
	
}

// loads level information from a file if the file isn't empty.
world::Area * world::Area::loadFromFile() { return loadFromFile("dats/AIN_" + name + ".dat"); }

// loads level information from a provided area file.
world::Area * world::Area::loadFromFile(std::string fileName)
{
	world::Area * area = nullptr;

	std::ifstream file; // the file to be opened
	file.open(fileName, std::ios::in);

	try
	{
		if (!file)
			throw "Failed to open file for reading. Information failed to load";
	}
	catch (const char * ex)
	{
		std::cout << ex << std::endl;
		return nullptr;
	}
	catch (...)
	{
		std::cout << "Error encountered. Unable to open file for reading" << std::endl;
		return nullptr;
	}

	// loads in area information
	file.read(reinterpret_cast<char *>(area), sizeof(world::Area));
	
	file.close();

	return area;
}

// updates the area
void world::Area::update(float deltaTime)
{
	entity::Entity * tempEntity = nullptr;

	// updates the scene tiles
	for (int i = 0; i < areaTiles.size(); i++)
	{
		if (areaTiles.at(i)->onScreen == false) // not on screen, so don't update.
			continue;

		areaTiles.at(i)->update(deltaTime);

		if (areaTiles[i]->getHealth() <= 0.0F) // if the tile has no health, it should be deleted.
		{
			for (OOP::Primitive * p : areaTiles[i]->getCollisionBodies()) // removing all of the primitives from their parents for the tiles.
				p->getPrimitive()->removeFromParent();

			areaTiles[i]->getSprite()->removeFromParent(); // removes the tile's sprite.
			areaTiles.erase(areaTiles.begin() + i); // erases the pointer and other tile data.
		}

	}
		

	// updates the enemies
	for (int i = 0; i < areaEnemies.size(); i++)
	{
		if (areaEnemies.at(i)->onScreen == false) // not on screen, so don't update.
			continue;

		areaEnemies[i]->update(deltaTime);
		
		if (areaEnemies[i]->getHealth() <= 0.0F) // if the enemy has lost all of its health.
		{
			for (OOP::Primitive * p : areaEnemies[i]->getCollisionBodies()) // removing all of the primitives from their parents.
				p->getPrimitive()->removeFromParent();

			areaEnemies[i]->getSprite()->removeFromParent();
			areaEnemies.erase(areaEnemies.begin() + i); // erases the pointer.

			
		}
	}
}



