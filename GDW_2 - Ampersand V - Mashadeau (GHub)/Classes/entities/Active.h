#pragma once
#include "entities/Entity.h"

namespace entity
{
	class Active : public Entity
	{
	public:
		Active();
		~Active();
	
	private:

	protected:
		float health;
		float atkPWR;
	};
}


