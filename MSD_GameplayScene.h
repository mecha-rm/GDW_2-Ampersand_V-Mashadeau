// The main gameplay scene for the game
#pragma once

#include "cocos2d.h"

#include "areas/World.h"

#include <vector>

using namespace cocos2d;

typedef class MSD_GameplayScene : public Scene
{
public:
	MSD_GameplayScene();
	~MSD_GameplayScene();

	// Creates a gameplay scene.
	static Scene* createScene();

	// called when the scene is entered
	void onEnter();

	// initialization functions
	bool init(); // what's called when the Cocos2D-X scene is created.
	void initListeners(); // initalizes event handlers
	
	void initMouseListener(); // used for mouse actions
	void initKeyboardListener(); // used for keyboard actions
	void initContactListener(); // used for collision
	void initPauseMenu();
	void initSprites();

	// callbacks
	void mouseDownCallback(Event* event);
	void mouseUpCallback(Event* event);
	void mouseMoveCallback(Event* event);
	void mouseScrollCallback(Event* event);
	void keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	void keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go
	bool onContactBeginCallback(PhysicsContact& contact); // listening for hit detection (which we're not supposed to use)

	// update function for the scene
	void update(float deltaTime);

	CREATE_FUNC(MSD_GameplayScene);

protected:
private:
	Director * director; // engine
	
	// event listeners
	EventListenerMouse* mouseListener;
	EventListenerKeyboard* keyboardListener;
	
	// event Helpers
	bool mouseDown;
	Vec2 mousePosition;

	// event toggles; these turn certain functions on or off.
	bool enableMouse = true; // turns mouse functionality on/off.
	bool enableKeyboard = true; // turns keyboard functionality on/off.
	bool enableContact = true; // turns collision functionality on/off.

	Area sceneArea;
	

} GameplayScene;
