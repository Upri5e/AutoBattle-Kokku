#include "InvisibilityAbility.h"

InvisibilityAbility::InvisibilityAbility(int duration) : invisDuration(duration)
{
	activeStatus = false;
	turnsCount = 0;
}

void InvisibilityAbility::ActivateAbility(std::shared_ptr<Character> user)
{
	if (!activeStatus)
	{
		characterPtr = user;
		turnsCount = 0;
		user->canBeChased = false;
		user->canBeAttacked = false;
		activeStatus = true;
	}
}

void InvisibilityAbility::DeactivateAbility()
{
	if (auto characterSPtr = characterPtr.lock())
	{
		if (activeStatus)
		{
			characterSPtr->canBeChased = true;
			characterSPtr->canBeAttacked = true;
			activeStatus = false;
		}
		return;
	}
}

void InvisibilityAbility::UpdateAbility()
{
	turnsCount++;

	if (turnsCount >= invisDuration)
	{
		DeactivateAbility();
		return;
	}
}