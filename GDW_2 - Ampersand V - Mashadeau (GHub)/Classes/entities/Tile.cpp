#include "entities/Tile.h"



entity::Tile::Tile()
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
