#ifndef ABILITY_H
#define ABILITY_H

#include "../Character.h"

class Character;

class AbilityComponent {
public:

	 ~AbilityComponent() = default;
	 virtual void ActivateAbility(Character& user) {};
};
#endif // !ABILITY_H
