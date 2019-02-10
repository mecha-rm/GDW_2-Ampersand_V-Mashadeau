#include "areas/AIN_X/AIN_X00.h"


// using an initalizer list caused problems, so no parameters were sent.
AIN_X00::AIN_X00() : Area("images/backgrounds/AIN_X00a.png")
{
	name = "X00";
	bg_img1 = "images/backgrounds/AIN_X00a.png";

	arrayToVector();
	// Area::arrayToVector(*tileGrid, ROW_MAX, COL_MAX);
}

AIN_X00::~AIN_X00()
{
}

// stores the elements from the array into the tiles vector in the Area class
void AIN_X00::arrayToVector()
{
	float offset = 0.0F;

	for (int row = 0; row < ROW_MAX; row++)
	{
		for (int col = 0; col < COL_MAX; col++)
		{
			if (tileGrid[row][col] == nullptr) // if the location is a nullptr, the program skips it
				continue;

			tileGrid[row][col]->setPosition(64.0F + 128.0F * col, 64.0F + 128.0F * row); // sets the position of the current tile, based on its position in the array.
			sceneTiles.push_back(tileGrid[row][col]); // adds the tile to the scene.

			if (tileGrid[row][col]->COPY_UP > 0) // Copies Upwards
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then 128.0 pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxY() : 128.0F;

				for (int i = 1; i <= tileGrid[row][col]->COPY_UP; i++) // while there are still copies left to be made...
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPositionY(tileGrid[row][col]->getPositionY() + offset * i); // makes a tile one square above the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_DOWN > 0) // Copies  Down
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then 128.0 pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxY() : 128.0F;

				for (int i = 1; i <= tileGrid[row][col]->COPY_DOWN; i++) // while there are still copies left to be made...
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPositionY(tileGrid[row][col]->getPositionY() - offset * i); // makes a tile one square below the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_LEFT > 0) // Copies left
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then 128.0 pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxX() : 128.0F;

				for (int i = 1; i <= tileGrid[row][col]->COPY_LEFT; i++) // while there are still copies left to be made...
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPositionX(tileGrid[row][col]->getPositionX() - offset * i); // makes a tile one square below the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_RIGHT > 0) // Copies Right
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then 128.0 pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxX() : 128.0F;

				for (int i = 1; i <= tileGrid[row][col]->COPY_RIGHT; i++) // while there are still copies left to be made...
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPositionX(tileGrid[row][col]->getPositionX() + offset * i); // makes a tile one square below the previous tile.
				}
			}

		}
	}
}
