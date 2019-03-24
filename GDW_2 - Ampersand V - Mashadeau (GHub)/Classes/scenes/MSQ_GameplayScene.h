// The main gameplay scene for the game
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
	MSQ_GameplayScene();

	static void preloadAudio();

	// Creates a gameplay scene.
	static Scene* createScene();

	// called when the scene is entered
	void onEnter();

	// initialization functions
	bool init(); // what's called when the Cocos2D-X scene is created.
	void initListeners(); // initalizes event handlers
	void initSprites();
	void initPauseMenu();

	// callbacks
	void onMousePressed(EventMouse::MouseButton mouseButt, Event* event); //if a mouse button is pressed
	void onMouseReleased(EventMouse::MouseButton mouseButt, Event* event); //if a mouse button is released
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go

	// switches from one area to another. The format is as follows: AIN_###_#.
	// the last digit is needed to know what spawn point to use. It must be greater than or equal to 0, and not exceed 4 (it can be 4 though).
	// if the string does not have a length of 9, an exception is thrown.
	void switchArea(std::string & fileName);

	// called to handle collisions between entities.
	void collisions();
	
	
	void playerTileCollisions(); // player tile collisions
	void playerEnemyCollisions(); // player enemy collisions


	// update function for the scene
	void update(float deltaTime);

	CREATE_FUNC(MSQ_GameplayScene);

private:
	Director * director; // engine
	OOP::MouseListener mouse; // the mouse functions
	OOP::KeyboardListener keyboard;
	
	// event listeners
	EventListenerKeyboard* keyboardListener;

	// event toggles; these turn certain functions on or off.
	const bool ENABLE_MOUSE = true; // turns mouse functionality on/off.
	const bool ENABLE_KEYBOARD = true; // turns keyboard functionality on/off.
	const bool ENABLE_CONTACT = true; // turns collision functionality on/off.

	bool gridVisible = false; // turns on the grid.
	OOP::PrimitiveGrid * grid = nullptr; // stores the grid information

	// gets a reference to the 'shapesVisible' so that the collision spaces can be turned on/off from the scene file.
	bool * shapesVisible = &entity::Entity::shapesVisible;

	// bool collisionVisible; // turns on collision boxes and circles
	// DrawNode * collisions; // will store primitives that show hitboxes of everything.

	world::Area * sceneArea; // the current area of the scene
	bool switchingScenes = false; // becomes 'true' when the scenes are being switched so that the switch animation doesn't get restarted over and over.
	
	static std::string areaName; // saves the current area of the scene. This will be used for loading and unloading areas. This is only used upon scene initialization.
	static int spawnPoint; // the spawn point used upon entering the area. This is only used upon scene initialization.

	entity::Player * plyr; // the object used for the player

	// static std::vector<world::Area *> areas; // this will save the areas gone to, and will be used to switch screens if scenes are not stored. These will be stored in dat files later on.
	
	std::vector<entity::Tile *> * sceneTiles; // the tiles in the scene, which are gotten from the Area class.
	std::vector<entity::Enemy *> * sceneEnemies; // the enemies in the scene, which are gotten from the Area class.
	
	DrawNode * hud; // the drawNode used for making the hud.
	const int BAR_LEN = 3;
	// The items used for the health bar.
	/*
	 * [0]: the front of the hp bar, which is an overlay. 
	 * [1]: the actual bar that decreases as part of the hp bar.
	 * [2]: the back of the hp bar, which is what appears as the health bar goes down.
	*/
	Sprite * hpBar[3]; // an array used for holding sprite information on the hpbar
	Rect hpBarRect; // used to recall how big each image for the hpBar is. This is set in the gameplay scene.

	/*
	 * [0]: the front of the hp bar, which is an overlay.
	 * [1]: the actual bar that decreases as part of the magic bar.
	 * [2]: the back of the magic bar, which is what appears as the health bar goes down.
	*/
	Sprite * mpBar[3] { nullptr, nullptr, nullptr };


	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool jump = false;


protected:

} GameplayScene;
