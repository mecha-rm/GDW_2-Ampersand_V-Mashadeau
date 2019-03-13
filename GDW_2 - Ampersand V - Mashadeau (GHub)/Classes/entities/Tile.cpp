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
	
	//sprite->getPhysicsBody()->createBox(Size(128.0F, 128.0F));
	
	sprite->setGlobalZOrder(1.0F); // all tiles should be on the same global z-order.
	sprite->setTag(tile);
	sprite->getPhysicsBody()->setTag(tile); // This is currently not being used.
	/*
	sprite->getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(128.0F, 128.0F)));
	sprite->getPhysicsBody()->setContactTestBitmask(0xFFFFFFFF);
	*/

	tempNode->setGlobalZOrder(3.0F);
	setAntiGravity(true); // tiles shouldn't be moved by gravity, so their anti gravity gets turned on by default.

	this->TIN = TIN; // setting the TIN; this will be changed later if a platform does not exist of this number.
	this->LETTER = letter; // setting the letter identifier; this will be changed later if it is invalid.

	switch (TIN)
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

		switch (this->LETTER) // places the hitbox in a different position based on where the tile exit hitbox i.s/
		{
		case 'a': // exit above
			collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(0.0F, 127.0F), Vec2(128.0f, 128.0F), CLR_DEF));
			break;

		case 'b': // exit below
			collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(0.0F, 1.0F), Vec2(128.0f, 0.0F), CLR_DEF));
			break;
		case 'c': // exit left
			collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(0.0F, 0.0F), Vec2(1.0F, 128.0F)));
			break;

		case 'd': // exit right
			collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(127.0F, 0.0F), Vec2(128.0f, 128.0F), CLR_DEF));
			break;

		case 'e': // exit centre
		default:
			collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(64.0F, 64.0F), 128.0F, CLR_DEF));
			break;
		}

		collisionShapes.at(0)->getPrimitive()->setGlobalZOrder(19.9F);
		collisionShapes.at(0)->setVisible(true);

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
		setTexture("images/tiles/TIN_010.png"); // sets the image for the sprite
		frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F);
		switch (letter)
		{
		case 'a': // 'a' is also the default type.
		default:
			this->LETTER = 'a'; // since 'a' is also the default, this is set to 'a', just to be sure.
			setName("Stone Block");
			setDescription("A block made of stone.");
			
			setTextureRect(frameSize);

			collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(sprite->getTextureRect().getMidX(), sprite->getTextureRect().getMidY()), 128.0F, CLR_DEF));
			break;
		}

		// sprite->getPhysicsBody()->createBox(Size(128.0F, 128.0F));
		// sprite->getPhysicsBody()->getShapes();
		break;

	case 11: // semi-solid stone platform

		// setTexture()
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

		collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(frameSize.getMidX(), frameSize.getMidY()), 128.0F, CLR_DEF));
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

		collisionShapes.push_back(new OOP::PrimitiveSquare(Vec2(64.0F, 64.0F), 128.0F));
		break;
	}

	for (OOP::Primitive * colShape : collisionShapes) // adds all of the collision shapes to the sprite.
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

// the update loop for for the tiles
void entity::Tile::update(float deltaTime)
{
	Entity::update(deltaTime); // calls the 'Entity' update loop
}
