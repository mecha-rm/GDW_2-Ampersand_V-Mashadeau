#pragma once
#include "entities/Active.h"

namespace entity
{
	class Enemy :
		public Active
	{
	public:
		Enemy();
		~Enemy();

	private:
		unsigned int EIN;
		char letter;

	protected:

	};
}



