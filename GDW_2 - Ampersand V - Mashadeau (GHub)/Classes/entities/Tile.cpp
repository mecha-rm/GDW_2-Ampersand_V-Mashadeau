#include "entities/Tile.h"



entity::Tile::Tile(int type, char letter, unsigned int copyUp, unsigned int copyRight, unsigned int copyDown, int copyLeft)
{
}


entity::Tile::~Tile()
{
}
const unsigned int entity::Tile::getTIN()
{
	return TIN;
}
// the letter of the tile
const char entity::Tile::getLetter() const { return LETTER; }
