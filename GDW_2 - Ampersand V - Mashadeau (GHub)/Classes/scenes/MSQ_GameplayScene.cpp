#include "scenes/MSQ_GameplayScene.h"

#include <iostream>

// initalizing static variables
std::string MSQ_GameplayScene::areaName = "AIN_X00"; // debug area
int MSQ_GameplayScene::spawnPoint = 0; // spawn point 0

bool MSQ_GameplayScene::debug = true;
bool MSQ_GameplayScene::enable_hud = true; // enables hud view

std::vector<std::string> MSQ_GameplayScene::areasVisited;

// constructor; initalizes the mouse listener
MSQ_GameplayScene::MSQ_GameplayScene() : mouse(OOP::MouseListener(this)), keyboard(OOP::KeyboardListener(this)) {}

void MSQ_GameplayScene::preloadAudio() { //This thing is called to preload all the audio needed
	//Music
	
	//Effects
	AudioLibrary::MSQ_sword.preload();
}

Scene * MSQ_GameplayScene::createScene()
{
	//Preloads the audio
	preloadAudio();

	// 'scene' is an autorelease object
	Scene * scene = Scene::create(); // created without physics since we use our own.
	GameplayScene * layer = MSQ_GameplayScene::create();

	scene->addChild(layer);
	// Vec2 winSize = Director::getInstance()->getWinSizeInPixels();
	return scene;
}

// called when scene is entered.
void MSQ_GameplayScene::onEnter() { Scene::onEnter(); }

// called when scene is exited.
void MSQ_GameplayScene::onExit() { Scene::onExit(); }

bool MSQ_GameplayScene::init()
{
	// Ensures the parent init function was called first. If it wasn't, this one is exited.
	if (!Scene::init())
		return false;

	director = Director::getInstance();

	// Initialize the event handlers
	initListeners();

	//Init the Sprites
	initSprites();

	// Initialize the pause menu
	// initPauseMenu();

	// Allows for the update() function to be called by cocos
	this->scheduleUpdate();

	// Let cocos know that the init function was successful
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
	//mouse.getListener()->onMouseDown = CC_CALLBACK_2(MSQ_GameplayScene::onMousePressed, this);
	//mouse.getListener()->onMouseUp = CC_CALLBACK_2(MSQ_GameplayScene::onMouseReleased, this);
	mouse.getListener()->setEnabled(ENABLE_MOUSE); // sets whether the mouse is enabled or not.

	keyboard.setLabelVisible(false);
	// we shouldn't need to set these here, but we do. We'll fix it if we have time.
	keyboard.getListener()->onKeyPressed = CC_CALLBACK_2(MSQ_GameplayScene::onKeyPressed, this);
	keyboard.getListener()->onKeyReleased = CC_CALLBACK_2(MSQ_GameplayScene::onKeyReleased, this);
	keyboard.getListener()->setEnabled(ENABLE_KEYBOARD); // enables (or disables) keyboard
}

// initalizes all sprites
void MSQ_GameplayScene::initSprites() 
{
	bool revisit = false; // becomes 'true' if the player has visited this area before.

	// creating the scene
	for (std::string str : areasVisited)
		if (str == areaName) // if the area has been visited before, then it's a revisit.
			revisit = true;
		
	if (revisit == false) // 'remembers' the area now that the player has visited it.
		areasVisited.push_back(areaName);


	sceneArea = world::World::getArea(areaName); // makes the area. Remember, all the anchour points are the middle of the sprite layers (0.5, 0.5).
	sceneArea->setAllLayerPositions(Vec2(director->getWinSizeInPixels().width / 2, director->getWinSizeInPixels().height / 2)); // makes all the layers be at the middle of the screen.

	this->addChild(sceneArea->getAsSingleNode()); // gets the scene graphic elements (hitboxes not withstanding) as a single node.

	sceneTiles = sceneArea->getAreaTiles(); // saves a pointer to the scene tiles
	sceneEnemies = sceneArea->getAreaEnemies(); // saves a pointer to the scene enmies
	
	// creating the player; the default values handle the creation process.
	plyr = new entity::Player(); // creates the player
	plyr->setPosition(sceneArea->getSpawn(spawnPoint)); // sets the player using spawn point 0.
	plyr->setAntiGravity(debug);
	this->addChild(plyr->getSprite());

	// creating the hud
	hud = DrawNode::create(); // creating the hud
	
	// initalizes the HP bar
	hpBarRect = Rect(0.0F, 0.0F, 465.0F, 67.0F); // the size of an individual space
	hpBarPos = Vec2(director->getWinSizeInPixels().width * 0.135F, director->getWinSizeInPixels().height * 0.96F); // setting the hp bar's position.

	// [0] = front, [1] = middle (the part that shows the actual HP), [2] = back
	for (int i = 0; i < BAR_LEN; i++)
	{
		hpBar[i] = Sprite::create("images/HP_BAR_B.png"); // creates the sprite.
		hpBar[i]->setTextureRect(Rect(0.0F, 0.0F + hpBarRect.getMaxY() * i, hpBarRect.getMaxX(), hpBarRect.getMaxY())); // sets what section of the image to use.

		hpBar[i]->setPosition(hpBarPos); // moves the bar to the proper place.
		hpBar[i]->setLocalZOrder(3.0 - i); // sets the local z-order.
		hpBar[i]->setGlobalZOrder(10.0F); // sets the global z-order.

		hud->addChild(hpBar[i]); // adds to the hud.
	}

	hpBarOffset = hpBarPos - getDefaultCamera()->getPosition(); // gets the diffrence between the camera's position and hp bar's location.

	// initializes the MP bar
	mpBarRect = Rect(0.0F, 0.0F, 465.0F, 67.0F);
	mpBarPos = Vec2(director->getWinSizeInPixels().width * 0.135F, director->getWinSizeInPixels().height * 0.89F);

	// [0] = front, [1] = middle (the part that shows the actual MP), [2] = back
	for (int i = 0; i < BAR_LEN; i++)
	{
		mpBar[i] = Sprite::create("images/MP_BAR_A.png"); // creates the sprite.
		mpBar[i]->setTextureRect(Rect(0.0F, 0.0F + mpBarRect.getMaxY() * i, mpBarRect.getMaxX(), mpBarRect.getMaxY())); // sets what section of the image to use.

		mpBar[i]->setPosition(mpBarPos); // moves the bar to the proper place.
		mpBar[i]->setLocalZOrder(3.0 - i); // sets the local z-order.
		mpBar[i]->setGlobalZOrder(10.0F); // sets the global z-order.

		hud->addChild(mpBar[i]); // adds to the hud.
	}

	mpBarOffset = mpBarPos - getDefaultCamera()->getPosition(); // gets the different between the camera's position and the mp bar's location.

	this->addChild(hud);
	hud->setVisible(enable_hud); // Hud visibility.

	// creating the grid
	grid = new OOP::PrimitiveGrid(cocos2d::Vec2(0.0F, 0.0F), cocos2d::Vec2(director->getWinSizeInPixels().width, director->getWinSizeInPixels().height), 128.0F, Color4F::WHITE);
	// grid->getPrimitive()->setGlobalZOrder(10.3F); // makes the grid be above everything else.
	grid->getPrimitive()->setVisible(true); // makes the grid visible (or not visible)
	this->addChild(grid->getPrimitive()); // adds grid to drawList
	gridOffset = grid->getPosition() - getDefaultCamera()->getPosition();


	// setting the camera if it's activated.
	if (ENABLE_CAMERA)
	{
		this->getDefaultCamera()->setAnchorPoint(Vec2(0.5F, 0.5F)); // setting the camera's anchour point
		
		this->getDefaultCamera()->setPosition(plyr->getPosition()); // sets the location of the camera
		
		hpBarPos = getDefaultCamera()->getPosition() + hpBarOffset; // moves the hp bar
		for (int i = 0; i < BAR_LEN; i++) // moves all of the hp bars accordingly.
			hpBar[i]->setPosition(hpBarPos);

		grid->setPosition(gridOffset + getDefaultCamera()->getPosition()); // moves the grid.
	}

	debugMode(); // called to turn on (or off) debug mode.
}

// initializes pause menu; currently does nothing.
void MSQ_GameplayScene::initPauseMenu() {}


//// CALLBACKS /////////////////////////////////////////////////////////////
void MSQ_GameplayScene::onMousePressed(EventMouse::MouseButton mouseButt, Event * event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event); //casting as a mouse event
	
	switch (mouseButt) {
	case EventMouse::MouseButton::BUTTON_LEFT:
		//attack = true(make this the same code as found in F)
		break;
	case EventMouse::MouseButton::BUTTON_RIGHT:
		//if needed
		break;
	}
}

void MSQ_GameplayScene::onMouseReleased(EventMouse::MouseButton mouseButt, Event * event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event); //casting as a mouse event

	switch (mouseButt) {
	case EventMouse::MouseButton::BUTTON_LEFT:
		//attack = false(make this the same code as found in F)
		break;
	case EventMouse::MouseButton::BUTTON_RIGHT:
		//if needed
		break;
	}
}
void MSQ_GameplayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		if (debug)
			moveUp = true; // tells the program to move the player up.

		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		if (debug)
			moveDown = true; // tells the player to go down.
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveLeft = true;
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		moveUp = true;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		moveDown = true;
		break;

	case EventKeyboard::KeyCode::KEY_A:
		moveLeft = true;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		moveRight = true;
		break;

	case EventKeyboard::KeyCode::KEY_F:
		pAction = 6;
		plyrAction = true;
		AudioLibrary::MSQ_sword.play();
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
	case EventKeyboard::KeyCode::KEY_X: // turns debug mode on/off.
		debug = !debug;
		break;

	case EventKeyboard::KeyCode::KEY_H: // toggles on/off hud.
		enable_hud = !enable_hud;
		break;

	case EventKeyboard::KeyCode::KEY_UP_ARROW:
		moveUp = false;

		if(!debug) // if debug is off, then the jump is turned on upon 'UP' being let go.
			jump = true;

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
	case EventKeyboard::KeyCode::KEY_W:
		moveUp = false;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		moveDown = false;
		break;

	case EventKeyboard::KeyCode::KEY_A:
		moveLeft = false;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		moveRight = false;
		break;
	case EventKeyboard::KeyCode::KEY_F: // moved to key down.
		//attack
		// pAction = 6;
		// plyrAction = true;
		// AudioLibrary::MSQ_sword.play();

		break;
	case EventKeyboard::KeyCode::KEY_1:
		//item 1
		break;
	case EventKeyboard::KeyCode::KEY_2:
		//item 2
		break;
	case EventKeyboard::KeyCode::KEY_3:
		//item 3
		break;
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		//menu
		break;
	}
}

// called to turn on/off debug mode.
void MSQ_GameplayScene::debugMode()
{
	static bool d_mode = false;

	if (d_mode == debug)
		return;

	d_mode = debug;
	
	plyr->zeroVelocity(); // zeroes out the player's velocity to remove any velocity they currently have.
	plyr->setAntiGravity(debug); // disables or enables the player's gravity
	
}


// switches the area based on the passed file name.
// the last digit is needed to know what spawn point to use. It must be greater than or equal to 0, and not exceed 4 (it can be 4 though).
void MSQ_GameplayScene::switchArea(std::string & fileName)
{

	std::string spawn = ""; // the spawn point of the player in the new area
	Scene * newScene = nullptr; // a new gameplay scene that will load up a new area.
	TransitionerScene * pathScene = nullptr; // the scene transferred to for transitions.

	if (switchingScenes)
		return;

	try // handles invalid uses of this function.
	{
		if (switchingScenes)
			throw "Scene switch is progress. Function not available.\n";

		if (fileName.length() != 9)
			throw "The string was not the appropriate length, or did not contain the right characters.\n";

		spawn = fileName.substr(fileName.length() - 1, 1); // gets the ending number.
		fileName.erase(fileName.length() - 2, 2); // erases the spawn point in the file name, since it's already in the string.

		if (!ustd::isInt(spawn)) // if spawn point isn't an integer.
			throw "Inadequate character used for spawn point. Requires integer from 0 to 4\n";
		
		if (std::stoi(spawn) < 0 || std::stoi(spawn) > 4) // if the spawn point is out of range.
			throw "Spawn point does not exist\n";

		if (world::World::getArea(fileName) == nullptr) // if the area doesn't exist.
			throw "This area does not exist.\n";
	}
	catch (const char * ex) // catches the thrown message exception.
	{
		std::cout << ex;
		return;
	}
	catch (...) // this shouldn't be reached, but exists just in case.
	{
		std::cout << "Scene switch failed.\n";
		return;
	}

	areaName = fileName; // saves the new area so that it's set upon initalization of the new game object.
	spawnPoint = std::stoi(spawn); // saves the spawn point of the player for when they get into the new area.

	newScene = GameplayScene::createScene(); // creates the gameplay scene.
	
	// if a scene transition is used, the trnansition must finish before the program allows user input, BUT if this happens then the game will start processing things before the player can actually do anything.
	// director->replaceScene(TransitionFadeBL::create(1.0F, newScene)); // replaces the scene for the director, and does a transition.
	director->replaceScene(newScene); // replaces the scene without a transition.

	switchingScenes = true; // becomes 'true' so that scene switches don't overlay one another.
}

// exits the game.
void MSQ_GameplayScene::exitGame()
{
	areasVisited.clear(); // removes the 'memory' of visited areas.
	// TODO: switch back to menu.
}

// runs collision tests.
void MSQ_GameplayScene::collisions()
{	
	// std::cout << "PX: " << plyr->getAABBs().at(0)->getPosition().x << ", PY: " << plyr->getAABBs().at(0)->getPosition().y << std::endl;
	playerTileCollisions(); // called for player-tile collisions.
	enemyTileCollisions(); // collision between the enemies and the tiles.
	
	playerEnemyCollisions(); // called for player collisions with enemies
	weaponEnemyCollisions();
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
	float theta; // the angle between the player and the tile

	float compAngle = 60.0F; // the angle used to check the player's position relative to the tile, in degrees.

	if(debug == false)
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

			if (!switchingScenes && tile->getTIN() >= 0 && tile->getTIN() <= 4) // if it's a scene exit, then no ohter checks need to be done.
			{
				// nextArea = sceneArea->getExit(tile->getTIN());
				// swapScene = true;
				switchArea(sceneArea->getExit(tile->getTIN())); // gets the tile identification number, and gets the exit attached to it.
				// delete plyr;
				return;
			}


			// gets what primitives collided with the player.
			colPrim1 = plyr->collidedPrimitive;
			colPrim2 = tile->collidedPrimitive;

			distVec = plyr->getPosition() - tile->getPosition(); // calculates the distance along the x and y between the player and the tile.
			// distVec = Vec2(abs(distVec.x), abs(distVec.y));

			dist = sqrt(pow(distVec.x, 2) + pow(distVec.y, 2)); // gets the distance between the player and the tile, usin the pythagoren theorem.

			// gets the minimum distance the two items can be apart without being within one another.
			// both of them are squares.
			if (colPrim1->getId() == 1 && colPrim2->getId() == 1)
			{
				minDistVec.x = ((OOP::PrimitiveSquare *) colPrim1)->m_WIDTH / 2 + ((OOP::PrimitiveSquare *) colPrim2)->m_WIDTH / 2;
				minDistVec.y = ((OOP::PrimitiveSquare *) colPrim1)->m_HEIGHT / 2 + ((OOP::PrimitiveSquare *) colPrim2)->m_HEIGHT / 2;

				// distVec = plyr->getPosition() - Vec2(0.0F, ((OOP::PrimitiveSquare *) colPrim2)->m_HEIGHT / 2) - tile->getPosition();
			}

			// angle = asinf(distVec.y / dist);
			theta = atanf(distVec.y / distVec.x); // gets the angle between the the player and the tile using TOA (opposite/adjacent) 

			/*
			if (distVec.x < minDistVec.x && distVec.y < minDistVec.x)
			{
				plyr->setPositionX((plyr->getPositionX() < tile->getPositionX()) ? tile->getPositionX() - minDistVec.x : tile->getPositionX() + minDistVec.x);

				// plyr->setPosition(plyr->getPosition() + Vec2(minDistVec.x * umath::rotate(minDistVec.getNormalized(), angle).x, minDistVec.y * umath::rotate(minDistVec.getNormalized(), angle).y));

				// (plyr->getPositionX() < tile->getPositionX()) ? plyr->setPositionX(tile->getPositionX() - minDistVec.x) : plyr->setPositionX(tile->getPositionX() + minDistVec.x);

				// (plyr->getPositionY() < tile->getPositionY()) ? plyr->setPositionY(tile->getPositionY() - minDistVec.y) : plyr->setPositionY(tile->getPositionY() + minDistVec.y);

			}
			else if (distVec.y < minDistVec.y)
			{
				plyr->setPositionY((plyr->getPositionY() < tile->getPositionY()) ? tile->getPositionY() - minDistVec.y : tile->getPositionY() + minDistVec.y);
				// plyr->setPositionY(tile->getPositionY() - minDistVec.y);
			}
			*/

			// std::cout << umath::radiansToDegrees(angle) << std::endl;

			// if the abs angle is less than 45.0F, then the player is next to the tile.
			if (abs(umath::radiansToDegrees(theta)) < compAngle)
			{
				if (distVec.x <= 0.0F)
				{
					plyr->cancelRight = true;
					plyr->setPositionX(tile->getPositionX() - abs(minDistVec.x));
					// plyr->setPositionX(plyr->getPositionX() - 1.0); // this will move the player out of the wall. The player's jump wouldn't work properly 
				}
				else if (distVec.x > 0.0F)
				{
					plyr->cancelLeft = true;
					plyr->setPositionX(tile->getPositionX() + abs(minDistVec.x));
				}
				plyr->zeroVelocityX();

			}
			// if the player is at an angle greater than 45.0F, the player is on top or below the platform.
			else if (abs(umath::radiansToDegrees(theta)) >= compAngle)
			{
				if (distVec.y <= 0.0F)
				{
					
					plyr->cancelUp = true;
					plyr->setPositionY(tile->getPositionY() - abs(minDistVec.y));

					if(debug == false)
						plyr->setAntiGravity(false);
				
				}
				else if (distVec.y > 0.0F)
				{
					plyr->cancelDown = true;
					plyr->setPositionY(tile->getPositionY() + abs(minDistVec.y));

					if(debug == false)
						plyr->setAntiGravity(true);
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

// collisions between enemies and tiles
void MSQ_GameplayScene::enemyTileCollisions()
{
}

// calculates player collision with enemies
void MSQ_GameplayScene::playerEnemyCollisions()
{
	float offset = 0.0F;

	if (plyr->getInvincible()) // if the player currently has invincibility frames, then the enemy collisions are ignored.
		return;

	// entity::Enemy * enemy; // saves a pointer to the 
	for each(entity::Enemy * enemy in *sceneArea->getAreaEnemies())
	{
		if (entity::Entity::collision(plyr, enemy)) // checks for collision
		{
			// gets the primitives that collided with one another.
			// colPrim1 = plyr->collidedPrimitive;
			// colPrim2 = enemy->collidedPrimitive;

			
			// plyr->setHealth(plyr->getHealth() - enemy->getAttackPower());
			plyr->setHealth(plyr->getHealth() - magic::MagicType::damage(enemy->getMagicType(), plyr->getMagicType(), enemy->getAttackPower())); // replace with proper calculation.
			plyr->gotHit();
			
			offset = hpBarRect.getMaxX() * (plyr->getHealth() / plyr->getMaxHealth()); // calculates the offset needed to reposition the newly sized hp bar.

			hpBar[1]->setTextureRect(Rect(0.0F, hpBarRect.getMaxY(), hpBarRect.getMaxX() * (plyr->getHealth() / plyr->getMaxHealth()), hpBarRect.getMaxY()));
			
			// This takes the size of the hpBar at full size (hpBarRect.getMaxX()), halves it.
			// It then subtracts the position of hpBar[0] (i.e. the frame doesn't move) by it, and then adds the new size of the health bar divided by '2' to it.
			// in other words it basically just aligns itself with the left edge of the frame and then moves it over by half of the health bar's current length, since the position is based on its centre.
			// this is all so the hp bar is where it should be.
			hpBar[1]->setPositionX(hpBar[0]->getPositionX() - hpBarRect.getMaxX() / 2 + offset / 2);

			break;

		}
	}
}

// collision between the player's current weapon and the enemy.
void MSQ_GameplayScene::weaponEnemyCollisions()
{
	entity::Weapon * weapon = plyr->getCurrentWeapon();
	magic::Magic weaponMagic; // gets the magic type of the weapon.
	float offset = 0.0F; // saves the offset needed for the mpBar

	if (weapon == nullptr)
		return;

	// if the player has no magic power, then the weapon's type is switched to 'null'.
	weaponMagic = (plyr->getMagicPower() > 0.0F) ? weapon->getMagicType() : magic::Magic(magic::null);

	for(int i = 0; i < sceneEnemies->size(); i++)
	{
		if (sceneEnemies->at(i) == nullptr)
			continue;

		entity::Enemy * emy = sceneEnemies->at(i);

		// so essenially, a problem with the weapon collisions is that they would be based off the weapon's sprite instead of the player's sprite under a normal function call.
		// as such, a collision body needs to be paired with the player that only contains the weapons at the appropriate spot, hence the function call.
		if (entity::Entity::collision(plyr, weapon->getOffsetCollisionBodies(weapon->getOwner()->getSprite(), weapon->getCollisionBodies()), sceneEnemies->at(i), sceneEnemies->at(i)->getOffsetCollisionBodies())) // checks for collision.
		{
			// if the player has no magic power, then the weapon's attack power is cut in half, and has a type value of 'null'.
			sceneEnemies->at(i)->setHealth(sceneEnemies->at(i)->getHealth() - 
				magic::Magic::damage(weaponMagic, emy->getMagicType(), weapon->getDamage() / (plyr->getMagicPower() > 0.0F) ? 1 : 2));

			sceneEnemies->at(i)->gotHit(); // the enemy has been hit

			plyr->addMagicPower(-1 * (weapon->getMagicUsage())); // reduces the player's magic.
			offset = mpBarRect.getMaxX() * (plyr->getMagicPower() / plyr->getMagicPowerMax()); // calculates the offset needed to reposition the newly sized mp bar.

			mpBar[1]->setTextureRect(Rect(0.0F, mpBarRect.getMaxY(), mpBarRect.getMaxX() * (plyr->getMagicPower() / plyr->getMagicPowerMax()), mpBarRect.getMaxY()));

			// This takes the size of the hpBar at full size (hpBarRect.getMaxX()), halves it.
			// It then subtracts the position of hpBar[0] (i.e. the frame doesn't move) by it, and then adds the new size of the health bar divided by '2' to it.
			// in other words it basically just aligns itself with the left edge of the frame and then moves it over by half of the health bar's current length, since the position is based on its centre.
			// this is all so the hp bar is where it should be.
			mpBar[1]->setPositionX(mpBar[0]->getPositionX() - mpBarRect.getMaxX() / 2 + offset / 2);

			break;
		}
	}

}


// update loop
void MSQ_GameplayScene::update(float deltaTime)
{
	float d_movespeed = 300.0F; // the movement speed of the player (when debug is on).

	if (switchingScenes) // updates are no longer run if the scene is being switched.
		return;

	debugMode(); // called to change the settings if debug mode has been turned on/off.

	if (ENABLE_CAMERA) // updates the camera if it's active.
	{
		this->getDefaultCamera()->setPosition(plyr->getPosition()); // sets the position of the camera so that it follows hte player
		
		sceneArea->setAllLayerPositions(this->getDefaultCamera()->getPosition()); // makes the backgrounds be directly behind the player. This needs to be changed later so that it scrolls.
		
		hpBarPos = getDefaultCamera()->getPosition() + hpBarOffset; // moves the hp bar
		for (int i = 0; i < BAR_LEN; i++) // moves all of the hp bars accordingly.
			hpBar[i]->setPosition(hpBarPos);

		mpBarPos = getDefaultCamera()->getPosition() + mpBarOffset; // moves the mp bar
		for (int i = 0; i < BAR_LEN; i++) // moves all of the mp bars accordingly.
			mpBar[i]->setPosition(hpBarPos);

		grid->setPosition(gridOffset + getDefaultCamera()->getPosition()); // moves the grid so that it
	}

	if (enable_hud != hud->isVisible()) // if the hud's visibility is wrong, it's set accordingly.
		hud->setVisible(enable_hud);

	// These movement parameters will need to be changed later.
	// if the cancels are true, then the player can't move that given direction.

	if (moveUp && !plyr->cancelUp) // moves the player up.
	{
		plyr->setPositionY(plyr->getPositionY() + d_movespeed * deltaTime);
	}
	else if (moveDown && !plyr->cancelDown) // moves the player down.
	{
		plyr->setPositionY(plyr->getPositionY() - d_movespeed * deltaTime);
	}

	if (moveLeft && !plyr->cancelLeft) // moving left
	{
		if (plyr->getFlippedSpriteX() == false) // flips the sprite so that it's facing left
			plyr->setFlippedSpriteX(true);

		if (debug) // if debug is on, then the player moves at a fixed speed.
			plyr->setPositionX(plyr->getPositionX() - d_movespeed * deltaTime);
		else
			plyr->addForce(plyr->getMoveForceX() * -1, 0.0F);
	}
	else if (moveRight && !plyr->cancelRight) // moving right
	{
		if (plyr->getFlippedSpriteX() == true) // flips the sprite so that it's facing right (i.e. the default)
			plyr->setFlippedSpriteX(false);

		if(debug) // if debug is on, then the player moves at a fixed speed.
			plyr->setPositionX(plyr->getPositionX() + d_movespeed * deltaTime);
		else // if debug is off, the player is given force to move.
			plyr->addForce(plyr->getMoveForceX(), 0.0F);

	}
	
	if (jump)
	{
		plyr->zeroVelocityY();
		plyr->setPositionY(plyr->getPositionY());
		plyr->addJumpForce();
		jump = false;
	}
	if (plyrAction) // animation should be played
	{
		switch (pAction)
		{
		case 6: // attack 1 animation.
			plyr->runAction(pAction);
			pAction = 0;
		}

		plyrAction = false;
	}
	

	// std::cout << DrawNode::create()->getPosition().x << std::endl;
	// updates the player
	plyr->update(deltaTime);
	
	// updates the area the player is currently in. This update also updates the scene tiles, and enemies.
	sceneArea->update(deltaTime);

	collisions();

}
