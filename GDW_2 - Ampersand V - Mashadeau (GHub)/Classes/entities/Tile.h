#pragma once
#include "entities/Entity.h"


namespace entity
{
	class Tile : public entity::Entity
	{
	public:
		/*
		* Creates a tile based on the type number passed.
		* type: the type number
		*
		* copyUp: the amount of copies you want to make of the tile in the upwards (positive y) direction.
		* copyRight: the amount of copies you want to make of the tile in the rightward (positive x) direction.
		*
		* copyDown: the amount of copies you want to make of the tile in the downwards (negative y) direction.
		* copyLeft: the amount of copies you want to make of the tile in the leftward (negative x) direction.
		*/
		Tile(int type, char letter, unsigned int copyUp = 0, unsigned int copyRight = 0, unsigned int copyDown = 0, int copyLeft = 0);
		~Tile();

		// gets the tile identification number.
		const unsigned int getTIN();

		// gets what letter the 
		const char getLetter() const;

	private:
		unsigned int TIN; // tile identification number. This can't be const because of validation checking, but it should be const.
		char LETTER; // the type of tile. Different tiles may be categorized under the same number, and be differentiated via letters.


		// Used for copying the tiles in all four directions.

		// variable used for copying the tile in the upward direction.
		unsigned int copyUp = 0;
		// variable used for copying the tile in the rightward direction.
		unsigned int copyRight = 0;

		// variable used for copying the tile in the downwords direction.
		unsigned int copyDown = 0;

		// variable used for copying the tile in the leftward direction.
		unsigned int copyLeft = 0;

	protected:

	};
}


