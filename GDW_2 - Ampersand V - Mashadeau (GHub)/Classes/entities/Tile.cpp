#include "entities/Tile.h"

// Constructor for tile. All that's needed is the type of the tile, the letter, and how many copies the user wants to make in a given direction.
entity::Tile::Tile(unsigned int TIN, char letter, const unsigned int COPY_UP, const unsigned int COPY_DOWN, const unsigned int COPY_LEFT, const unsigned int COPY_RIGHT, const bool OFFSET_BY_SPRITE_SIZE)
	: Entity(), COPY_UP(COPY_UP), COPY_DOWN(COPY_DOWN), COPY_LEFT(COPY_LEFT), COPY_RIGHT(COPY_RIGHT), OFFSET_BY_SPRITE_SIZE(OFFSET_BY_SPRITE_SIZE)
{
	createTile(TIN, letter);
}


entity::Tile::~Tile() {}

// creates the tile based on a provided type and letter.
void entity::Tile::createTile(unsigned int TIN, char letter)
{
	DrawNode * tempNode = DrawNode::create(); // used to create an enemy square if no tile of the provided TIN exists.
	
	sprite->setGlobalZOrder(1.0F); // all tiles should be on the same global z-order.
	sprite->setTag(tile);

	tempNode->setGlobalZOrder(3.0F);
	setAntiGravity(true); // tiles shouldn't be moved by gravity, so their anti gravity gets turned on by default.

	this->TIN = TIN; // setting the TIN; this will be changed later if a platform does not exist of this number.
	this->LETTER = letter; // setting the letter identifier; this will be changed later if it is invalid.

	switch (this->TIN)
	{
	case 0: // exit 0
	case 1: // exit 1
	case 2: // exit 2
	case 3: // exit 3
	case 4: // exit 4
		// a basic visual is used to represent the exit. In the final game, this should be turned off.
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
		sprite->setTextureRect(frameSize); // creates a texture rect, so that the default only has one tile
		sprite->setColor(Color3B::BLUE);
		tempNode->drawRect(Vec2(sprite->getTextureRect().getMinX(), sprite->getTextureRect().getMinY()), Vec2(sprite->getTextureRect().getMaxX(), sprite->getTextureRect().getMaxY()), Color4F::GREEN);
		sprite->addChild(tempNode);

		switch (this->LETTER) // places the hitbox in a different position based on where the tile exit hitbox i.s
		{
		case 'a': // exit above
			collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(0.0F, 127.0F), Vec2(128.0f, 128.0F), CLR_DEF));
			break;

		case 'b': // exit below
			collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(0.0F, 1.0F), Vec2(128.0f, 0.0F), CLR_DEF));
			break;
		case 'c': // exit left
			collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(0.0F, 0.0F), Vec2(1.0F, 128.0F), CLR_DEF));
			break;

		case 'd': // exit right
			collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(127.0F, 0.0F), Vec2(128.0f, 128.0F), CLR_DEF));
			break;

		case 'e': // exit centre
		default:
			collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(64.0F, 64.0F), 128.0F, CLR_DEF));
			break;
		}

		collisionBodies.at(0)->getPrimitive()->setGlobalZOrder(19.9F);
		collisionBodies.at(0)->setVisible(true);

		// sprite->setVisible(false); // uncomment to hide all graphics
		break;
	case 5: // spawn 0
	case 6: // spawn 1
	case 7: // spawn 2
	case 8: // spawn 3
	case 9: // spawn 4

		frameSize = Rect(0.0F, 0.0F, 256.0F, 256.0F);
		sprite->setTextureRect(frameSize); // creates a texture rect, so that the default only has one tile
		sprite->setColor(Color3B::GREEN);
		tempNode->drawRect(Vec2(sprite->getTextureRect().getMinX(), sprite->getTextureRect().getMinY()), Vec2(sprite->getTextureRect().getMaxX(), sprite->getTextureRect().getMaxY()), Color4F::BLUE);
		sprite->addChild(tempNode);

		// spawn points don't have hitboxes, so no primitives are made.

		// sprite->setVisible(false); // uncomment to hide all graphics
		break;
	case 10: // stock block

		// this->LETTER = 'a'; // there's only one block at the moment, so it's set as type a.
		setName("Stone Block");
		setDescription("A block made of stone.");
		setTexture("images/tiles/TIN_010.png"); // sets the image for the sprite
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);

		switch (letter)
		{
		case 'a': // 'a' is also the default type.
		default:
			this->LETTER = 'a'; // since 'a' is also the default, this is set to 'a', just to be sure.

			setTextureRect(frameSize);
			collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(sprite->getTextureRect().getMidX(), sprite->getTextureRect().getMidY()), 128.0F, CLR_DEF));
			break;
		}

		break;

	case 11: // semi-solid stone platform

		// setTexture()
		break;

	case 100://sewer tiles
		setName("Sewer Tile");
		setDescription("Tile set");
		setTexture("images/tiles/TIN_100.png");
		frameSize = Rect(0.0f, 0.0f, 128.0f, 128.0f);

		switch (this->LETTER)
		{
		case 'a':
		default:
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;

		case 'b':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'c':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'd':
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'e':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'f':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'g':
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'h':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'i':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		}

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
		break;

	case 101://cult tiles
		setName("Cult Tile");
		setDescription("Tile set");
		setTexture("images/tiles/TIN_101.png");
		frameSize = Rect(0.0f, 0.0f, 128.0f, 128.0f);

		switch (this->LETTER)
		{
		case 'a':
		default:
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;

		case 'b':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'c':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'd':
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'e':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'f':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'g':
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'h':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'i':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		}

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
		break;

	case 102://cult platforms and Sewer ladder
		setName("Platforms and Ladders");
		setDescription("Tile set");
		setTexture("images/tiles/TIN_102.png");
		frameSize = Rect(0.0f, 0.0f, 128.0f, 128.0f);

		switch (this->LETTER) {
		case 'a'://platform left
		default:
			setTextureRect(Rect(frameSize.getMaxX() * 0.0f, frameSize.getMaxY() * 0.0f, frameSize.getMaxX(), frameSize.getMaxY()));

		case 'b'://platform mid
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'c'://platform right
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'd'://sewer ladder 
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;

		}
		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
		break;
	

	case 500: //air area block base
		setName("Mountain Block");
		setDescription("Tile set");
		setTexture("images/tiles/TIN_500.png");
		frameSize = Rect(0.0f, 0.0f, 128.0f, 128.0f);

		switch (this->LETTER) {
			case 'a':
			default:
				setTextureRect(Rect(frameSize.getMaxX() * 0.0f, frameSize.getMaxY() * 0.0f, frameSize.getMaxX(), frameSize.getMaxY()));
		}

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
		break;

	case 600: // stone castle block
		setName("Castle Stone Block");
		setDescription("Tile set");
		setTexture("images/tiles/TIN_600.png");
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);

		switch (this->LETTER)
		{
		case 'a':
		default:
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;

		case 'b':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'c':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 0.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'd':
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'e':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'f':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 1.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'g':
			setTextureRect(Rect(frameSize.getMaxX() * 0.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'h':
			setTextureRect(Rect(frameSize.getMaxX() * 1.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		case 'i':
			setTextureRect(Rect(frameSize.getMaxX() * 2.0F, frameSize.getMaxY() * 2.0F, frameSize.getMaxX(), frameSize.getMaxY()));
			break;
		}

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
		break;

	case 700: // magic orb

		break;

	case 701: // hp orb

		break;

	case 800: // null blade
		setTexture("images/weapons/WIN_000.png");
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
		weaponNum = 0;

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
		break;

	case 802: // eath staff blade
		setTexture("images/weapons/WIN_002.png");
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
		weaponNum = 2;

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
		break;

	default:
		this->TIN = 0; // a tile of type 0 is invalid. This number is taken up by something else, but said thing does not actually make a tile.
		this->LETTER = 'a'; // default letter of 'a'.
		setName("NON_EXISTENT_TILE");
		setDescription("Unable to find data");

		// a basic visual is used to represent the exit. In the final game, this should be turned off.
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
		sprite->setTextureRect(frameSize); // creates a texture rect, so that the default only has one tile
		sprite->setColor(Color3B::WHITE);
		tempNode->drawRect(Vec2(sprite->getTextureRect().getMinX(), sprite->getTextureRect().getMinY()), Vec2(sprite->getTextureRect().getMaxX(), sprite->getTextureRect().getMaxY()), Color4F::BLACK);
		sprite->addChild(tempNode);

		collisionBodies.push_back(new OOP::PrimitiveSquare(Vec2(64.0F, 64.0F), 128.0F));
		break;
	}

	for (OOP::Primitive * colShape : collisionBodies) // adds all of the collision shapes to the sprite.
	{
		colShape->getPrimitive()->setGlobalZOrder(10.1F);
		colShape->getPrimitive()->setVisible(shapesVisible);
		sprite->addChild(colShape->getPrimitive());
	}

}

// returns the tile identification number
const unsigned int entity::Tile::getTIN() const { return TIN; }

// the letter of the tile
const char entity::Tile::getLetter() const { return LETTER; }

// sets the position of the tile, overriding the 'setPosition' in the entity class.
void entity::Tile::setPosition(Vec2 newPos)
{
	cocos2d::Vec2 offset = newPos - getPosition(); // calculates the offset for moving the STARTING_POS and ENDING_POS
	startingPoint += offset; // proportionally moves the starting position.
	endingPoint += offset; // proportionally moves the ending position.

	Entity::setPosition(newPos); // sets the position of the vertical platform
}

// sets the position of the tile using floats.
void entity::Tile::setPosition(float posX, float posY) { setPosition(Vec2(posX, posY)); }

// sets the position on the x-axis.
void entity::Tile::setPositionX(float newPosX) { setPosition(Vec2(newPosX, getPositionY())); }

// sets the position of the tile on the y-axis
void entity::Tile::setPositionY(float newPosY) { setPosition(Vec2(getPositionX(), newPosY)); }

// gets the health of the tile.
float entity::Tile::getHealth() { return health; }

// sets the health of the tile.
void entity::Tile::setHealth(float hp) { health = (hp >= 0.0F) ? hp : 0.0F; }

// gets whether the tile can be damaged or not.
bool entity::Tile::getDamagable() { return damageable; }

// checks the effect the tile has on the player.
void entity::Tile::effect(entity::Tile * tile, entity::Player * plyr)
{
	entity::Weapon * weapon = nullptr; // the weapon that the player has given up.
	entity::Tile * tempTile = nullptr;

	switch (tile->TIN)
	{
	case 700: // magic orb
		(tile->changeMpMax) ? plyr->addMagicPowerMax(tile->mpAdd, true) : plyr->addMagicPower(tile->mpAdd);
		break;

	case 701: // health orb
		(tile->changeHpMax) ? plyr->addMaxHealth(tile->hpAdd, true) : plyr->addHealth(tile->hpAdd);
		break;

	case 800: // null blade
		weapon = plyr->giveWeapon(new entity::Weapon(tile->weaponNum, plyr));
		break;

	case 802: // provides a weapon to the player. The weapon numbers (WIN) are 800 less than the tile number they're attachted to (e.g. tile 802 has weapon 002).
		weapon = plyr->giveWeapon(new entity::Weapon(tile->weaponNum, plyr));
		break;

	}

	// if the weapon was switched out, it is then given to the tile to store it, kind of like a box.
	// if there is no weapon to put back in, then the tile gets its contents removed by setting its health to 0 so that it gets deleted.
	// (weapon == nullptr) ? tile->setHealth(0.0F) : tile = new entity::Tile(weapon->getWIN() + 800);

	if (weapon == nullptr)
	{
		tile->setHealth(0.0F);
		tempTile = tile;
	}
	else
	{
		tile->weaponNum = weapon->getWIN();
		tile->setTexture(weapon->getTextureFilePath()); // replaces the image
	}	
}

// the update loop for for the tiles
void entity::Tile::update(float deltaTime)
{
	if (moveSpeedX > 0.0F || moveSpeedY > 0.0F) // moves hte platform
	{
		Entity::setPosition(getPosition() +
			Vec2(100.0F * ((moveRight) ? 1 : -1) * moveSpeedX * deltaTime,
				 100.0F * ((moveUp) ? 1 : -1) * moveSpeedY * deltaTime));
	}

	if(rotationSpeed > 0.0F)
		sprite->setRotation(sprite->getRotation() + ((rotateClockwise) ? 1 : -1) * 10.0F * rotationSpeed); // rotates the tile.

	// if the platform has passed the ending point, then it starts moving the other way.
	if (getPositionX() >= endingPoint.x)
	{
		moveRight = false;
	}
	else if (getPositionX() <= startingPoint.x) // if the platform has returned to the starting point, it starts to move the other direction again.
	{
		moveRight = true;
	}

	if (getPositionY() >= endingPoint.y) // if the platform has surpassed its endingPoint, it will start moving down.
	{
		moveUp = false;
	}
	else if (getPositionY() <= startingPoint.y) // if the platform has gone past (or reached) its starting point, it now goes up.
	{
		moveUp = true;
	}

	Entity::update(deltaTime); // calls the 'Entity' update loop
}