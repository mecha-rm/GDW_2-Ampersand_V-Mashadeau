#include "areas/AIN_X/AIN_X00.h"


// using an initalizer list caused problems, so no parameters were sent.
AIN_X00::AIN_X00() : Area("images/backgrounds/AIN_X00a.png")
{
	bool flipY = false; // flip the tiles and enemies positions on the y-axis

	name = "X00";
	bg_img1 = "images/backgrounds/AIN_X00a.png";

	tileArrayToVector(flipY); // set to 'true' to flip the tiles along the y-axis
	enemyArrayToVector(flipY); // set to 'true' to flip the enemies along the y-axis.
}

AIN_X00::~AIN_X00() {}

// stores the elements from the tile array into the tiles vector in the Area class. Variable flipY determines whether the bottom of the array [0][0] is treated as the bottom of the screen, or the top.
void AIN_X00::tileArrayToVector(const bool flipY)
{
	float offset = 0.0F; // used to offset copies of the element

	for (int row = 0; row < ROW_MAX; row++)
	{
		for (int col = 0; col < COL_MAX; col++)
		{
			if (tileGrid[row][col] == nullptr) // if the location is a nullptr, the program skips it
				continue;

			tileGrid[row][col]->setPosition(64.0F + GRID_UNIT_SIZE * col, 64.0F + GRID_UNIT_SIZE * row); // sets the position of the current tile, based on its position in the array.
			if (flipY)
				tileGrid[row][col]->setPositionY(GRID_UNIT_SIZE * ROW_MAX - tileGrid[row][col]->getPositionY());
			

			
			sceneTiles.push_back(tileGrid[row][col]); // adds the tile to the scene.

			if (tileGrid[row][col]->COPY_UP > 0) // Copies Upwards
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_UP; i++) // loops while there are still copies left to be made.
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX(), tileGrid[row][col]->getPositionY() + offset * i); // makes a tile one square above the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_DOWN > 0) // Copies  Down
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_DOWN; i++) // loops while there are still copies left to be made.
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX(), tileGrid[row][col]->getPositionY() - offset * i); // makes a tile one square below the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_LEFT > 0) // Copies left
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_LEFT; i++) // loops while there are still copies left to be made.
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX() - offset * i, tileGrid[row][col]->getPositionY()); // makes a tile one square below the previous tile.
				}
			}

			if (tileGrid[row][col]->COPY_RIGHT > 0) // Copies Right
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (tileGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? tileGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= tileGrid[row][col]->COPY_RIGHT; i++) // loops while there are still copies left to be made.
				{
					sceneTiles.push_back(new entity::Tile(tileGrid[row][col]->getTIN(), tileGrid[row][col]->getLetter())); // adds the new tile to the vector.
					sceneTiles.at(sceneTiles.size() - 1)->setPosition(tileGrid[row][col]->getPositionX() + offset * i, tileGrid[row][col]->getPositionY()); // makes a tile one square below the previous tile.
				}
			}

		}
	}
}

// stores the elements from the enemy array into the enemy vector in the Area class. Variable flipY determines whether the bottom of the array [0][0] is treated as the bottom of the screen, or the top.
void AIN_X00::enemyArrayToVector(const bool flipY)
{
	float offset = 0.0F; // used to offset copies of the element

	for (int row = 0; row < ROW_MAX; row++)
	{
		for (int col = 0; col < COL_MAX; col++)
		{
			if (enemyGrid[row][col] == nullptr) // if the location is a nullptr, the program skips it
				continue;

			enemyGrid[row][col]->setPosition(64.0F + GRID_UNIT_SIZE * col, 64.0F + GRID_UNIT_SIZE * row); // sets the position of the current enemy, based on its position in the array.
			
			if (flipY) // flipping the enemy's position if flipY is true
				enemyGrid[row][col]->setPositionY(GRID_UNIT_SIZE * ROW_MAX - enemyGrid[row][col]->getPositionY());


			sceneEnemies.push_back(enemyGrid[row][col]); // adds the enemy to the scene.

			if (enemyGrid[row][col]->COPY_UP > 0) // Copies Upwards
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_UP; i++) // loops while there are still copies left to be made.
				{
					sceneEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					sceneEnemies.at(sceneEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX(), enemyGrid[row][col]->getPositionY() + offset * i); // makes a enemy one unit above the previous enemy.
				}
			}

			if (enemyGrid[row][col]->COPY_DOWN > 0) // Copies  Down
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's height is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxY() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_DOWN; i++) // loops while there are still copies left to be made.
				{
					sceneEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					sceneEnemies.at(sceneEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX(), enemyGrid[row][col]->getPositionY() - offset * i); // makes a enemy one square below the previous tile.
				}
			}

			if (enemyGrid[row][col]->COPY_LEFT > 0) // Copies left
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_LEFT; i++) // loops while there are still copies left to be made.
				{
					sceneEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					sceneEnemies.at(sceneEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX() - offset * i, enemyGrid[row][col]->getPositionY()); // makes a enemy one square below the previous tile.
				}
			}

			if (enemyGrid[row][col]->COPY_RIGHT > 0) // Copies Right
			{
				// If the user wants the sprite to be offset by its actual size, the textureRect's width is used. If not, then GRID_UNIT_SIZE pixels are used.
				offset = (enemyGrid[row][col]->OFFSET_BY_SPRITE_SIZE) ? enemyGrid[row][col]->getSprite()->getTextureRect().getMaxX() : GRID_UNIT_SIZE;

				for (int i = 1; i <= enemyGrid[row][col]->COPY_RIGHT; i++) // loops while there are still copies left to be made.
				{
					sceneEnemies.push_back(new entity::Enemy(enemyGrid[row][col]->getEIN(), enemyGrid[row][col]->getLetter())); // adds the new enemy to the vector.
					sceneEnemies.at(sceneEnemies.size() - 1)->setPosition(enemyGrid[row][col]->getPositionX() + offset * i, enemyGrid[row][col]->getPositionY()); // makes a enemy one square below the previous tile.
				}
			}

		}
	}
}
