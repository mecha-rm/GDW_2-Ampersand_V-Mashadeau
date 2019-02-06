#pragma once

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

namespace entity
{
	class Entity
	{
	public:
		Entity();
		~Entity();

		// gets how long the entity has existed for.
		float getAge();

		// returns the name of the entity
		std::string getName();

		// returns the 
		std::string getDescription();

		// returns the entity's sprite
		Sprite * getSprite() const;

		// returns the image for the sprite
		Texture2D * getTexture() const;

		// Setting the position
		void setPosition(Vec2 newPos);

		// Setting the position
		void setPosition(float x, float y);

		Vec2 getPosition() const;

		// Setting the sprite's x position.
		void setPositionX(float x);

		// Getting the sprite's x position.
		float getPositionX() const;

		// Setting the sprite's y position.
		void setPositionY(float y);

		// Getting the sprite's y position.
		float getPositionY() const;

		// Sets the sprite's opacity via a percentage. Use a value from 0.0 to 1.0, with 1.0 (i.e. 100%) being full opacity.
		// Opacity for sprites are out of 255, but this function works on percentages.
		void setOpacity(float opacity);

		// gets the sprite's current opacity as a value from 0.0 to 1.0 (i.e. a decimal percentage)
		// Opacity for sprites are out of 255, but this function works on percentages.
		float getOpacity();

		// update loop
		void update(float deltaTime);

	private:

		// gets the length of time the entity has existed for, in milliseconds (delta time)
		float age;

	protected:
		// sets the sprite for the entity
		void setSprite(Sprite * sprite);

		// sets the sprite's texture (image)
		void setTexture(std::string image);


		std::string name; // the entity's name
		std::string description; // the entity's description

		Sprite * sprite;

	};
}



