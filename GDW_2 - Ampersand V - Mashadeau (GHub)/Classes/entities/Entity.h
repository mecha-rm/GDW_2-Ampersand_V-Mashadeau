// information for all entities in a scene, which are physical elements part of the game world.
#pragma once

#include <string>
// #include "cocos2d.h"

#include "magics/MagicTypes.h"
#include "Primitives.h"
#include "Utilities.h"
#include "SpriteAnimation.h"
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
		virtual ~Entity();

		// gets how long the entity has existed for.
		float getAge();

		// returns the name of the entity.
		const std::string getName() const;

		// sets the name of the entity.  This also gets stored as the sprite name.
		void setName(std::string name);

		// returns the description of the entity.
		const std::string getDescription() const;

		// sets the description of the entity.
		void setDescription(std::string description);

		// gets the tag that tells the user what kind of entity this is.
		entity::etag getTag();

		// sets the tag for the entity
		void setTag(entity::etag tag);

		// returns the entity's sprite
		Sprite * getSprite() const;

		// returns the image for the sprite
		Texture2D * getTexture() const;

		// gets the file path for the texture.
		std::string getTextureFilePath() const;

		// returns the rectangle used for cropping the texture
		Rect getTextureRect() const;

		// returns the magic type of the entity; changing the magic type will result in the defaults for that type being used.
		magic::magic_t getMagic_T() const;

		// gets the magic object of the entity. Use this to get it's level of effectiveness against other types.
		magic::MagicType getMagicType() const;


		// Setting the position. While all sprite children move with the sprite, their positions don't change (i.e. getPosition() for them would return the same value).
		virtual void setPosition(Vec2 newPos);

		// Setting the position
		virtual void setPosition(float x, float y);

		Vec2 getPosition() const;

		// Setting the sprite's x position.
		virtual void setPositionX(float x);

		// Getting the sprite's x position.
		float getPositionX() const;

		// Setting the sprite's y position.
		virtual void setPositionY(float y);

		// Getting the sprite's y position.
		float getPositionY() const;
		

		// Sets the sprite's opacity via a percentage. Use a value from 0.0 to 1.0, with 1.0 (i.e. 100%) being full opacity.
		// Opacity for sprites are out of 255, but this function works on percentages.
		void setOpacity(float opacity);

		// gets the sprite's current opacity as a value from 0.0 to 1.0 (i.e. a decimal percentage)
		// Opacity for sprites are out of 255, but this function works on percentages.
		float getOpacity();

		// flips the sprite on the x-axis using 'sprFX'. If 'aniFX' is 'true', then the sprite's animations are flipped on the x-axis as well.
		// If 'aniFX' is true, the provided value of 'sprFX' will become the flip factor for ALL ANIMATIONS.
		// in other words, if the sprite is flipped (sprFX == true) and aniFX is 'true', then all of the animation frames would share the same flip factor.
		void setFlippedSpriteX(bool sprFX, bool aniFX = true);

		// flips the sprite on the x-axis. If it was already flipped, it is un-flipped, and vice versa.
		// if aniFX is true, then the animations are also flipped in a similar fashion (if flipped, they become un-flipped, and vice-versa).
		void flipSpriteX(bool aniFX = true);

		// returns 'true' if the sprite is currently flipped on the x-axis. Do note that the current animation may have flip the sprite.
		bool getFlippedSpriteX() const;

		// returns 'true' if all of the sprite animations are flipped, false otherwise.
		bool getFlippedSpriteAnimationsX() const;


		// flips the sprite on the y-axis using 'sprFY'. If 'aniFY' is 'true', then the sprite's animations are flipped on the y-axis as well.
		// If 'aniFY' is true, the provided value of 'sprFY' will become the flip factor for ALL ANIMATIONS.
		// in other words, if the sprite is flipped (sprFX == true) and aniFX is 'true', then all of the animation frames would share the same flip factor.
		void setFlippedSpriteY(bool sprFY, bool aniFY = true);
		
		// flips the sprite on the y-axis. If it was already flipped, it is un-flipped, and vice versa.
		// if aniFx is true, then the animations are also flipped in a similar fashion (if flipped, they become un-flipped, and vice-versa).
		void flipSpriteY(bool aniFX = true);

		// returns 'true' if the sprite is currently flipped on the y-axis. Do note that the current animation may have flip the sprite.
		bool getFlippedSpriteY() const;

		// returns 'true' if all the sprite animations are flipped, false otherwise.
		bool getFlippedSpriteAnimationsY() const;


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
		
		// if true, then the acceleration is rotated in the update. If false, then it isn't. 
		bool getRotateAcceleration() const;

		// if true, then the acceleration is rotated in the update. If false, then it isn't. 
		void setRotateAcceleration(bool rAccel);

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

		// gets rotation factor in degrees (which is what it's stored as).
		float getRotationInDegrees();

		// sets the rotation factor in degrees.
		void setRotationInDegrees(float theta);

		// gets the rotation factor, converted to radians
		float getRotationInRadians();

		// sets the rotation factor in radians
		void setRotationInRadians(float theta);

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
		std::vector<OOP::Primitive *> getCollisionBodies() const;

		// sets a vector for collision bodies for the entity.
		void setCollisionBodies(std::vector<OOP::Primitive *>& colBodies);

		// returns the collision bodies of the entity, offset so that they're where they are relative to the whole game world.
		// NOTE: if the entity doesn't have a sprite, and/or if the sprite hasn't been added to anything, you shouldn't use this function, since it's based on the position of the sprite.
		virtual std::vector<OOP::Primitive *> getOffsetCollisionBodies() const;

		// returns the collision bodies of the provided entity, offset so that they're where they are relative to the whole game world.
		// NOTE: if the entity doesn't have a sprite, and/or if the sprite hasn't been added to anything, you shouldn't use this function, since it's based on the position of the sprite.
		static std::vector<OOP::Primitive *> getOffsetCollisionBodies(const cocos2d::Sprite * spr, const std::vector<OOP::Primitive *> & prims);

		// adds a primitive to the collision bodies vector. If it's already in the vector, it won't be added again.
		void addCollisionBody(OOP::Primitive * prim);

		// remove a primitive from the collision bodes vector
		void removeCollisionBody(OOP::Primitive * prim);
		
		// used to make all of the collision bodies either active or not active. Non-active collison boxes will not be picked up by collisions.
		void setActiveCollisionBodies(bool active);

		// turns off the collision bodies for the sprite.
		void disableCollisionBodies();

		// turns on the body collisions for the entity
		void enableCollisionBodies();
		
		// checks collision between two primitives. Do note that if the primitives don't have a collision algorithim setup, this will return false.
		static bool collision(OOP::Primitive * prim1, OOP::Primitive * prim2);

		// runs collisions between two primitive vectors. This should be used to check if a body collision collides with an attack collision.
		// this cannot save what two primitives collided with one another.
		static bool collision(std::vector<OOP::Primitive *>& cols1, std::vector<OOP::Primitive *>& cols2);

		// checks for collision between the entity object and the one passed. This uses the collisionBodies.
		bool collision(entity::Entity * e2);

		// checks for collision between two entities. This uses the collisionBodies vectors for both entities.
		static bool collision(entity::Entity * e1, entity::Entity * e2);

		// checks for collision between two entities. If the collisionBodies vector isn't the one meant to be used, pass a different set of vectors. Just make sure they're actually meant for the entites.
		// this offsets the locations of the attached primitives so that they're in the proper place.
		static bool collision(entity::Entity * e1, const std::vector<OOP::Primitive *> & e1Bodies, entity::Entity * e2, const std::vector<OOP::Primitive *> & e2Bodies);



		// returns the vector of animations.
		std::vector<OOP::SpriteSheetAnimation *> getAnimations() const;

		// returns an animation at the provided index. If no animation exists at this index, a 'nullptr' is returned.
		OOP::SpriteSheetAnimation * getAnimationByIndex(unsigned int index) const;

		// gets an animation by a tag. The first animation with this tag will be returned. If an animation with this tag is not found, a nullptr is returned.
		OOP::SpriteSheetAnimation * getAnimationByTag(int tag);

		// returns the index of the animation. If the animation does not exist in the animation vector, then a '-1' is returned.
		int getAnimationIndex(const OOP::SpriteSheetAnimation *) const;

		// gets the current animation being used. If there is no current animation, a nullptr is returned.
		OOP::SpriteSheetAnimation * getCurrentAnimation();

		// adds an animation to the entity. It also returns the index get the animation that has been added.
		void addAnimation(OOP::SpriteSheetAnimation *);

		// runs an animation based on a provided index. If no animation has this index, then no animation is run.
		void runAnimationByIndex(unsigned int index);

		// runs an animation based on a provided tag. If no animation has this tag, no changes are made.
		void runAnimationByTag(int tag);

		// returns 'true' if an animation is currently running, and false otherwise.
		bool runningAnimation();

		// update loop
		virtual void update(float deltaTime);

		static float * areaGravity; // saves the level of gravity in the scene. This should be shared by all entities.
	
		// the primitive that has recently encountered a collison. The location of this primitive is where it is overall, NOT where it is relevant to the player.
		OOP::Primitive * collidedPrimitive;

		// a boolean that toggles on/off hitbox visibility.
		// If you don't want to have some collision shapes visible, set this to 'false', and set specific entities to 'true' or 'false' after initialization.
		static bool shapesVisible;

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
		
		float age = 0; // gets the length of time the entity has existed for, in milliseconds (delta time)

		std::string name = ""; // the entity's name
		// int NAME_LEN; // maximum name lenth
		std::string description = ""; // the entity's description

		// the image path of the entity. Can be used to create another texture.
		std::string imagePath = "";

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

		// sets a new magic object for the entity based on a type and uses the default values for said type.
		void setMagicType(magic::magic_t magicType);

		// sets a new magic object for the entity.
		void setMagicType(magic::MagicType magic);

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

		// the magic type of the entity
		magic::MagicType magicType = magic::MagicType(magic::null);

		Sprite * sprite; // the entity's sprite
		Rect frameSize = Rect(0.0F, 0.0F, 128.0F, 128.0F); // the size of an individual frame of the sprite.

		std::vector<OOP::SpriteSheetAnimation *> animations; // a vector of animations.

		OOP::SpriteSheetAnimation * currentAnimation = nullptr; // saves a pointer to the current animation being run.

		Vec2 force = Vec2(0.0f, 0.0f); // the force of the entity

		// rotates the acceleration if 'true'. This uses the 'theta' value.
		bool rotateAccel = false;

		// holds all physical body collisions. There is an 'ID' that tells you what type is stored there so you can downcast.
		std::vector<OOP::Primitive * > collisionBodies;

		// used to turn on and off the gravity. If 'antiGravity' is false, then the entity IS affected by gravity. If it's false, then the entity ISN'T effected by gravity.
		bool antiGravity = false;

	};
}



