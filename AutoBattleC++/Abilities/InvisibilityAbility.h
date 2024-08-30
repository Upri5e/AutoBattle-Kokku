#ifndef INVISIBILITYABILITY_H
#define INVISIBILITYABILITY_H

#include "AbilityComponent.h"

class InvisibilityAbility : public AbilityComponent
{
public:
	InvisibilityAbility(int duration);
	void ActivateAbility(std::shared_ptr<Character> user) override;
	void DeactivateAbility() override;
	void UpdateAbility();

	int invisDuration;
private:
	int turnsCount;
	std::weak_ptr<Character> characterPtr;
};

#endif // !INVISIBILITYABILITY_H
