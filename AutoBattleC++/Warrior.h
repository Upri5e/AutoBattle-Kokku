#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class Warrior : public Character
{
public:

	Warrior(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon);

	void Move() override;
};

#endif WARRIOR_H