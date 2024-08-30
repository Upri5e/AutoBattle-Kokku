#ifndef ARCHER_H
#define ARCHER_H

#include "Character.h"

class Archer : public Character
{
public:
	Archer(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon);
	void PlayTurn() override;
};

#endif // !ARCHER_H

