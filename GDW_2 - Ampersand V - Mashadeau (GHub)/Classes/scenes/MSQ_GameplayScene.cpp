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
	// Scene * scene = Scene::createWithPhysics(); // create with physics

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
	// MOUSE LISTENER SETUP
	// uses enablers to activate or disable certain listeners.
	// creates the mouse listener
	getEventDispatcher()->addEventListenerWithFixedPriority(mouse.getListener(), 1); // adds a mouse listener to the scene using the event dispatcher. It has a priority of 1.
	mouse.getListener()->setEnabled(ENABLE_MOUSE); // sets whether the mouse is enabled or not.

	// KEYBOARD LISTENER SETUP
	// creates the keyboard listener
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MSQ_GameplayScene::onKeyPressed, this); // creating key pressed callback
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MSQ_GameplayScene::onKeyReleased, this); // creacting key released callback

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this); // adds the keyboard listener to the event dispatcher
	keyboardListener->setEnabled(ENABLE_KEYBOARD); // enables the keyboard if it is meant to be turned on.


	// CONTACT LISTENER SETUP
	// adds the contact listener to the scene
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = std::bind(&MSQ_GameplayScene::OnContactBeginCallback, this, std::placeholders::_1); // creates the callback
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this); // adding the contact listener to the scene
	contactListener->setEnabled(ENABLE_CONTACT); // determines whether the contact listener is on or not.
}

// initalizes all sprites
void MSQ_GameplayScene::initSprites() 
{
	// creating the scene
	sceneArea = world::World::getArea("AIN_X00"); // makes the area. Remember, all the anchour points are the middle of the sprite layers (0.5, 0.5).
	sceneArea->setAllLayerPositions(Vec2(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height / 2)); // makes all the layers be at the middle of the screen.
	
	this->addChild(sceneArea->getAsSingleNode()); // gets the scene graphic elements (hitboxes not withstanding) as a single node.

	sceneTiles = sceneArea->getAreaTiles(); // saves a pointer to the scene tiles
	sceneEnemies = sceneArea->getAreaEnemies(); // saves a pointer to the scene enmies
	
	// creating the player; the default values handle the creation process.
	plyr = new entity::Player(); // creates the player
	plyr->setPosition(sceneArea->getSpawn0()); // sets the player using spawn point 0.
	this->addChild(plyr->getSprite());

	grid = new OOP::PrimitiveGrid(cocos2d::Vec2(0.0F, 0.0F), cocos2d::Vec2(director->getWinSizeInPixels().width, director->getWinSizeInPixels().height), 128.0F, Color4F::WHITE);
	grid->getPrimitive()->setGlobalZOrder(10.1F); // makes the grid be above everything else.
	grid->getPrimitive()->setVisible(true); // makes the grid visible (or not visible)
	this->addChild(grid->getPrimitive()); // adds grid to drawList

	this->getDefaultCamera()->setAnchorPoint(Vec2(0.5F, 0.5F)); // setting the camera's anchour point
	this->getDefaultCamera()->setPosition(plyr->getPosition()); // sets the location of the camera
}

// initializes pause menu; currently does nothing.
void MSQ_GameplayScene::initPauseMenu() {}

//// CALLBACKS /////////////////////////////////////////////////////////////
void MSQ_GameplayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveUp = true;
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveDown = true;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveLeft = true;
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveRight = true;
		break;
	}

	// change last parameter to check for key codes
	// if(keyCode == EventKeyboard::KeyCode::KEY_0)
}

void MSQ_GameplayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event
	
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveUp = false;
		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		moveDown = false;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveLeft = false;
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveRight = false;
		break;
	}
}

bool MSQ_GameplayScene::OnContactBeginCallback(PhysicsContact & contact)
{
	// gets the two nodes thar are being checked for collision.
	Node * nodeA = contact.getShapeA()->getBody()->getNode();
	Node * nodeB = contact.getShapeB()->getBody()->getNode();
	
	// sets the tags for both nodeA and nodeB, getting them from the two shapes being compared.
	nodeA->setTag(contact.getShapeA()->getBody()->getTag());
	nodeB->setTag(contact.getShapeB()->getBody()->getTag());

	if (!(nodeA && nodeB)) // if one of these nodes do not exist, then a 'false' is returned.
		return false;

	
	if (nodeA->getTag() == entity::player) // if the node A has a 'player' tag
	{
		switch (nodeB->getTag()) // depending on the tag of the second node, different functions are called.
		{
		case entity::tile:
			playerTileCollision(nodeB->getPosition());
			break;
		case entity::enemy:
			playerEnemyCollision(nodeB->getPosition());
			break;
		case entity::item:
			playerItemCollision(nodeB->getPosition());
			break;
		}
	}
	else if (nodeA->getTag() == entity::enemy) // if node A has an enemy tag
	{
		switch (nodeB->getTag()) // depending on the tag of the second node, different functions are called.
		{
		case entity::tile:
			enemyTileCollision(nodeA->getPosition(), nodeB->getPosition());
			break;
		case entity::weapon:
			enemyWeaponCollision(nodeA->getPosition(), nodeB->getPosition());
			break;
		}
	}

	return false;
}

// called to find the tile the player is colliding with, and handle what happens, based on the position(s).
void MSQ_GameplayScene::playerTileCollision(Vec2 tilePos)
{
	entity::Tile * sceneTile; // saves the tile that the player has collided with

	for each (entity::Tile * tile in *sceneTiles)
	{
		if (tile->getPosition() == tilePos) // if the tile has been found.
		{
			sceneTile = tile;
			break;
		}
	}
}

// called to find the enemy the player is colliding with, and handle what happens, based on the position(s).
void MSQ_GameplayScene::playerEnemyCollision(Vec2 enemyPos)
{
	entity::Enemy * sceneEnemy; // saves the tile that the player has collided with

	for each (entity::Enemy * enemy in *sceneEnemies)
	{
		if (enemy->getPosition() == enemyPos) // if the enemy has been found.
		{
			sceneEnemy = enemy;
			break;
		}
	}
}

// called to find the item the player is colliding with, and handle what happens, based on the position(s).
void MSQ_GameplayScene::playerItemCollision(Vec2 itemPos)
{
	// TODO: add an item vector and get the item
}

// called to find what tile the enemy is colliding with, based on the position(s).
void MSQ_GameplayScene::enemyTileCollision(Vec2 enemyPos, Vec2 tilePos)
{
	entity::Enemy * sceneEnemy;
	entity::Tile * sceneTile;

	for each (entity::Enemy * enemy in *sceneEnemies) // finds the enemy
	{
		if (enemy->getPosition() == enemyPos) // if the enemy has been found.
		{
			sceneEnemy = enemy;
			break;
		}
	}

	for each (entity::Tile * tile in *sceneTiles) // finds the tile
	{
		if (tile->getPosition() == tilePos) // if the tile has been found.
		{
			sceneTile = tile;
			break;
		}
	}

}

// called to find what enemy the weapon is colliding with, based on the position(s).
void MSQ_GameplayScene::enemyWeaponCollision(Vec2 enemyPos, Vec2 weaponPos)
{
	// TODO: check enemy collison with player weapons
}

// update loop
void MSQ_GameplayScene::update(float deltaTime)
{
	this->getDefaultCamera()->setPosition(plyr->getPosition()); // sets the position of the camera so that it follows hte player
	sceneArea->setAllLayerPositions(this->getDefaultCamera()->getPosition()); // makes the backgrounds be directly behind the player. This needs to be changed later so that it scrolls.

	// These movement parameters will need to be changed later.
	if (moveUp)
	{
		plyr->addMoveForceY();
	}
	else if (moveDown)
	{
		plyr->addForce(0.0F, plyr->getMoveForceY() * -1);
	}

	if (moveLeft)
	{
		plyr->addForce(plyr->getMoveForceX() * -1, 0.0F);
	}
	else if (moveRight)
	{
		plyr->addForce(plyr->getMoveForceX(), 0.0F);
	}

	// updates the player
	plyr->update(deltaTime);
	// updates the area the player is currently in. This update also updates the scene tiles, and enemies.
	sceneArea->update(deltaTime);
}






