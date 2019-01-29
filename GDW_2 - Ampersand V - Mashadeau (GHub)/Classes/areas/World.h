// stores inclusions for all areas
#pragma once

#include "areas/Area.h"

#include "areas/AIN_X/AIN_X00.h"


struct World
{
public:
	World() = default;

	// returns an area based on a passed AIN number.
	static Area * getArea(const std::string AIN);

};

