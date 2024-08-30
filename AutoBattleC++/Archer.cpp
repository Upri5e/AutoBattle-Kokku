#include "Archer.h"
#include "Abilities/ThrowRockAbility.h"
#include<iostream>

Archer::Archer(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	:Character(Types::Archer, index, bfieldGrid, icon)
{
	Ability = std::make_unique<ThrowRockAbility>(1.5); //Create and add the ability to the class
}

void Archer::PlayTurn()
{
	if (target && target->canBeAttacked)
	{
		int random = rand() % 100;
		if (random <= Ability->chance)
		{
			Ability->ActivateAbility(shared_from_this());
			return;
		}
	}

	Character::PlayTurn();
}

