#ifndef KNOCKBACKABILITY_H
#define KNOCKBACKABILITY_H

#include "AbilityComponent.h"
#include <memory>

class KnockBackAbility : public AbilityComponent
{
private:
	int knockBackDistance;
	std::shared_ptr<Grid> grid;

	void GetLocAfterKnockback(Character& user, int knockBackDist, int& newX, int& newY);
public:

	KnockBackAbility(int tiles, std::shared_ptr<Grid> battleFieldGrid);

	void ActivateAbility(std::shared_ptr <Character> user) override;
};

#endif // !KNOCKBACKABILITY_H


