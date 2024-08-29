#ifndef CHARACTERFACTORY_H
#define	CHARACTERFACTORY_H

#include<memory>

#include "Character.h"
#include "Paladin.h"

class CharacterFactory {
public:
	static std::shared_ptr<Character> CreateCharacter(Types::CharacterClass charClass, int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	{
		switch (charClass)
		{
		case Types::Paladin:
			return std::make_shared<Paladin>(index, bfieldGrid, icon);
			break;
		case Types::Warrior:
		case Types::Cleric:
		case Types::Archer:
		default:
			return std::make_shared<Character>(charClass, index, bfieldGrid, icon);
			break;
		}
	}
};
#endif // !CHARACTERFACTORY_H
