#ifndef TELEPORTABILITY_H
#define TELEPORTABILITY_H

#include "AbilityComponent.h"

class TeleportAbility : public AbilityComponent
{
public:
	TeleportAbility(int maxDistance, std::shared_ptr<Grid> battleFieldGrid);

	void ActivateAbility(std::shared_ptr<Character> user) override;

private:
	int maxRangeAroundTarget;
	std::weak_ptr<Grid> battleField;
	bool GetTeleportLocation(std::shared_ptr <Character> user,int tpStartRange, int& newX, int& newY);
};

#endif // !TELEPORTABILITY_H
