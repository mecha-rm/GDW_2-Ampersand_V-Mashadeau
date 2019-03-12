// information for all entities in a scene, which are physical elements part of the game world.
#pragma once

#include <string>
// #include "cocos2d.h"

#include "magics/MagicTypes.h"
#include "Primitives.h"
#include "Utilities.h"
#include <iostream>
using namespace cocos2d;

namespace entity
{
	// these tags are used to set the identification tags for different entites.
	// these are currently not being used, but they can discern different entities.
	enum etag
	{
		entity = 0,
		tile = 1,
		player = 2,
		enemy = 3,
		weapon = 4,
		item = 5
	};
	

	class Entity
	{
	public:
		Entity(std::string texture = "", float globalZOrder = 0.0F);
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

		// returns the magic type of the entity; changing the magic type will result in the defaults for that type being used.
		magic::magic_t getMagicType() const;

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

		/*
		Just use sprite->rotate().

		// rotates the entity using the rotation value stored in the class.
		Vec2 rotateEntity(Vec2 acceleration);

		// rotates the entity. An acceleration vector can be passed if the user wants to send the entity in the direction they're being rotated in.
		// the rotation factor is assumed to be in radians.
		Vec2 rotateEntity(float theta, Vec2 acceleration);
		*/
		
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

		// sets the force of the entity
		void setForce(Vec2 force);
		// sets the force of the entity
		void setForce(float x, float y);
		// adds to the entity's current amount of force
		void addForce(Vec2 force);
		// adds force on the individual axes.
		void addForce(float forceX = 0.0F, float forceY = 0.0F);
		
		// gets the current velocity of the entity.
		Vec2 getVelocity();

		// zeroes out the entity's velocity on both axes
		void zeroVelocity();

		// zeroes out the entity's velocity on the x-axis.
		void zeroVelocityX();

		// zeroes out the entity's velocity on the y-axis.
		void zeroVelocityY();

		// returns the maximum velocity of the entity.
		Vec2 getMaxVelocity();

		// returns the deceleration rate of the entity.
		Vec2 getDecelerate() const;
		// returns at what point the entity comes to a complete stop.
		Vec2 getForceStop() const;
		// returns whether the entity has a constant velocity or not.
		bool getConstVelocity() const;

		// gets whether the entity is effected by gravity or not. If 'true', the entity is not affected by gravity.
		bool getAntiGravity() const;
		// sets whether the entity is effected by gravity or not. If 'false' is passed, then the entity becomes effected by gravity.
		void setAntiGravity(float antiGravity);
		// toggles the anti gravity on/off.
		void setAntiGravity();

		// returns a vector of all collision shapes for the entity.
		const std::vector<OOP::Primitive *> getCollisionShapes() const;

		// checks for collision between the entity object and the one passed.
		bool collision(entity::Entity * e2);

		// checks for collision between two entities.
		static bool collision(entity::Entity * e1, entity::Entity * e2);

		// update loop
		virtual void update(float deltaTime);

		static float * areaGravity; // saves the level of gravity in the scene. This should be shared by all entities.

		float theta = 0.0F; // the rotation factor of the entity. THIS SHOULD BE IN RADIANS.
	
		// the primitive that has recently encountered a collison. The location of this primitive is where it is overall, NOT where it is relevant to the player.
		OOP::Primitive * collidedPrimitive;

		static const cocos2d::Color4F CLR_ATK; // colour used for attacking collision shapes (i.e. these deal damage)
		static const cocos2d::Color4F CLR_DEF; // colour used for defensive collision shapes (i.e. these take damage)
		static const cocos2d::Color4F CLR_NEU; // colour used for a neutral object that can be interacted with, but does not take or deal damage.

	private:
		float mass = 1.0; // the mass of the entity
		
		// the velocity of the entity
		Vec2 velocity = Vec2(0.0f, 0.0f);
		// the maximum velocity an entity can reach.
		Vec2 maxVelocity = Vec2(999.0F, 999.0F);
		
		// when no force is being applied, the entity slows down by being multiplied by this deceleration rate. This should be less than one.
		Vec2 decelerate = Vec2(0.85F, 0.85F);
		// controls at what point the entity comes to a complete stop.
		Vec2 forceStop = Vec2(0.001F, 0.001F);

		// makes it so that the entity goes right to its maximum speed, instead of steadily approaching its max speed.
		bool constVelocity = false;

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

		// sets a new magic type for the entity
		void setMagicType(magic::magic_t magicType);

		// sets the entity's current velocity.
		void setVelocity(Vec2 velocity);

		// sets the maximum velocity of the entity.  Comparisons use the absolute value of the entity, so it must be above 0.
		void setMaxVelocity(Vec2 maxVelocity);

		// sets the deleration.  This should be less than 1 but greater than 0.
		void setDecelerate(Vec2 decelerate);
		// sets at what point the entity stops. The entity stops once it falls below the value of 'forceStop'
		void setForceStop(Vec2 forceStop);
		
		// sets whether the entity has constant velocity or not. If true, the entity will either have a speed of 0, or some other value. 
		void setConstVelocity(bool constVelocity);
		//  toggles constant velocity ON/OFF. If true, the entity will either have a speed of 0, or some other value. 
		void setConstVelocity();

		std::string name = ""; // the entity's name
		// int NAME_LEN; // maximum name lenth
		std::string description = ""; // the entity's description

		// the magic type of the entity
		magic::MagicTypes * magicType = new magic::MagicTypes(magic::null);

		Sprite * sprite; // the entity's sprite
		Rect frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F); // the size of an individual frame of the sprite.

		Vec2 force = Vec2(0.0f, 0.0f); // the force of the entity

		// a body used for collisions with the sprite. This is currently not being used in favour of manual collisions.
		// This is currently not being used.
		PhysicsBody * collisionBody;

		// holds all physical body collisions. There is an 'ID' that tells you what type is stored there so you can downcast.
		std::vector<OOP::Primitive * > collisionShapes;
		std::vector<OOP::Primitive *> attackShapes; // used for attack collisions.
		// holds all animation frames.
		std::vector<std::vector<AnimationFrame *>> animationFrames;

		// used to turn on and off the gravity. If 'antiGravity' is false, then the entity IS affected by gravity. If it's false, then the entity ISN'T effected by gravity.
		bool antiGravity = false;
	};
}



