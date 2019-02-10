#pragma once
#include "entities/Entity.h"


namespace entity
{
	class Tile : public entity::Entity
	{
	public:
		/*
		* Creates a tile based on the type number passed.
		* TIN: the tile identification number
		*
		* COPY_UP: the amount of copies you want to make of the tile in the upwards (positive y) direction.
		* COPY_RIGHT: the amount of copies you want to make of the tile in the rightward (positive x) direction.
		*
		* COPY_DOWN: the amount of copies you want to make of the tile in the downwards (negative y) direction.
		* COPY_LEFT: the amount of copies you want to make of the tile in the leftward (negative x) direction.
		* OFFSET_BY_SPRITE_SIZE: when making copies of a sprite, there are two ways the new sprite's position can be offset from the original sprite.
			- if this variable is 'true', then the sprite is offset by the actual size of the sprite's image area.
			- if this variable is 'false', hten the sprite is offset by 128 px, the standard tile size.
		*/
		Tile(unsigned int TIN, char letter = 'a', const unsigned int COPY_UP = 0, const unsigned int COPY_DOWN = 0, const unsigned int COPY_LEFT = 0, const unsigned int COPY_RIGHT = 0, const bool OFFSET_BY_SPRITE_SIZE = false);
		~Tile();

		// gets the tile identification number.
		const unsigned int getTIN() const;

		// gets what letter the 
		const char getLetter() const;

		// Used for copying the tiles in all four directions.

		// variable used for copying the tile in the upward direction.
		const unsigned int COPY_UP = 0;
		// variable used for copying the tile in the rightward direction.
		const unsigned int COPY_RIGHT = 0;
		// variable used for copying the tile in the downwords direction.
		const unsigned int COPY_DOWN = 0;
		// variable used for copying the tile in the leftward direction.
		const unsigned int COPY_LEFT = 0;

		// if true, when making copies of the sprite, the new sprite's location is an offset of the original sprite's location based on the sprite's size.
		// if this is false, then it is placed 128 px away from the sprite it was being copied from.
		const bool OFFSET_BY_SPRITE_SIZE = false;

	private:
		// called to create the tile and give it its initial values
		void createTile(unsigned int TIN, char letter);

		unsigned int TIN; // tile identification number. This can't be const because of validation checking, but it should be const.
		char LETTER; // the type of tile. Different tiles may be categorized under the same number, and be differentiated via letters.
	protected:

	};
}


