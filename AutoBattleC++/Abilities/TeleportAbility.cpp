#include "TeleportAbility.h"
#include <iostream>

TeleportAbility::TeleportAbility(int maxDistance, std::shared_ptr<Grid> battleFieldGrid) : maxRangeAroundTarget(maxDistance)
{
	battleField = battleFieldGrid;
}

void TeleportAbility::ActivateAbility(std::shared_ptr<Character> user)
{
	auto grid = battleField.lock();

	if (!grid) return;

	int currentSearchRange = 1;
	int newBoxX;
	int newBoxY;
	bool positionFound = false;

	while (currentSearchRange <= maxRangeAroundTarget)
	{
		//if get teleport location succeeded
		if (GetTeleportLocation(user, currentSearchRange, newBoxX, newBoxY))
		{
			int newBoxIndex = grid->GetBoxIndexByLocation(newBoxX, newBoxY);
			auto newBox = grid->grids[newBoxIndex];
			if (!newBox->GetOccupied())
			{
				user->currentBox->SetOccupy(false, " ");
				user->currentBox = newBox;
				user->currentBox->SetOccupy(true, user->Icon);
				printf("Player %s teleported to %d,%d\n", user->Icon.c_str(), newBox->xIndex, newBox->yIndex);
				grid->drawBattlefield();
				positionFound = true;
				break;
			}
		}
		//if not successful we increase the search range
		currentSearchRange++;
	}

	if (!positionFound)
	{
		printf("Player %s Could not teleport. No available positions.\n", user->Icon.c_str());
	}
}

//Gets a location near the target based on range
bool TeleportAbility::GetTeleportLocation(std::shared_ptr<Character> user, int tpStartRange, int& newX, int& newY)
{
	auto target = user->GetTarget();
	auto grid = battleField.lock();

	if (!grid) return false;

	//Get random offsets to use for teleport
	int offsetX = rand() % (2 * tpStartRange) - tpStartRange;
	int offsetY = rand() % (2 * tpStartRange) - tpStartRange;

	//Assign the new location offsetted from the target by our rand offset
	newX = target->currentBox->xIndex + offsetX;
	newY = target->currentBox->yIndex + offsetY;

	//If out of bound we return -1 to indicate we need to call this again
	if (newX < 0 || newX >= grid->xLength || newY < 0 || newY >= grid->yLength)
	{
		return false;
	}
	return true;
}
