#ifndef KNOCKBACKABILITY_H
#define KNOCKBACKABILITY_H

#include "AbilityComponent.h"
#include <memory>

class KnockBackAbility : public AbilityComponent
{
private:
	int knockBackDistance;
	std::weak_ptr<Grid> grid;

	void GetLocAfterKnockback(std::shared_ptr <Character> user, int knockBackDist, int& newX, int& newY);
public:

	KnockBackAbility(int tiles, std::shared_ptr<Grid> battleFieldGrid);

	void ActivateAbility(std::shared_ptr <Character> user) override;
};

#endif // !KNOCKBACKABILITY_H


