#pragma once
#include "entities/Entity.h"

namespace entity
{
	class Item : public Entity
	{
	public:
		// class for making items.
		Item(unsigned int IIN);
		~Item();

		// returns the item identification number.
		unsigned int getIIN();

	private:

		// creates an item based on the pased IIN
		void createItem(unsigned int IIN);
		
		// the item identification number
		unsigned int IIN;
		

	protected:
	
	};
}


