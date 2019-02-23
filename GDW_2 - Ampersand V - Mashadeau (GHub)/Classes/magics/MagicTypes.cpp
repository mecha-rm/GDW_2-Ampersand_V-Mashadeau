// holds the information on the various types of magic in the game.
// This doesn't inherit the entity class, but it is used by all entites.
#include "magics/MagicTypes.h"

const int magic::MagicTypes::TOTAL_TYPES = 6;

// sets entity type with default values.
magic::MagicTypes::MagicTypes(magic_t type)
{
	// checks the provided type, and initalizes the damage multipliers against all types
	// if you're confused, ask yourself "how weak is the entity to the attack is has been hit by?"
	// order: null - shadow - fire - water - earth - air
	switch (type)
	{
	case null: // neutral damage
		MagicTypes(null, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F);
		break;

	case shadow: // resists earth, weak to fire
		MagicTypes(shadow, 1.0F, 1.0F, 2.0F, 1.0F, 0.5F, 1.0F);
		break;

	case fire: // resists fire, weak to water
		MagicTypes(fire, 1.0F, 1.0F, 0.5F, 2.0F, 1.0F, 1.0F);
		break;

	case water: // resists fire, weak to earth
		MagicTypes(water, 1.0F, 1.0F, 0.5F, 1.0F, 2.0F, 1.0F);
		break;

	case earth: // resists water, weak to shadow
		MagicTypes(earth, 1.0F, 2.0F, 1.0F, 0.5F, 1.0F, 1.0F);
		break;

	case air: // somewhat resists fire, weak to earth
		MagicTypes(air, 1.0F, 1.0F, 0.75F, 1.0F, 1.75F, 1.0F);
		break;
	
	}
}

// sets type weaknesses for an entity, as well as its type.
// for the weaknesses, ask yourself "how weak is the entity to attacks of this type.
magic::MagicTypes::MagicTypes(magic_t type, float nullWeakness, float shadowWeakness, float fireWeakness, float waterWeakness, float earthWeakness, float airWeakness)
{
	this->type = type;
	damageMultipliers[0] = nullWeakness;
	damageMultipliers[1] = shadowWeakness;
	damageMultipliers[2] = fireWeakness;
	damageMultipliers[3] = waterWeakness;
	damageMultipliers[4] = earthWeakness;
	damageMultipliers[5] = airWeakness;
}

magic::MagicTypes::~MagicTypes() {}

// returns the magic type of the entity
magic::magic_t magic::MagicTypes::getType() const { return type; }

// returns the multiplier that will be applied to the attack the entity is about to be hit with.
float magic::MagicTypes::getWeakness(magic_t entityType) const { return damageMultipliers[entityType]; }
