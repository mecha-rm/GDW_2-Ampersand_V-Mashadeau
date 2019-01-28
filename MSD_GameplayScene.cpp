#include "scenes/MSD_GameplayScene.h"

// constructor
MSD_GameplayScene::MSD_GameplayScene() {}

// destructor
MSD_GameplayScene::~MSD_GameplayScene() {}

Scene * MSD_GameplayScene::createScene()
{
	// 'scene' is an autorelease object
	Scene* scene = Scene::create(); // create without physics
	// Scene* scene = Scene::createWithPhysics(); // create with physics
	MSD_GameplayScene* layer = MSD_GameplayScene::create();

	scene->addChild(layer);
	// Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	return scene;
}

void MSD_GameplayScene::onEnter() { Scene::onEnter(); }

bool MSD_GameplayScene::init()
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
void MSD_GameplayScene::initListeners()
{
	// uses enablers to activate or disable certain listeners.
	if (enableMouse)
		initMouseListener(); // init mouse
	
	if (enableKeyboard)
		initKeyboardListener(); // Init keyboard
	
	if (enableContact)
		initContactListener(); // Init the contact listener

}

// initalizes mouse listener
void MSD_GameplayScene::initMouseListener()
{
	////Init the mouse listener
	//mouseListener = EventListenerMouse::create();

	////On Mouse Down
	mouseListener->onMouseDown = CC_CALLBACK_1(MSD_GameplayScene::mouseDownCallback, this);

	////On Mouse Up
	mouseListener->onMouseUp = CC_CALLBACK_1(MSD_GameplayScene::mouseUpCallback, this);

	////On Mouse Move
	mouseListener->onMouseMove = CC_CALLBACK_1(MSD_GameplayScene::mouseMoveCallback, this);

	////On Mouse Scroll
	mouseListener->onMouseScroll = CC_CALLBACK_1(MSD_GameplayScene::mouseScrollCallback, this);

	////Add the mouse listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

// Listens for keyboard input
void MSD_GameplayScene::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MSD_GameplayScene::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MSD_GameplayScene::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void MSD_GameplayScene::initContactListener()
{
	//Create the contact listener
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	//Assign callbacks
	contactListener->onContactBegin = CC_CALLBACK_1(MSD_GameplayScene::onContactBeginCallback, this);

	//Add the listener to the event dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

// initalizes all sprites
void MSD_GameplayScene::initSprites() 
{
	sceneArea = World::getArea("AIN_X00"); // makes the area. Remember, all the anchour points are the middle of the sprite layers (0.5, 0.5).
	sceneArea->setAllLayerPositions(Vec2(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height / 2)); // makes all the layers be at the middle of the screen.
	

}

void MSD_GameplayScene::initPauseMenu() {}

//// CALLBACKS /////////////////////////////////////////////////////////////

void MSD_GameplayScene::mouseDownCallback(Event * event)
{
}

void MSD_GameplayScene::mouseUpCallback(Event * event)
{
}

void MSD_GameplayScene::mouseMoveCallback(Event * event)
{
}

void MSD_GameplayScene::mouseScrollCallback(Event * event)
{
}

void MSD_GameplayScene::keyDownCallback(EventKeyboard::KeyCode keyCode, Event * event)
{
}

void MSD_GameplayScene::keyUpCallback(EventKeyboard::KeyCode keyCode, Event * event)
{
}

bool MSD_GameplayScene::onContactBeginCallback(PhysicsContact & contact)
{
	return false;
}

void MSD_GameplayScene::update(float deltaTime)
{
}






