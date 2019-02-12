#include "Area.h"

#include <iostream>

const unsigned int world::Area::ROW_MAX; // maximum row amount
const unsigned int world::Area::COL_MAX; // maximum column amount
const float world::Area::GRID_UNIT_SIZE = 128.0F; // grid square size

// creates three backgrounds, and a foreground
world::Area::Area(std::string backgroundLayer1, std::string backgroundLayer2, std::string backgroundLayer3, std::string foregroundLayer, Vec2 anchour)
{
	// creates all the backgrounds and foregrounds
	setBackgroundLayer1(backgroundLayer1, anchour);
	setBackgroundLayer2(backgroundLayer2, anchour);
	setBackgroundLayer3(backgroundLayer3, anchour);
	setForegroundLayer(foregroundLayer, anchour);

}

// destructor; releases all sprites.
world::Area::~Area()
{
	bg1->release();
	bg2->release();
	bg3->release();
	fg->release();
}

// Returns the first background layer
Sprite * world::Area::getBackgroundLayer1() const { return bg1; }

// sets background layer 1
void world::Area::setBackgroundLayer1(std::string backgroundLayer1, Vec2 anchour)
{
	if (backgroundLayer1 == "") // if the layer is blank, then the sprite isn't created.
		return;

	if (bg1 == nullptr) // if bg1 is a nullptr (which it should never be), then the create function is called.
	{
		bg1 = Sprite::create(backgroundLayer1);
		bg1->setGlobalZOrder(0.0F);
	}
	else // changes texture.
	{
		bg1->setTexture(backgroundLayer1);
	}

	bg1->setAnchorPoint(anchour); // setting the anchour point.
}

// Returns the second background layer
Sprite * world::Area::getBackgroundLayer2() const { return bg2; }

// sets background layer 2
void world::Area::setBackgroundLayer2(std::string backgroundLayer2, Vec2 anchour)
{
	if (backgroundLayer2 == "") // if the layer is blank, then the sprite isn't created.
		return;

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
Sprite * world::Area::getBackgroundLayer3() const { return bg3; }

// sets background layer 3
void world::Area::setBackgroundLayer3(std::string backgroundLayer3, Vec2 anchour)
{
	if (backgroundLayer3 == "") // if the layer is blank, then the sprite isn't created.
		return;

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
void world::Area::setForegroundLayer(std::string foregroundLayer, Vec2 anchour)
{
	if (foregroundLayer == "") // if the layer is blank, then the sprite isn't created.
		return;

	if (fg == nullptr) // if bg3 is a nullptr, then the create function is called.
	{
		fg = Sprite::create(foregroundLayer);
		fg->setGlobalZOrder(9.0F);
	}
	else // changes texture.
	{
		fg->setTexture(foregroundLayer);
	}

	fg->setAnchorPoint(anchour); // setting the anchour point.
}

// sets the positions of all background and foreground layers.
void world::Area::setAllLayerPositions(Vec2 position)
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

	for (int i = 0; i < areaTiles.size(); i++) // adds all the tiles from the tile vector
		tempNode->addChild(areaTiles.at(i)->getSprite());

	for (int i = 0; i < areaEnemies.size(); i++) // adds all the enemies from the enemy vector
		tempNode->addChild(areaEnemies[i]->getSprite());
	

	return tempNode;
}

// sets the name of the area
std::string world::Area::getName() const { return name; }

// sets the area's name.
void world::Area::setName(std::string name) { this->name = name; }

// returns the location exit 0 leads to.
std::string world::Area::getExit0() { return exit0; }

// returns the location exit 1 leads to.
std::string world::Area::getExit1() { return exit1; }

// returns the location exit 2 leads to.
std::string world::Area::getExit2() { return exit2; }

// returns the location exit 3 leads to.
std::string world::Area::getExit3() { return exit3; }

// returns the location exit 4 leads to.
std::string world::Area::getExit4() { return exit4; }

// returns spawn point #0
Vec2 world::Area::getSpawn0() { return spawn0; }

// returns spawn point #1
Vec2 world::Area::getSpawn1() { return spawn1; }

// returns spawn point #2
Vec2 world::Area::getSpawn2() { return spawn2; }

// returns spawn point #3
Vec2 world::Area::getSpawn3() { return spawn3; }

// returns spawn point #4
Vec2 world::Area::getSpawn4(){ return spawn4; }

// returns the tiles in the area.
std::vector<entity::Tile*> * world::Area::getAreaTiles() { return &areaTiles; }

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
void world::Area::writeToFile() { writeToFile(fileName); }

// writes the level data to a file.
void world::Area::writeToFile(std::string fileName)
{

}

// loads level information from a file if the file isn't empty.
void world::Area::loadFromFile()
{

}

// updates the area
void world::Area::update(float deltaTime)
{
	// updates the scene tiles
	for (int i = 0; i < areaTiles.size(); i++)
		areaTiles.at(i)->update(deltaTime);

	// updates the enemies
	for (int i = 0; i < areaEnemies.size(); i++)
		areaEnemies[i]->update(deltaTime);
}



