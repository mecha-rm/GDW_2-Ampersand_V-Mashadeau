// The main gameplay scene for the game
#pragma once

#include "areas/World.h"
#include "entities/Player.h"

#include "Primitives.h"
#include "MouseListener.h"

#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

typedef class MSQ_GameplayScene : public Scene
{
public:
	MSQ_GameplayScene();
	~MSQ_GameplayScene();

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
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go
	bool OnContactBeginCallback(PhysicsContact& contact); // listening for hit detection (which we're not supposed to use)

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
	
	// event listeners
	EventListenerKeyboard* keyboardListener;
	EventListenerPhysicsContact * contactListener; // used for listening for collisions

	// event toggles; these turn certain functions on or off.
	const bool ENABLE_MOUSE = true; // turns mouse functionality on/off.
	const bool ENABLE_KEYBOARD = true; // turns keyboard functionality on/off.
	const bool ENABLE_CONTACT = true; // turns collision functionality on/off.

	bool gridVisible = false; // turns on the grid.
	OOP::PrimitiveGrid * grid; // stores the grid information

	// bool collisionVisible; // turns on collision boxes and circles
	// DrawNode * collisions; // will store primitives that show hitboxes of everything.

	world::Area * sceneArea; // the current area of the scene
	entity::Player * plyr; // the object used for the player

	static std::vector<world::Area *> areas; // this will save the areas gone to, and will be used to switch screens if scenes are not stored. These will be stored in dat files later on.
	
	std::vector<entity::Tile *> * sceneTiles; // the tiles in the scene, which are gotten from the Area class.
	std::vector<entity::Enemy *> * sceneEnemies; // the enemies in the scene, which are gotten from the Area class.


	bool moveUp = false;
	bool moveDown = false;
	bool moveLeft = false;
	bool moveRight = false;

} GameplayScene;
