#ifndef ABILITY_H
#define ABILITY_H

#include "../Character.h"

class Character;

class AbilityComponent {
public:

	~AbilityComponent() = default;
	virtual void ActivateAbility(std::shared_ptr<Character> user) {};
	virtual void UpdateAbility() {};
	virtual void DeactivateAbility() {};
	int chance = 50;

	bool GetStatus() {
		return activeStatus;
	}
protected:
	bool activeStatus;
};
#endif // !ABILITY_H
