// At the moment this class doesn't do anything
#pragma once
#include "entities/Entity.h"

namespace entity
{
	class Inactive : public entity::Entity
	{
	public:
		Inactive();
		~Inactive();

		// update loop
		void update(float deltaTime);

	private:

		// if this entity is restored, this determines whether it should be returned to its original form or not.
		bool reset = false;

	protected:
	};
}


