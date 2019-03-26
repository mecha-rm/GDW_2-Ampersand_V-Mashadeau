#pragma once
#include "entities/Inactive.h"

namespace entity
{
	class Item : public Inactive
	{
	public:
		// class for making items.
		Item(unsigned int IIN);
		~Item();

		// returns the item identification number.
		unsigned int getIIN();

		void update(float deltaTime);

	private:

		// creates an item based on the pased IIN
		void createItem(unsigned int IIN);
		
		// the item identification number
		unsigned int IIN;
		

	protected:
	
	};
}


