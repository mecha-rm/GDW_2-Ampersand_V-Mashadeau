// stores inclusions for all areas
#pragma once

#include "areas/Area.h"

//DEBUG
#include "areas/AIN_X/AIN_X00.h"
#include "areas/AIN_X/AIN_X01.h"

//CASTLE
//#include "areas/AIN_A/AIN_A00.h"
//#include "areas/AIN_A/AIN_A01.h"

//SHADOW
#include "areas/AIN_B/AIN_B00.h"
#include "areas/AIN_B/AIN_B01.h"

//FIRE
#include "areas/AIN_C/AIN_C00.h"
#include "areas/AIN_C/AIN_C01.h"

//EARTH
//#include "areas/AIN_E/AIN_E00.h"
//#include "areas/AIN_E/AIN_E01.h"

//AIR
#include "areas/AIN_F/AIN_F00.h"
#include "areas/AIN_F/AIN_F01.h"

namespace world
{
	struct World
	{
		World() = default;

		// returns an area based on a passed AIN number.
		static world::Area * getArea(std::string & AIN);

	};
}

