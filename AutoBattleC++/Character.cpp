#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <vector>
#include <algorithm>

//using namespace std;

//TODO::Add all params with defaults
Character::Character(Types::CharacterClass charcaterClass, int index) : PlayerIndex(index), Health(100), BaseDamage(50), DamageMultiplier(1), Icon('X'), IsDead(false), AttackRange(1)
{
}

Character::~Character()
{

}

bool Character::TakeDamage(float amount)
{
	//Check if damage kills character
	if ((Health -= amount) <= 0)
	{
		Die();
		return true;
	}
	return false;
}

//int Character::getIndex(std::vector<Types::GridBox*> v, int index)
//{
//	return 0;
//}

void Character::Die()
{
	Health = 0;
	IsDead = true;
}
//
//void Character::WalkTo(bool CanWalk)
//{
//
//}
//


void Character::StartTurn(std::shared_ptr<Grid> battlefieldGrid) {
	printf("Player %c turn\n", Icon);
	if (target && !target->IsDead)
	{
		if (CheckCloseTargets(battlefieldGrid, AttackRange)) //If target is within range, character attacks
		{
			Attack(target);
			return;
		}
		else
		{   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target

			int newBoxX = currentBox->xIndex;
			int newBoxY = currentBox->yIndex;

			//We check target position compared to player on X and store the movement to that direction accordingly
			if (currentBox->xIndex != target->currentBox->xIndex)
			{
				if (currentBox->xIndex > target->currentBox->xIndex)
				{
					newBoxX--;
				}
				else if (currentBox->xIndex < target->currentBox->xIndex)
				{
					newBoxX++;
				}
			}
			else if (currentBox->yIndex != target->currentBox->yIndex)
			{
				//We check target position compared to player on Y
				if (currentBox->yIndex > target->currentBox->yIndex)
				{
					newBoxY--;
				}
				else if (currentBox->yIndex < target->currentBox->yIndex)
				{
					newBoxY++;
				}
			}

			//If the new
			if (newBoxX >= 0 && newBoxX < battlefieldGrid->xLength && newBoxY >= 0 && newBoxY < battlefieldGrid->yLength)
			{
				int index = battlefieldGrid->GetBoxIndexByLocation(newBoxX, newBoxY);
				auto newBox = battlefieldGrid->grids[index];

				if (!newBox->GetOccupied())
				{
					currentBox->SetOccupy(false, ' ');
					currentBox = newBox;
					currentBox->SetOccupy(true, Icon);
					battlefieldGrid->drawBattlefield();
				}
			}
		}
	}
	else
	{
		printf("Target does not exist! Game is over!");
	}
	return;
}

bool Character::CheckCloseTargets(std::shared_ptr<Grid> battlefield, int range)
{
	std::shared_ptr<Types::GridBox> targetBox = target->currentBox;
	int distance = abs(targetBox->xIndex - currentBox->xIndex) + abs(targetBox->yIndex - currentBox->yIndex); //Get the distance between character and its target
	return distance <= range; //If distance is within range it returns true
}

void Character::Attack(std::shared_ptr<Character> target)
{
	target->TakeDamage(BaseDamage * DamageMultiplier);
	printf("Player %c Attacked player %c\n", Icon, target->Icon);
}

void Character::SetTarget(const std::shared_ptr<Character>& target)
{
	this->target = target;
}

