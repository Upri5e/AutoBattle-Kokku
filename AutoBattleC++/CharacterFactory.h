#ifndef CHARACTERFACTORY_H
#define	CHARACTERFACTORY_H

#include<memory>

#include "Character.h"
#include "Paladin.h"
#include "Cleric.h"
#include "Warrior.h"
#include "Archer.h"

class CharacterFactory {
public:
	static std::shared_ptr<Character> CreateCharacter(Types::CharacterClass charClass, int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	{
		switch (charClass)
		{
		case Types::Paladin:
			return std::make_shared<Paladin>(index, bfieldGrid, icon);
		case Types::Cleric:
			return std::make_shared<Cleric>(index, bfieldGrid, icon);
		case Types::Warrior:
			return std::make_shared<Warrior>(index, bfieldGrid, icon);
		case Types::Archer:
			return std::make_shared<Archer>(index, bfieldGrid, icon);
		default:
			return std::make_shared<Character>(charClass, index, bfieldGrid, icon);
		}
	}
};
#endif // !CHARACTERFACTORY_H
