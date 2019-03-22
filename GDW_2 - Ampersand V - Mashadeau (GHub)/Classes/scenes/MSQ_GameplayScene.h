// The main gameplay scene for the game
#pragma once

#include "areas/World.h"
#include "entities/Player.h"

#include "Primitives.h"
#include "MouseListener.h"
#include "KeyboardListener.h"
#include "cocos2d.h"
#include "audio/Audio.h"
#include <vector>

using namespace cocos2d;

typedef class MSQ_GameplayScene : public Scene
{
public:
	MSQ_GameplayScene();
	~MSQ_GameplayScene();

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
	bool OnContactBeginCallback(PhysicsContact& contact); // listening for hit detection (which we're not supposed to use)

	// called to handle collisions between entities.
	void collisions();
	
	
	void playerTileCollisions(); // player tile collisions
	void playerEnemyCollisions(); // player enemy collisions

	// These are leftovers from when we tried to use physics objects. These should be removed in the final product.
	// These are meant to be used with physics bodies. These are NOT being used at this time.
	// called to find the tile the player is colliding with, and handle what happens, based on the position(s).
	void playerTileCollision(Vec2 tilePos);
	// called to find the enemy the player is colliding with, and handle what happens, based on the position(s).
	void playerEnemyCollision(Vec2 enemyPos);
	// called to find the item the player is colliding with, and handle what happens, based on the position(s).
	void playerItemCollision(Vec2 itemPos);
	
	// called to find what tile the enemy is colliding with, based on the position(s).
	void enemyTileCollision(Vec2 enemyPos, Vec2 tilePos);
	// called to find what enemy the weapon is colliding with, based on the position(s).
	void enemyWeaponCollision(Vec2 enemyPos, Vec2 weaponPos);


	// update function for the scene
	void update(float deltaTime);

	CREATE_FUNC(MSQ_GameplayScene);

protected:
private:
	Director * director; // engine
	OOP::MouseListener mouse; // the mouse functions
	OOP::KeyboardListener keyboard;
	
	// event listeners
	EventListenerKeyboard* keyboardListener;
	EventListenerPhysicsContact * contactListener; // used for listening for collisions

	// event toggles; these turn certain functions on or off.
	const bool ENABLE_MOUSE = true; // turns mouse functionality on/off.
	const bool ENABLE_KEYBOARD = true; // turns keyboard functionality on/off.
	const bool ENABLE_CONTACT = true; // turns collision functionality on/off.

	bool gridVisible = false; // turns on the grid.
	OOP::PrimitiveGrid * grid; // stores the grid information

	// gets a reference to the 'shapesVisible' so that the collision spaces can be turned on/off from the scene file.
	bool * shapesVisible = &entity::Entity::shapesVisible;

	// bool collisionVisible; // turns on collision boxes and circles
	// DrawNode * collisions; // will store primitives that show hitboxes of everything.

	world::Area * sceneArea; // the current area of the scene
	entity::Player * plyr; // the object used for the player

	static std::vector<world::Area *> areas; // this will save the areas gone to, and will be used to switch screens if scenes are not stored. These will be stored in dat files later on.
	
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
	Sprite * mpBar[3];


	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;
	bool jump = false;

} GameplayScene;
