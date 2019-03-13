#include "scenes/MSQ_GameplayScene.h"

#include <iostream>

// constructor; initalizes the mouse listener
MSQ_GameplayScene::MSQ_GameplayScene() : mouse(OOP::MouseListener(this)), keyboard(OOP::KeyboardListener(this)) {}

// destructor
MSQ_GameplayScene::~MSQ_GameplayScene() {}

Scene * MSQ_GameplayScene::createScene()
{
	// 'scene' is an autorelease object
	// Scene * scene = Scene::create(); // create without physics
	Scene * scene = Scene::createWithPhysics(); // create with physics
	scene->getPhysicsWorld()->setGravity(Vec2(0.0F, 0.0F));
	// scene->getPhysicsWorld()->set
	GameplayScene * layer = MSQ_GameplayScene::create();

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

	// the mouse listener gets added to the scene that is passed, so the line below is no longer needed.
	// getEventDispatcher()->addEventListenerWithFixedPriority(mouse.getListener(), 1); // adds a mouse listener to the scene using the event dispatcher. It has a priority of 1.
	
	mouse.setLabelVisible(true); // sets whether the label is visible or not.
	mouse.getListener()->setEnabled(ENABLE_MOUSE); // sets whether the mouse is enabled or not.

	// KEYBOARD LISTENER SETUP
	// creates the keyboard listener
	/*
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(MSQ_GameplayScene::onKeyPressed, this); // creating key pressed callback
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MSQ_GameplayScene::onKeyReleased, this); // creacting key released callback

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this); // adds the keyboard listener to the event dispatcher
	keyboardListener->setEnabled(ENABLE_KEYBOARD); // enables the keyboard if it is meant to be turned on.
	*/

	keyboard.setLabelVisible(false);
	keyboard.getListener()->onKeyPressed = CC_CALLBACK_2(MSQ_GameplayScene::onKeyPressed, this);
	keyboard.getListener()->onKeyReleased = CC_CALLBACK_2(MSQ_GameplayScene::onKeyReleased, this);
	keyboard.getListener()->setEnabled(ENABLE_KEYBOARD); // enables (or disables) keyboard
	


	/*
	// CONTACT LISTENER SETUP
	// adds the contact listener to the scene
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(MSQ_GameplayScene::OnContactBeginCallback, this);
	// contactListener->onContactBegin = std::bind(&MSQ_GameplayScene::OnContactBeginCallback, this, std::placeholders::_1); // creates the callback
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this); // adding the contact listener to the scene
	contactListener->setEnabled(ENABLE_CONTACT); // determines whether the contact listener is on or not.
	*/
}

// initalizes all sprites
void MSQ_GameplayScene::initSprites() 
{
	// the hp bar's position
	Vec2 hpBarPos{ director->getWinSizeInPixels().width * 0.135F, director->getWinSizeInPixels().height * 0.96F };
	// the magic bar's position
	Vec2 mpBarPos;

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

	// creating the hud
	hud = DrawNode::create(); // creating the hud
	hpBarRect = Rect(0.0F, 0.0F, 465.0F, 67.0F); // the size of an individual space
	
	// initalizes the HP bar
	// [0] = front, [1] = middle (the part that shows the actual HP), [2] = back
	for (int i = 0; i < BAR_LEN; i++)
	{
		hpBar[i] = Sprite::create("images/HP_BAR_A.png"); // creates the sprite.
		hpBar[i]->setTextureRect(Rect(0.0F, 0.0F + hpBarRect.getMaxY() * i, hpBarRect.getMaxX(), hpBarRect.getMaxY())); // sets what section of the image to use.
		// test = hpBar[i]->getTextureRect();

		hpBar[i]->setPosition(hpBarPos); // moves the bar to the proper place.
		hpBar[i]->setLocalZOrder(3.0 - i); // sets the local z-order.
		hpBar[i]->setGlobalZOrder(10.0F); // sets the global z-order.

		hud->addChild(hpBar[i]);
	}

	this->addChild(hud);

	// creating the grid
	grid = new OOP::PrimitiveGrid(cocos2d::Vec2(0.0F, 0.0F), cocos2d::Vec2(director->getWinSizeInPixels().width, director->getWinSizeInPixels().height), 128.0F, Color4F::WHITE);
	// grid->getPrimitive()->setGlobalZOrder(10.3F); // makes the grid be above everything else.
	grid->getPrimitive()->setVisible(true); // makes the grid visible (or not visible)
	this->addChild(grid->getPrimitive()); // adds grid to drawList


	// setting the camera
	// this->getDefaultCamera()->setAnchorPoint(Vec2(0.5F, 0.5F)); // setting the camera's anchour point
	// this->getDefaultCamera()->setPosition(plyr->getPosition()); // sets the location of the camera

	
	/* 
	// Tester things; ignore this.
	// DrawNode().setRot
	// sceneTiles->at(0)->getPosition().x - 64.0F, sceneTiles->at(0)->getPosition().y - 64.0F, 128.0F, 128.0F
	sceneTiles->at(0)->rotateEntity(umath::degreesToRadians(30.0F), Vec2(0, 0));
	DrawNode * drawNode(DrawNode::create());
	drawNode->drawRect(Vec2(sceneTiles->at(0)->getPosition().x - 64.0F, sceneTiles->at(0)->getPosition().y - 64.0F), Vec2(sceneTiles->at(0)->getPosition().x + 64.0F, sceneTiles->at(0)->getPosition().y + 64.0F), Color4F::RED);
	drawNode->drawRect(Vec2(plyr->getPosition().x - 37.0f, plyr->getPosition().y - 91.0F), Vec2(plyr->getPosition() + Vec2(37.0F, 91.0F)), Color4F::RED);
	// drawNode->setRotation(30.0F);
	drawNode->setGlobalZOrder(20.0F);
	this->addChild(drawNode);
	*/
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

	case EventKeyboard::KeyCode::KEY_SPACE:
		jump = true;
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

// runs collision tests.
void MSQ_GameplayScene::collisions()
{
	
	// std::cout << "PX: " << plyr->getAABBs().at(0)->getPosition().x << ", PY: " << plyr->getAABBs().at(0)->getPosition().y << std::endl;
	playerTileCollisions(); // called for player-tile collisions.
	playerEnemyCollisions(); // called for player collisions with enemies
}

// calculates player collision with tiles.
void MSQ_GameplayScene::playerTileCollisions()
{
	entity::Tile * tile = nullptr;

	OOP::Primitive * colPrim1; // the primitive from the player that encountered a collision
	OOP::Primitive * colPrim2; // the primitive from the other entity that encounted a collision
	
	cocos2d::Vec2 distVec(0.0F, 0.0F); // saves the distance between the two entities on the (x, y)
	cocos2d::Vec2 minDistVec(0.0F, 0.0F); // saves the minimum distance 
	float dist = 0.0F; // the distance between the two entities, which is the 'c' value in the pythagorean theorem.
	float angle;

	plyr->setAntiGravity(false); // the player is now affected by gravity. If the player is on a tile, gravity is turned off.
	plyr->cancelUp = false;
	plyr->cancelDown = false;
	plyr->cancelLeft = false;
	plyr->cancelRight = false;
	


	for (int i = 0; i < sceneArea->getAreaTiles()->size(); i++)
	{
		if (entity::Entity::collision(plyr, sceneArea->getAreaTiles()->at(i))) // if collision has happened, the program doesn't continue to check.
		{
			tile = sceneArea->getAreaTiles()->at(i); // saves the tile the player has collided with.
			
			// gets what primitives collided with the player.
			colPrim1 = plyr->collidedPrimitive;
			colPrim2 = tile->collidedPrimitive;

			distVec = plyr->getPosition() - tile->getPosition(); // calculates the distance along the x and y between the player and the tile.

			dist = sqrt(pow(distVec.x, 2) + pow(distVec.y, 2)); // gets the distance between the player and the tile, usin the pythagoren theorem.

			// gets the minimum distance the two items can be apart without being within one another.
			// both of them are squares.
			if (colPrim1->getId() == 1 && colPrim2->getId() == 1)
			{
				minDistVec.x = ((OOP::PrimitiveSquare *) colPrim1)->m_WIDTH + ((OOP::PrimitiveSquare *) colPrim2)->m_WIDTH;
				minDistVec.y = ((OOP::PrimitiveSquare *) colPrim2)->m_HEIGHT + ((OOP::PrimitiveSquare *) colPrim2)->m_HEIGHT;
			
				// distVec = plyr->getPosition() - Vec2(0.0F, ((OOP::PrimitiveSquare *) colPrim2)->m_HEIGHT / 2) - tile->getPosition();
			}

			// angle = asinf(distVec.y / dist);
			angle = atanf(distVec.y / distVec.x); // gets the angle between the the player and the tile using TOA (opposite/adjacent) 

			// std::cout << umath::radiansToDegrees(angle) << std::endl;

			// if the abs angle is less than 45.0F, then the player is next to the tile.
			if (abs(umath::radiansToDegrees(angle)) < 45.0F)
			{
				if (distVec.x <= 0.0F)
				{
					plyr->cancelRight = true;
					// plyr->setPositionX(tile->getPositionX() - minDistVec.x / 2);
					// plyr->setPositionX(plyr->getPositionX() - 1.0); // this will move the player out of the wall. The player's jump wouldn't work properly 
				}
				else if (distVec.x > 0.0F)
				{
					plyr->cancelLeft = true;
					// plyr->setPositionX(tile->getPositionX() + minDistVec.y / 2);
					// plyr->setPositionX(plyr->getPositionX() + 1.0);
				}
				plyr->zeroVelocityX();

			}
			// if the player is at an angle greater than 45.0F, the player is on top or below the platform.
			else if (abs(umath::radiansToDegrees(angle)) >= 45.0F)
			{
				if (distVec.y > 0.0F)
				{
					plyr->cancelDown = true;
					plyr->setAntiGravity(true);
					// plyr->setPositionY(plyr->getPositionY() + 1.0);
				}
				else if (distVec.y <= 0.0F)
				{
					plyr->cancelUp = true;
					plyr->setAntiGravity(false);
					// plyr->setPositionY(plyr->getPositionY() - 1.0);
				}

				plyr->zeroVelocityY();
			}

			colPrim1 = nullptr;
			colPrim2 = nullptr;
			plyr->collidedPrimitive = nullptr;
			tile->collidedPrimitive = nullptr;
			tile = nullptr;
		
		}
	}
}

// calculates player collision with enemies
void MSQ_GameplayScene::playerEnemyCollisions()
{
	OOP::Primitive * colPrim1; // the primitive from the player that encountered a collision
	OOP::Primitive * colPrim2; // the primitive from the other entity that encounted a collision

	// entity::Enemy * enemy; // saves a pointer to the 
	for each(entity::Enemy * enemy in *sceneArea->getAreaEnemies())
	{
		if (entity::Entity::collision(plyr, enemy)) // checks for collision
		{
			// gets the primitives that collided with one another.
			// colPrim1 = plyr->collidedPrimitive;
			// colPrim2 = enemy->collidedPrimitive;

			
			plyr->setHealth(plyr->getHealth() - 1); // replace with proper calculation.
			hpBar[1]->setTextureRect(Rect(0.0F, hpBarRect.getMaxY(), hpBarRect.getMaxX() * (plyr->getHealth() / plyr->getMaxHealth()), hpBarRect.getMaxY()));
			
			// hpBar[1]->setTextureRect(Rect(0.0F, 0.0F, hpBar[1]->getTexture.size.width * (plyr->getHealth() / plyr->getMaxHealth()), hpBar[1]->getTextureRect().size.height));
			// hpBar[1]->setTextureRect(Rect(0.0F, 0.0F, hpBar[1]->getTexture()->getContentSize().width * (plyr->getHealth() / plyr->getMaxHealth()), hpBar[1]->getTexture()->getContentSize().height));

			break;

		}
	}
}

//// THESE ARE UNUSED FUNCTIONS THAT SHOULD BE REMOVED LATER. IGNORE FROM THIS LINE... ///
// called to find the tile the player is colliding with, and handle what happens, based on the position(s).
// this is used for physics bodies, which have not been turned on, and likely won't be used.
void MSQ_GameplayScene::playerTileCollision(Vec2 tilePos)
{
	std::cout << "collision detected" << std::endl;
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
// this is used for physics bodies, which have not been turned on, and likely won't be used.
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
// this is used for physics bodies, which have not been turned on, and likely won't be used.
void MSQ_GameplayScene::playerItemCollision(Vec2 itemPos)
{
	// TODO: add an item vector and get the item
}

// called to find what tile the enemy is colliding with, based on the position(s).
// this is used for physics bodies, which have not been turned on, and likely won't be used.
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
// this is used for physics bodies, which have not been turned on, and likely won't be used.
void MSQ_GameplayScene::enemyWeaponCollision(Vec2 enemyPos, Vec2 weaponPos)
{
	// TODO: check enemy collison with player weapons
}
//// TO THIS LINE ///


// update loop
void MSQ_GameplayScene::update(float deltaTime)
{
	// this->getDefaultCamera()->setPosition(plyr->getPosition()); // sets the position of the camera so that it follows hte player
	// sceneArea->setAllLayerPositions(this->getDefaultCamera()->getPosition()); // makes the backgrounds be directly behind the player. This needs to be changed later so that it scrolls.

	// These movement parameters will need to be changed later.
	// if the cancels are true, then the player can't move that given direction.
	if (moveUp && !plyr->cancelUp)
	{
		plyr->addMoveForceY();
	}
	else if (moveDown && !plyr->cancelDown) // this should be disabled later
	{
		plyr->addForce(0.0F, plyr->getMoveForceY() * -1);
	}

	if (moveLeft && !plyr->cancelLeft)
	{
		plyr->addForce(plyr->getMoveForceX() * -1, 0.0F);
	}
	else if (moveRight && !plyr->cancelRight)
	{
		plyr->addForce(plyr->getMoveForceX(), 0.0F);
	}

	if (jump)
	{
		plyr->addJumpForce();
		jump = false;
	}

	// std::cout << DrawNode::create()->getPosition().x << std::endl;
	// updates the player
	plyr->update(deltaTime);
	
	// updates the area the player is currently in. This update also updates the scene tiles, and enemies.
	sceneArea->update(deltaTime);

	collisions();
}






