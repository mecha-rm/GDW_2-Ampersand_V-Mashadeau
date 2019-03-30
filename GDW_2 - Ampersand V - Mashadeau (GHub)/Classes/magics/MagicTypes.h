// holds the information on the various types of magic in the game.
// This doesn't inherit the entity class, but it is used by all entites.
#pragma once

// the different types of magic in the game
namespace magic {
	// the enum for magic types
	enum magic_t
	{
		null = 0,
		shadow = 1,
		fire = 2,
		water = 3,
		earth = 4,
		air = 5
	};

	typedef class MagicType
	{
	public:
		
		/*
		* Types:
		*	0: null
		*	1: shadow
		*	2: fire
		*	3: water
		*	4: earth
		*	5: air
		*
		* sets the type of magic the entity is; the constructor handles the weakness matchup.
		*/
		MagicType(magic_t type = null);

		/*
		* Types:
		*	0: null
		*	1: shadow
		*	2: fire
		*	3: water
		*	4: earth
		*	5: air
		*
		* sets the type of magic the entity is, and the weakness matchup. This should NOT contradict the standard type magics.
		* the question applied to this is "how weak is the entity to this type of attack?"
		*/
		MagicType(magic_t type, float nullWeakness, float shadowWeakness, float fireWeakness, float waterWeakness, float earthWeakness, float airWeakness);
		
		~MagicType();

		// returns the magic type of the entity
		magic_t getType() const;

		// sets the magic type. The weaknesses remain the same if this is called.
		void setType(magic_t type);

		// returns how weak the entity is to the provided type. This should be used to consult how much damage an attack should do to an entity.
		float getWeakness(magic_t magicType) const;

		// gets how weak the entity is to null damage.
		float getNullWeakness() const;

		// gets how weak the entity is to shadow damage.
		float getShadowWeakness() const;

		// gets how weak the entity is to fire damage.
		float getFireWeakness() const;

		// gets how weak the entity is to water damage.
		float getWaterWeakness() const;

		// gets how weak the entity is to earth damage.
		float getEarthWeakness() const;

		// gets how weak the entity is to air damage.
		float getAirWeakness() const;

		// calculates the amount of damage the 'attacker' will do the 'victim' my multiplying variable 'damage'.
		static float damage(MagicType & attacker, MagicType & victim, float damage);

		static const int TOTAL_TYPES; // the total amount of types in the game.
	private:
		magic_t type; // the type of magic the entity is.
		
		/*
		 * damageMultipliers: these are applied to an attack that's about to hit an entity.
		 *	It affects HOW MUCH DAMAGE the entity that's ABOUT TO BE HIT takes by checking what the entity's type match up is BEFORE calculating damage.
		 *
		 * [0]: multiplier when taking null damage
		 * [1]: multiplier when taking shadow damage
		 * [2]: multiplier when taking fire damage
		 * [3]: multiplier when taking water damage
		 * [4]: multiplier when taking earth damage
		 * [5]: multiplier when taking air damage
		 
		 * the multipliers are applied to an entity's attack to decide how much damage it will do to a given entity.
		 * if you're confused, ask yourself "how weak is the entity to the attack is has been hit by?"
		 * x = 1 : the enemy takes neutral damage.
		 * 0 < x < 1 : the enemy being hit is resistent to this type of magic (i.e. it takes less than 1.0x the damage)
		 * 0 < 1 < x : the enemy being hit has a weakness to this type of magic (i.e. it takes greater than 1.0x the damage).
		 * x < 0 < 1 : the damage the entity is about to take will have the opposite effect on them. Instead of taking damage, it will heal them.
				- think "the enemy gets (abs)x times the health back when it. The value of x MUST be negative in this case.
		*/
		float damageMultipliers[6];

		// saves pointers to specific parts of the array for easy access. These couldn't be made 'const' becasue it would delete the functions.

		// a pointer ot the spot in the array that saves how weak the entity is to null damage.
		float * nullWeakness = &damageMultipliers[0];
		// a pointer ot the spot in the array that saves how weak the entity is to shadow damage.
		float * shadowWeakness = &damageMultipliers[1];
		// a pointer ot the spot in the array that saves how weak the entity is to fire damage.
		float * fireWeakness = &damageMultipliers[2];
		// a pointer ot the spot in the array that saves how weak the entity is to water damage.
		float *waterWeakness = &damageMultipliers[3];
		// a pointer ot the spot in the array that saves how weak the entity is to earth damage.
		float * earthWeakness = &damageMultipliers[4];
		// a pointer ot the spot in the array that saves how weak the entity is to air damage.
		float * airWeakness = &damageMultipliers[5];


	protected:

	} Magic;
}
