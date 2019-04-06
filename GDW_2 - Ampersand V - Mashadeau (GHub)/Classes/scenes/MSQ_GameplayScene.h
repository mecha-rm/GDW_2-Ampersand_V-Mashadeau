/*
Project: Mashadeau: Sorcerer's Quest (Game Development Workshop II (INFR 1396U) Video Game)
Team: Ampersand V (&V)
	- Caleb Birnie (100699828)
	- Carter Menary (100700587)
	- Devin Fitzpatrick (100709082)
	- Nathan Tuck (100708651)
	- Roderick “R.J.” Montague (100701758)
	- Jason Lee (100698121)
		*Jason Lee was only part of this group for the purposes of Digital Game Design.
		*Jason is not in Essential Mathematics for Games II, Object Oriented Programming, or Game Development Workshop II.
Date: 04/04/2019
*/

// The main gameplay scene for the game. When a new area is entered, a new instance of this is made.
#pragma once

#include "areas/World.h"
#include "entities/Player.h"

#include "Primitives.h"
#include "MouseListener.h"
#include "KeyboardListener.h"
#include "audio/AudioLibrary.h"

#include "scenes/MSQ_TransitionerScene.h"
#include "cocos2d.h"
#include <vector>
#include <string>

using namespace cocos2d;

typedef class MSQ_GameplayScene : public Scene
{
public:
	// constructor
	MSQ_GameplayScene();

	// loads up audio for the scene.
	static void preloadAudio();

	// creates a gameplay scene.
	static Scene* createScene();

	// called when the scene is entered
	void onEnter();
	// called when leaving the scene
	void onExit();

	// initialization functions
	bool init(); // what's called when the Cocos2D-X scene is created.
	void initListeners(); // initalizes event handlers
	void initSprites(); // initializes sprites
	void initPauseMenu(); // initializes a pause menu, which we could not get implemented in time. It is empty.


	// callbacks for the mouse
	void onMousePressed(EventMouse::MouseButton mouseButt, Event* event); // if a mouse button is pressed
	void onMouseReleased(EventMouse::MouseButton mouseButt, Event* event); // if a mouse button is released
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go
	
	// called to turn on and off some debug functions, i.e. switch debug settings.
	void debugMode();

	// switches from one area to another. The format is as follows: AIN_###_#.
	// the last digit is needed to know what spawn point to use. It must be greater than or equal to 0, and not exceed 4 (it can be 4 though). So it's just 0-4.
	// if the string does not have a length of 9 (which is what it should be under all circumstances), an exception is thrown.
	void switchArea(std::string & fileName);

	// called to exit the game. This handles information that should be removed or changed before the player starts a new game.
	void exitGame();

	// called to handle collisions between entities.
	void collisions();
	
	
	void playerTileCollisions(); // player tile collisions
	void enemyTileCollisions(); // enemy-tile collisions
	void playerEnemyCollisions(); // player enemy collisions
	void weaponEnemyCollisions(); // collisions between the player's weapon and the enemies.


	// update function for the scene
	void update(float deltaTime);
	
	CREATE_FUNC(MSQ_GameplayScene);

	Size winSize; // the window size. Used for optimizing update loops and collisions.
	bool canJump = true; // used to check if the player should be allowd to jump or not.


private:

	Director * director; // cocos engine
	OOP::MouseListener mouse; // the mouse functions
	OOP::KeyboardListener keyboard; // the keyboard functions

	const bool ENABLE_MOUSE = true; // turns mouse functionality on/off.
	const bool ENABLE_KEYBOARD = true; // turns keyboard functionality on/off.
	const bool ENABLE_CAMERA = true; // enables (or disables) the game camera.

	static bool debug; // becomes 'true' when debug mode is turned on.
	static bool enable_hud; // enables the hud, or disables it.

	bool gridVisible = false; // turns on the grid visibility.
	OOP::PrimitiveGrid * grid = nullptr; // stores the grid information.
	Vec2 gridOffset = Vec2(0.0F, 0.0F); // the position offset of the grid so that it remains in the smae place with a moving camera.

	// gets a reference to the 'shapesVisible' variable so that the collision spaces can be turned on/off from the scene file.
	bool * shapesVisible = &entity::Entity::shapesVisible;

	world::Area * sceneArea; // the current area of the scene
	bool switchingScenes = false; // becomes 'true' when the scenes are being switched so that the switch animation doesn't play over and over, and so that the scene switch only gets called once.

	static std::string areaName; // saves the name of the current area. This is used for switching scenes and loading up the proper area code when the player leaves their current screen.
	static const std::string DEFAULT_AREA; // the default area the player starts in. This is used to send the player back to the beginning of the world when they lose all of their health.
	
	static int spawnPoint; // the spawn point used upon entering an area.
	// the areas that the player has visited. Originally, this was going to be used to load up stage data from previous visits versus reseting the area each time, but this did not work out.
	// this variable is still used in code, but ultimately does nothing.
	static std::vector<std::string> areasVisited;


	entity::Player * plyr; // the object used for the player.
	bool plyrAction = false; // becomes 'true' when a new animation should be played for the player.
	int pAction = 0; // saves the action the player is taking.
	
	// used for saving information between scenes.
	static int pHealth; // the player's current health when leaving the scene.
	static int pHealthMax; // the player's max health when leaving the scene.
	static int pMagic; // the player's magic amount when leaving the scene.
	static int pMagicMax; // the player's maximum magic amount when leaving the scene.
	static std::vector<int> pWeapons; // the player's weapons when leaving the scene.

	std::vector<entity::Tile *> * sceneTiles; // the tiles in the scene, which are gotten from the Area class.
	std::vector<entity::Enemy *> * sceneEnemies; // the enemies in the scene, which are gotten from the Area class.
	
	DrawNode * hud; // the drawNode used for making the hud.
	const int BAR_LEN = 3; // the amount of items in the health bar array (see below)
	
	/*
	 * The items used for the health bar and what they represent are explained below.
		 * [0]: the front of the hp bar, which is an overlay/frame. 
		 * [1]: the actual bar that decreases as part of the hp bar.
		 * [2]: the back of the hp bar, which is what appears as the health bar goes down.
	*/
	Sprite * hpBar[3]; // an array used for holding sprite information on the hpbar.
	Rect hpBarRect; // used to recall how big each image for the hpBar is. This is set in the gameplay scene.
	Vec2 hpBarPos = Vec2(0.0F, 0.0F); // the hp bar's position.
	Vec2 hpBarOffset = Vec2(0.0F, 0.0F); // the position of the hp bar proportional to the camera. This is used so that the hp bar doens't move when the player does.

	/*
	 * [0]: the front of the mp bar, which is an overlay.
	 * [1]: the actual indicator that decreases as part of the magic bar.
	 * [2]: the back of the magic bar, which is what appears as the magic bar goes down.
	*/
	Sprite * mpBar[3]; // holds sprite information for the magic bar
	Rect mpBarRect; // the rectangle that holds the size of the mp bar sprites. This is used to aid with cropping.
	Vec2 mpBarPos = Vec2(0.0F, 0.0F); // the position of the magic bar.
	Vec2 mpBarOffset = Vec2(0.0F, 0.0F); // an offset used to keep the mp bar in place.

	/*
	 * sprites added to the hud overlay.
	 * [0][y] = current, [1][y] = weapon 1, [2][y] = weapon 2, [3][y] = weapon 3
	 * [x][0] = outer frame, [x][1] = weapon image, [x][2] = background
	*/
	Sprite * hudWeapons[4][3]; // holds sprite information for the weapons on the overlay. The rows are the weapons, and the columns are the image assets.
	std::string weaponImages[4]{ "", "", "", "" }; // the weapon images that go in the hud.
	Rect weaponIconSize; // the size of the sprites, which are cropped out of a sprite sheet. The weapons themselves aren't, but the frame assets are.

	Vec2 hudWeaponOffset[4]; // the position offset for the weapon display so that it stays in place.
	const int HUD_WEAPONS_ROWS = 4; // the amount of rows in the weapon display.
	const int HUD_WEAPONS_COLS = 3; // the amount of columns in the weapon display.

protected:

} GameplayScene;
