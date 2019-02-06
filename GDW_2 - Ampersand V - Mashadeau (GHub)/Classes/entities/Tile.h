#pragma once
#include "entities/Entity.h"


namespace entity
{
	class Tile : public entity::Entity
	{
	public:
		Tile();
		~Tile();

		// gets the tile identification number.
		const unsigned int getTIN();

		// gets what letter the 
		const char getLetter() const;

	private:
		unsigned int TIN; // tile identification number. This can't be const because of validation checking, but it should be const.
		char LETTER; // the type of tile. Different tiles may be categorized under the same number, and be differentiated via letters.

	protected:

	};
}


