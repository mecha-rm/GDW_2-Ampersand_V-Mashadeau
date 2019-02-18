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
	
	sprite->setGlobalZOrder(3.0F); // all tiles should be on the same global z-order.
	tempNode->setGlobalZOrder(3.0F);
	setAntiGravity(true); // tiles shouldn't be moved by gravity, so their anti gravity gets turned on by default.

	this->TIN = TIN; // setting the TIN; this will be changed later if a platform does not exist of this number.
	this->LETTER = letter; // setting the letter identifier; this will be changed later if it is invalid.

	switch (TIN)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:

	case 10: // stock block
		
		// this->LETTER = 'a'; // there's only one block at the moment, so it's set as type a.
		setTexture("images/tiles/TIN_010.png"); // sets the image for the sprite
		switch (letter)
		{
		case 'a': // 'a' is also the default type.
		default:
			this->LETTER = 'a'; // since 'a' is also the default, this is set to 'a', just to be sure.
			name = "Stone Block";
			description = "A block made of stone.";
			
			setTextureRect(0.0F, 0.0F, 128.0F, 128.0F);

			break;

		}
		break;

	

	case 11:


	default:
		this->TIN = 0; // a tile of type 0 is invalid. This number is taken up by something else, but said thing does not actually make a tile.
		this->LETTER = 'a'; // default letter of 'a'.
		name = "NON_EXISTENT_TILE";
		description = "Unable to find data";

		// setSprite(cocos2d::Sprite::create()); // uses TIN_010 by default. This will be covered up.
		sprite->setTextureRect(Rect(0.0F, 0.0F, 128.0F, 128.0F)); // creates a texture rect, so that the default only has one tile
		sprite->setColor(Color3B::RED);
		tempNode->drawRect(Vec2(0.0F, 0.0F), Vec2(sprite->getTextureRect().getMaxX(), sprite->getTextureRect().getMaxY()), Color4F::BLUE); // creates an outline for the rectangle, and adds it to the sprite.
		sprite->addChild(tempNode); // adds the tempNode so that it goes over the sprite.
		
		break;
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
