#ifndef CHARACTERFACTORY_H
#define	CHARACTERFACTORY_H

#include<memory>

#include "Character.h"
#include "Paladin.h"
#include "Cleric.h"

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
		case Types::Archer:
		default:
			return std::make_shared<Character>(charClass, index, bfieldGrid, icon);
		}
	}
};
#endif // !CHARACTERFACTORY_H
