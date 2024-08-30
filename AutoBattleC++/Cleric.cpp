#include "Cleric.h"
#include "Abilities/InvisibilityAbility.h"
#include <iostream>

Cleric::Cleric(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	:Character(Types::Cleric, index, bfieldGrid, icon)
{
	srand(time(NULL)); //Seed random number generator
	Ability = std::make_unique<InvisibilityAbility>(1);
	Ability->chance = 100;
}

Cleric::~Cleric()
{
}

void Cleric::PlayTurn()
{
	if (Ability->GetStatus())
	{
		Ability->UpdateAbility();
	}
	else
	{
		int random = rand() % 100;
		if (random < Ability->chance)
		{
			printf("%s is invisible\n", Icon.c_str());
			Ability->ActivateAbility(shared_from_this());
		}
	}
	Character::PlayTurn();
}
