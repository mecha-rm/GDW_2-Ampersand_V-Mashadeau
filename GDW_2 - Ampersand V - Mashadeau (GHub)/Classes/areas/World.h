// stores inclusions for all areas
#pragma once

#include "areas/Area.h"

#include "areas/AIN_F/AIN_F00.h"
#include "areas/AIN_F/AIN_F01.h"

#include "areas/AIN_X/AIN_X00.h"
#include "areas/AIN_X/AIN_X01.h"

namespace world
{
	struct World
	{
		World() = default;

		// returns an area based on a passed AIN number.
		static world::Area * getArea(std::string & AIN);

	};
}

