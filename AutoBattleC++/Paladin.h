#ifndef PALADIN_H
#define PALADIN_H

#include "Character.h"
#include <memory>

class Paladin : public Character
{
public:

	Paladin(int index, std::shared_ptr<Grid> bfieldGrid, std::string icon);
	~Paladin();

	void Attack() override;

private:
	int KnockbackDistance = 3;
};

#endif // !PALADIN_H
