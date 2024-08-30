#include "Warrior.h"
#include "Abilities/TeleportAbility.h"
#include <iostream>

Warrior::Warrior(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	:Character(Types::Warrior, index, bfieldGrid, icon)
{

	Ability = std::make_unique<TeleportAbility>(4,battleFieldGrid);
}

void Warrior::Move()
{
	int random = rand() % 100;
	if (random <= Ability->chance)
	{
		Ability->ActivateAbility(shared_from_this());
	}
	else
	{
		Character::Move();
	}
}
