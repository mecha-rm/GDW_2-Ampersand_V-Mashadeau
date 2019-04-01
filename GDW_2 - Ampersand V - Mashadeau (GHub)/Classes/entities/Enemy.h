#pragma once
#include "entities/Active.h"

namespace entity
{
	class Enemy :
		public Active
	{
	public:
		Enemy(unsigned int EIN, char letter = 'a', const unsigned int COPY_UP = 0, const unsigned int COPY_DOWN = 0, const unsigned int COPY_LEFT = 0, const unsigned int COPY_RIGHT = 0, const bool OFFSET_BY_SPRITE_SIZE = false);
		~Enemy();

		// gets the tile identification number.
		const unsigned int getEIN() const;

		// gets what letter the enemy has 
		const char getLetter() const;

		// the update loop
		void update(float deltaTime);

		// variable used for copying the enemy in the upward direction.
		const unsigned int COPY_UP = 0;
		// variable used for copying the enemy in the rightward direction.
		const unsigned int COPY_RIGHT = 0;
		// variable used for copying the enemy in the downwords direction.
		const unsigned int COPY_DOWN = 0;
		// variable used for copying the enemy in the leftward direction.
		const unsigned int COPY_LEFT = 0;

		// if true, when making copies of the sprite, the new sprite's location is an offset of the original sprite's location based on the sprite's size.
		// if this is false, then it is placed 128 px away from the sprite it was being copied from.
		const bool OFFSET_BY_SPRITE_SIZE = false;

		// if true, the enemy's movement force is applied in the positive y direction. If false, it's applied in the negative y direction.
		bool moveUp = false;
		// if true, the enemy's movement force is applied in the positive x direction. If false, it's applied in the negative x direction.
		bool moveRight = false;

	private:
		// called to create an Enemy and give it initial values.
		void createEnemy(unsigned int EIN, char letter);

		// setting the EIN value of the enemy
		unsigned int EIN;
		// setting the letter for the enemy
		char LETTER;

	protected:
		
	};
}



