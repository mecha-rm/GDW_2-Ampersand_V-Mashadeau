// stores inclusions for all areas
#pragma once

#include "areas/Area.h"

#include "areas/AIN_X/AIN_X00.h"


struct World
{
	World() = default;

	// returns an area based on a passed AIN number.
	static Area * getArea(std::string AIN);

};

