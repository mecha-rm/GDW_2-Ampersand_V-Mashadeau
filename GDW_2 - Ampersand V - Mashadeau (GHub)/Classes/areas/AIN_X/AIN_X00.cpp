#include "areas/AIN_X/AIN_X00.h"


// using an initalizer list with the variables, caused problems, so a test background is loaded in. These are replaced later.
world::AIN_X00::AIN_X00() : Area("")
{
	bool flipY = false; // flip the tiles and enemies positions on the y-axis

	name = "X00";
	Area::setBackgroundLayer1(bg_img1);
	Area::setBackgroundLayer2(bg_img2);
	Area::setBackgroundLayer3(bg_img3);
	Area::setForegroundLayer(fg_img);
	
	// setGravity(200.0F); // sets the level of gravity in the scene. This should NOT be negative.

	Area::tileArrayToVector(tileGrid, flipY); // set to 'true' to flip the tiles along the y-axis
	Area::enemyArrayToVector(enemyGrid, flipY); // set to 'true' to flip the enemies along the y-axis.
}