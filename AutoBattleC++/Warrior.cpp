#include "Warrior.h"

Warrior::Warrior(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	:Character(Types::Warrior, index, bfieldGrid, icon)
{
}
