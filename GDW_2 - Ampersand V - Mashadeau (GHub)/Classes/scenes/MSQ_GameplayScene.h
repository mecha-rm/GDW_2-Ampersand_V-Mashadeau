// The main gameplay scene for the game
#pragma once

#include "areas/World.h"
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

	void initKeyboardListener(); // used for keyboard actions
	void initContactListener(); // used for collision;
	void initSprites();
	void initPauseMenu();

	// callbacks
	void keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	void keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go
	bool onContactBeginCallback(PhysicsContact& contact); // listening for hit detection (which we're not supposed to use)

	// update function for the scene
	void update(float deltaTime);

	CREATE_FUNC(MSQ_GameplayScene);

protected:
private:
	Director * director; // engine
	OOP::MouseListener mouse; // the mouse functions
	
	// event listeners
	EventListenerKeyboard* keyboardListener;
	
	// event Helpers
	bool mouseDown;
	Vec2 mousePosition;

	// event toggles; these turn certain functions on or off.
	const bool ENABLE_MOUSE = true; // turns mouse functionality on/off.
	const bool ENABLE_KEYBOARD = true; // turns keyboard functionality on/off.
	const bool ENABLE_CONTACT = true; // turns collision functionality on/off.

	bool gridVisible = false; // turns on the grid.
	OOP::PrimitiveGrid * grid; // stores the grid information

	// bool collisionVisible; // turns on collision boxes and circles
	// DrawNode * collisions; // will store primitives that show hitboxes of everything.

	Area * sceneArea; // the current area of the scene

	static std::vector<Area *> areas; // this will save the areas gone to, and will be used to switch screens if scenes are not stored. These will be stored in dat files later on.
	static std::vector <Scene *> loadedScenes; // if scenes remain loaded, then this will be used to return to a previous scene
	
} GameplayScene;
