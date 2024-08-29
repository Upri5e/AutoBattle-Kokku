#include "KnockBackAbility.h"
#include "../Types.h"

KnockBackAbility::KnockBackAbility(int tiles, std::shared_ptr<Grid> battleFieldGrid) : knockBackDistance(tiles), grid(battleFieldGrid)
{
}
void KnockBackAbility::ActivateAbility(Character& user)
{
	auto target = user.GetTarget();

	if (target && !target->IsDead)
	{
		int localKnockDistance = knockBackDistance;
		int newX = target->currentBox->xIndex;
		int newY = target->currentBox->yIndex;
		
		while (localKnockDistance > 0)
		{
			GetLocAfterKnockback(user, localKnockDistance, newX, newY);

			if (newX >= 0 && newX < grid->xLength && newY >= 0 && newY < grid->yLength)
			{
				auto newBoxIndex = grid->GetBoxIndexByLocation(newX, newY);
				auto newBox = grid->grids[newBoxIndex];

				if (newBox->GetOccupied())
				{
					localKnockDistance--;
					continue;
				}
				else
				{
					target->currentBox->SetOccupy(false, " ");
					target->currentBox = newBox;
					target->currentBox->SetOccupy(true, target->Icon);
					grid->drawBattlefield();
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}
void KnockBackAbility::GetLocAfterKnockback(Character& user, int knockBackDist, int& newX, int& newY)
{
	auto target = user.GetTarget();
	newX = target->currentBox->xIndex;
	newY = target->currentBox->yIndex;

	if (user.currentBox->xIndex == target->currentBox->xIndex) { //if the 2 characters are in the same column
		if (user.currentBox->yIndex > target->currentBox->yIndex) //Knock back the row
		{
			newY += knockBackDist;
		}
		else
		{
			newY -= knockBackDist;
		}
	}
	else if (user.currentBox->yIndex == target->currentBox->yIndex) //Else if 2 characters are in the same row
	{
		if (user.currentBox->xIndex > target->currentBox->xIndex) { //knockback on column
			newX -= knockBackDist;
		}
		else {
			newX += knockBackDist;
		}
	}
 }