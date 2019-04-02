#include "areas/AIN_F/AIN_F00.h"


// using an initalizer list with the variables, caused problems, so a test background is loaded in. These are replaced later.
world::AIN_F00::AIN_F00() : Area("")
{
	bool flipY = false; // flip the tiles and enemies positions on the y-axis

	name = "F00";
	Area::setBackgroundLayer1(bg_img1);
	Area::setBackgroundLayer2(bg_img2);
	Area::setBackgroundLayer3(bg_img3);
	Area::setForegroundLayer(fg_img);

	// there is a default gravity for all areas, so this line isn't required. However, if you want custom gravity for your area, you change it here.
	// setGravity(200.0F); // sets the level of gravity in the scene. This should NOT be negative.

	// setting all of the exits. Format: AIN_###_#
	// - the last digit (after the second underscore) determines what spawn point to use.
	exit0 = "AIN_F01_0"; //AIN_F00_0
	exit1 = "";
	exit2 = "";
	exit3 = "";
	exit4 = "";

	// setting all of the spawn points. These are based on the middle of the sprite.
	spawn0 = Vec2(3200.0F, 224.0F);
	spawn1 = Vec2(0.0F, 3200.0F);
	spawn2 = Vec2(0.0F, 0.0F);
	spawn3 = Vec2(0.0F, 0.0F);
	spawn4 = Vec2(0.0F, 0.0F);

	Area::tileArrayToVector(tileGrid, flipY); // set to 'true' to flip the tiles along the y-axis
	Area::enemyArrayToVector(enemyGrid, flipY); // set to 'true' to flip the enemies along the y-axis.
}