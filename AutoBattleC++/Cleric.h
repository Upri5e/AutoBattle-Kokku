#ifndef CLERIC_H
#define CLERIC_H

#include "Character.h"

class Cleric : public Character
{

public:
	Cleric(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon);
	~Cleric();

	void PlayTurn() override;
};
#endif // !CLERIC_H

