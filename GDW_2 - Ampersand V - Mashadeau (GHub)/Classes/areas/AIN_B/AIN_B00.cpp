#include "areas/AIN_B/AIN_B00.h" // remember to change the file name and the second sub folder (in this case, AIN_X) to the appropriate locations


// using an initalizer list with the variables, caused problems, so a test background is loaded in. These are replaced later.
world::AIN_B00::AIN_B00() : Area("")
{
	bool flipY = false; // flip the tiles and enemies positions on the y-axis

	name = "B00";
	Area::setBackgroundLayer1(bg_img1);
	Area::setBackgroundLayer2(bg_img2);
	Area::setBackgroundLayer3(bg_img3);
	Area::setForegroundLayer(fg_img);

	// there is a default gravity for all areas, so this line isn't required. However, if you want custom gravity for your area, you change it here.
	// setGravity(200.0F); // sets the level of gravity in the scene. This should NOT be negative.

	Area::tileArrayToVector(tileGrid, flipY); // set to 'true' to flip the tiles along the y-axis
	Area::enemyArrayToVector(enemyGrid, flipY); // set to 'true' to flip the enemies along the y-axis.
}