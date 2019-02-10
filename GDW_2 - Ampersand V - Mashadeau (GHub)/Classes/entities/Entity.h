#pragma once

#include <string>
#include "cocos2d.h"

using namespace cocos2d;

namespace entity
{
	class Entity
	{
	public:
		Entity(std::string texture = "", Vec2 position = Vec2(0.0F, 0.0F));
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

		// returns the rectangle used for cropping the texture
		Rect getTextureRect() const;

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

		// sets the mass of the entity; it must be greater than 0.
		void setMass(float mass);

		// returns the mass of the entity
		float getMass() const;

		// gets the amount of force the entity has.
		Vec2 getForce() const;
		// gets hte amount of force the entity has on the x-axis.
		float getForceX() const;
		// gets hte amount of force the entity has on the y-axis.
		float getForceY() const;
		// sets the amount of force the entity has.

		void setForce(Vec2 force);
		// adds to the entity's current amount of force
		void addForce(Vec2 force);
		// adds force on the individual axes.
		void addForce(float forceX = 0.0F, float forceY = 0.0F);
		// update loop
		void update(float deltaTime);

	private:
		float mass = 1.0; // the mass of the entity
		
		Vec2 acceleration = Vec2(0.0f, 0.0f); // the acceleration of the entity
		Vec2 velocity = Vec2(0.0f, 0.0f); // the velocity of the entity
		bool constVelocity = false; // makes it so that the entity only has one speed.

		// gets the length of time the entity has existed for, in milliseconds (delta time)
		float age;

	protected:
		// sets the sprite for the entity
		void setSprite(Sprite * sprite);

		// sets the sprite's texture (image)
		void setTexture(std::string image);

		// sets the sprite's textureRect; i.e. the area of the sprite's that's actually used.
		// 'Rects' are based off a start point and end point.
		void setTextureRect(Rect textureRect);

		// sets the sprite's texture rect, i.e. the area of the sprite's image file that's used.
		// (x, y) and (width, height) act as starting points and ending points respectively
		// if USE_CENTRE is true, then the cropped area treats (x, y) as the centre of the area, rather than the corner of the area.
		void setTextureRect(float x, float y, float width, float height, const bool USE_CENTRE = false);


		std::string name; // the entity's name
		std::string description; // the entity's description

		Sprite * sprite;
		Vec2 force = Vec2(0.0f, 0.0f); // the force of the entity
	};
}



