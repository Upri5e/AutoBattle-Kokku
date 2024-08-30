#ifndef THROWROCKABILITY_H
#define THROWROCKABILITY_H

#include "AbilityComponent.h"

class ThrowRockAbility : public AbilityComponent
{

public:

	ThrowRockAbility(float extraDamage);
	void ActivateAbility(std::shared_ptr<Character> user) override;

private:
	float damage;
};

#endif // !THROWROCKABILITY_H
