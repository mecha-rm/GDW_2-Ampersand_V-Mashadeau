#include "scenes/MSQ_GameplayScene.h"

#include <iostream>

// constructor; initalizes the mouse listener
MSQ_GameplayScene::MSQ_GameplayScene() : mouse(OOP::MouseListener(this)) {}

// destructor
MSQ_GameplayScene::~MSQ_GameplayScene() {}

Scene * MSQ_GameplayScene::createScene()
{
	// 'scene' is an autorelease object
	Scene * scene = Scene::create(); // create without physics
	// Scene* scene = Scene::createWithPhysics(); // create with physics
	auto * layer = MSQ_GameplayScene::create();

	scene->addChild(layer);
	// Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	return scene;
}

void MSQ_GameplayScene::onEnter() { Scene::onEnter(); }

bool MSQ_GameplayScene::init()
{
	// Ensure the parent init function was called first. If it wasn't, exit this one.
	if (!Scene::init())
		return false;

	director = Director::getInstance();

	// Initialize the event handlers
	initListeners();

	//Init the Sprites
	initSprites();

	// Initialize the pause menu
	initPauseMenu();

	// Allows for the update() function to be called by cocos
	this->scheduleUpdate();

	//Let cocos know that the init function was successful
	return true;
}

// initializes listners; there exists toggles that determine whether a certain listener is activated or not.
void MSQ_GameplayScene::initListeners()
{
	// uses enablers to activate or disable certain listeners.
	if (ENABLE_MOUSE) // adds a mouse listener to the scene using the event dispatcher if ENABLE_MOUSE is true. It has a priority of 1.
		getEventDispatcher()->addEventListenerWithFixedPriority(mouse.getListener(), 1);
		
	// Use this if you ever want to take out the mouse listener.
	// getEventDispatcher()->removeEventListener(mouse.getListener());

	if (ENABLE_KEYBOARD)
		initKeyboardListener(); // initalizes keyboard
	
	if (ENABLE_CONTACT)
		initContactListener(); // initalizes the contact listener

}

// Listens for keyboard input
void MSQ_GameplayScene::initKeyboardListener()
{
	// creating the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MSQ_GameplayScene::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MSQ_GameplayScene::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

// Listens for contact.
void MSQ_GameplayScene::initContactListener()
{
	// creating the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign callbacks
	contactListener->onContactBegin = CC_CALLBACK_1(MSQ_GameplayScene::onContactBeginCallback, this);

	//Add the listener to the event dispatcher
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

// initalizes all sprites
void MSQ_GameplayScene::initSprites() 
{
	sceneArea = World::getArea("AIN_X00"); // makes the area. Remember, all the anchour points are the middle of the sprite layers (0.5, 0.5).
	sceneArea->setAllLayerPositions(Vec2(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height / 2)); // makes all the layers be at the middle of the screen.
	this->addChild(sceneArea->getAsSingleNode()); // gets the backgrounds as one node.

	grid = new OOP::PrimitiveGrid(cocos2d::Vec2(0.0F, 0.0F), cocos2d::Vec2(director->getWinSizeInPixels().width, director->getWinSizeInPixels().height), 128.0F, Color4F::WHITE);
	grid->getPrimitive()->setVisible(true); // makes the grid visible (or not visible)
	this->addChild(grid->getPrimitive()); // adds grid to drawList
}

// initializes pause menu; currently does nothing.
void MSQ_GameplayScene::initPauseMenu() {}

//// CALLBACKS /////////////////////////////////////////////////////////////
void MSQ_GameplayScene::keyDownCallback(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event
	// change last parameter to check for key codes
	// if(keyCode == EventKeyboard::KeyCode::KEY_0)
}

void MSQ_GameplayScene::keyUpCallback(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event
}

bool MSQ_GameplayScene::onContactBeginCallback(PhysicsContact & contact)
{
	return false;
}

// update loop
void MSQ_GameplayScene::update(float deltaTime)
{
	// this->getDefaultCamera()->setPosition(/*player's position goes here*/);
}






