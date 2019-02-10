#include "entities/Tile.h"
#include "Primitives.h"

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
	DrawNode * tempNode = DrawNode::create();
	
	sprite->setGlobalZOrder(3.0F);
	
	tempNode->setGlobalZOrder(3.0F);

	switch (TIN)
	{
	case 1:
		// set
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:

	case 10: // stop block
		
		// this->LETTER = 'a'; // there's only one block at the moment, so it's set as type a.
		setSprite(Sprite::create("images/tiles/TIN_010.png")); // sets the image for the sprite
		
		this->TIN = 10; // setting the TIN
		switch (LETTER)
		{
		case 'a': // 'a' is also the default type.
		default:
			this->LETTER = 'a';
			setTextureRect(0.0F, 0.0F, 128.0F, 128.0F);

			break;

		}
		break;

	

	case 11:


	default:
		this->TIN = 0;
		this->LETTER = 'a';
		setSprite(cocos2d::Sprite::create("images/tiles/TIN_010.png")); // uses TIN_010 by default. This will be covered up.
		sprite->setTextureRect(Rect(0.0F, 0.0F, 128.0F, 128.0F)); // creates a texture rect, so that the default only has one tile
		
		tempNode->drawSolidRect(Vec2(0.0F, 0.0F), Vec2(128.0F, 128.0F), Color4F::BLUE); // creates a solid blue rectangle to go over the actual image.
		tempNode->drawRect(Vec2(0.0F, 0.0F), Vec2(128.0F, 128.0F), Color4F::RED); // creates an outline for the rectangle, and adds it to the sprite.
		sprite->addChild(tempNode); // adds the tempNode so that it goes over the sprite.
		break;
	}
}


const unsigned int entity::Tile::getTIN() const
{
	return TIN;
}
// the letter of the tile
const char entity::Tile::getLetter() const { return LETTER; }
