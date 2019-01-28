// Level data for AIN_X00
#pragma once

#include "areas/Area.h"

class AIN_X00 : public Area
{
public:
	AIN_X00();
	~AIN_X00();

private:
	// holds file paths for background images. Make sure you alter the constructor if you fill in these spaces.
	std::string bg_img1 = "images/backgrounds/AIN_X00a.png";
	std::string bg_img2 = "";
	std::string bg_img3 = "";

	// holds file path for foreground images.
	std::string fg_img = "";
};

