#include "Paladin.h"
#include"Abilities/KnockBackAbility.h"
#include <iostream>

Paladin::Paladin(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	:Character(Types::CharacterClass::Paladin, index, bfieldGrid, icon)
{
	//Add the knockback ability to paladin
	Ability = std::make_unique<KnockBackAbility>(KnockbackDistance, battleFieldGrid);
}

Paladin::~Paladin()
{
}

void Paladin::Attack()
{
	Character::Attack(); //Attack the target first

	if (!target || target->IsDead) //If the target dies we dont do ability
		return;

	//Check if knockback enemy
	int random = rand() % 100;

	if (random < Ability->chance)
	{
		printf("%s knocked %s back\n", Icon.c_str(), GetTarget()->Icon.c_str());
		Ability->ActivateAbility(shared_from_this()); //activate the ability
	}
}

