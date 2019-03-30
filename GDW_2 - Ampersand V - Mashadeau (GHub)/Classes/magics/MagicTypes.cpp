// holds the information on the various types of magic in the game.
// This doesn't inherit the entity class, but it is used by all entites.
#include "magics/MagicTypes.h"

// const int magic::MagicType::TOTAL_TYPES = 6;

// sets entity type with default values.
magic::MagicType::MagicType(magic_t type)
{
	// checks the provided type, and initalizes the damage multipliers against all types
	// if you're confused, ask yourself "how weak is the entity to the attack is has been hit by?"
	
	// order: null - shadow - fire - water - earth - air
	switch (type)
	{
	case null: // neutral damage
		*this = MagicType(null, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F);
		break;

	case shadow: // resists earth, weak to fire
		*this = MagicType(shadow, 1.0F, 1.0F, 2.0F, 1.0F, 0.5F, 1.0F);
		break;

	case fire: // resists fire, weak to water
		*this = MagicType(fire, 1.0F, 1.0F, 0.5F, 2.0F, 1.0F, 1.0F);
		break;

	case water: // resists fire, weak to earth
		*this = MagicType(water, 1.0F, 1.0F, 0.5F, 1.0F, 2.0F, 1.0F);
		break;

	case earth: // resists water, weak to shadow
		*this = MagicType(earth, 1.0F, 2.0F, 1.0F, 0.5F, 1.0F, 1.0F);
		break;

	case air: // somewhat resists fire, weak to earth
		*this = MagicType(air, 1.0F, 1.0F, 0.75F, 1.0F, 1.75F, 1.0F);
		break;
	
	}
}

// sets type weaknesses for an entity, as well as its type.
// for the weaknesses, ask yourself "how weak is the entity to attacks of this type.
magic::MagicType::MagicType(magic_t type, float nullWeakness, float shadowWeakness, float fireWeakness, float waterWeakness, float earthWeakness, float airWeakness)
{
	this->type = type;
	damageMultipliers[0] = nullWeakness;
	damageMultipliers[1] = shadowWeakness;
	damageMultipliers[2] = fireWeakness;
	damageMultipliers[3] = waterWeakness;
	damageMultipliers[4] = earthWeakness;
	damageMultipliers[5] = airWeakness;
}

magic::MagicType::~MagicType() {}

// returns the magic type of the entity
magic::magic_t magic::MagicType::getType() const { return type; }

// sets the magic type of the entity
void magic::MagicType::setType(magic::magic_t type) { this->type = type; }

// returns the multiplier that will be applied to the attack the entity is about to be hit with.
float magic::MagicType::getWeakness(magic_t magicType) const { return damageMultipliers[(int)magicType]; }

// gets how weak the entity is to null damage.
float magic::MagicType::getNullWeakness() const { return *nullWeakness; }

// gets how weak the entity is to shadow damage.
float magic::MagicType::getShadowWeakness() const { return *shadowWeakness; }

// gets how weak the entity is to fire damage.
float magic::MagicType::getFireWeakness() const { return *fireWeakness; }

// gets how weak the entity is to water damage.
float magic::MagicType::getWaterWeakness() const { return *waterWeakness; }

// gets how weak the entity is to earth damage.
float magic::MagicType::getEarthWeakness() const { return *earthWeakness; }

// gets how weak the entity is to air damage.
float magic::MagicType::getAirWeakness() const { return *airWeakness; }

// calculates how much damage the 'attacker' will do the the 'victim' by applying a multiplier to 'damage'.
float magic::MagicType::damage(MagicType & attacker, MagicType & victim, float damage)
{
	// the amount of weakness the victim has to the attack is gotten, and is then multiplied by how much damage the attack should do to calculate total damage.
	return damage * victim.getWeakness(attacker.getType());
}
