#include "Paladin.h"
#include"Abilities/KnockBackAbility.h"

Paladin::Paladin(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	:Character(Types::CharacterClass::Paladin, index, bfieldGrid, icon)
{
	auto ability = std::make_shared<KnockBackAbility>(KnockbackDistance, battleFieldGrid);
	AddAbility(ability);
}

Paladin::~Paladin()
{
}

void Paladin::PlayTurn()
{
	printf("Im a paladin now");
	Character::PlayTurn();
}

