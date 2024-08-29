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
		
		while (localKnockDistance > 0) //Loop untill we cannot knock the character back anymore
		{
			GetLocAfterKnockback(user, localKnockDistance, newX, newY); //Get the new location based on the current knockback distance

			if (newX >= 0 && newX < grid->xLength && newY >= 0 && newY < grid->yLength) //in bound of grid
			{
				auto newBoxIndex = grid->GetBoxIndexByLocation(newX, newY);
				auto newBox = grid->grids[newBoxIndex];

				if (newBox->GetOccupied()) //If the new box is occupied we need to -- the knockback distance and recalculate a new box
				{
					localKnockDistance--;
					continue;
				}
				else //new boxk can be occupide > move(knockback) target to new location
				{
					target->currentBox->SetOccupy(false, " ");
					target->currentBox = newBox;
					target->currentBox->SetOccupy(true, target->Icon);
					grid->drawBattlefield(); //Draw battlefield again because the target location changed
					break; //break out of the loop
				}
			}
			else //if out of bounds we -- knockback distance and recalculate new box
			{
				localKnockDistance--;
				continue;
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
		if (user.currentBox->yIndex > target->currentBox->yIndex) //Knock back on same column
		{
			newY -= knockBackDist;
		}
		else
		{
			newY += knockBackDist;
		}
	}
	else if (user.currentBox->yIndex == target->currentBox->yIndex) //Else if 2 characters are in the same row
	{
		if (user.currentBox->xIndex > target->currentBox->xIndex) //knockback on same row
		{ 
			newX -= knockBackDist;
		}
		else 
		{
			newX += knockBackDist;
		}
	}
 }