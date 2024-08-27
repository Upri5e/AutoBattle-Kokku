#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <vector>
#include <algorithm>

//using namespace std;

Character::Character(Types::CharacterClass charcaterClass, int index) : PlayerIndex(index), Health(100), BaseDamage(50), DamageMultiplier(1), Icon(' '), IsDead(false)
{
}

Character::~Character()
{

}

bool Character::TakeDamage(float amount)
{
	if ((Health -= amount) <= 0)
	{
		Die();
		return true;
	}
	return false;
}

int Character::getIndex(std::vector<Types::GridBox*> v, int index)
{
	return 0;
}

void Character::Die()
{
	// TODO >> kill
	IsDead = true;
	//TODO >> end the game?
}

void Character::WalkTo(bool CanWalk)
{

}



void Character::StartTurn(std::shared_ptr<Grid> battlefield) {
	printf("Player %d turn\n", PlayerIndex);
	if (target && !target->IsDead)
	{
		if (CheckCloseTargets(battlefield, 1))
		{
			Attack(target);
			return;
		}
		else
		{   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target


			if (currentBox->xIndex > target->currentBox->xIndex)
			{
				auto currentIndex = currentBox->xIndex;
				auto foundBox = std::find_if(battlefield->grids.begin(), battlefield->grids.end(), [&currentIndex](const std::shared_ptr<Types::GridBox>& Box) {
					return Box->xIndex == currentIndex - 1;
					});
				if (foundBox != battlefield->grids.end())
				{
					currentBox->ocupied = false;
					battlefield->grids[currentBox->Index] = currentBox;

					currentBox = (battlefield->grids[currentBox->Index - 1]);
					currentBox->ocupied = true;
					battlefield->grids[currentBox->Index] = currentBox;
					//Console.WriteLine($"Player {PlayerIndex} walked left\n");
					battlefield->drawBattlefield();

					return;
				}
			}
			else if (currentBox->xIndex < target->currentBox->xIndex)
			{
				currentBox->ocupied = false;
				battlefield->grids[currentBox->Index] = currentBox;
				currentBox = (battlefield->grids[currentBox->Index + 1]);
				return;
				battlefield->grids[currentBox->Index] = currentBox;
				//Console.WriteLine($"Player {PlayerIndex} walked right\n");
				battlefield->drawBattlefield();
			}

			if (currentBox->yIndex > target->currentBox->yIndex)
			{
				battlefield->drawBattlefield();
				currentBox->ocupied = false;
				battlefield->grids[currentBox->Index] = currentBox;
				currentBox = battlefield->grids[(currentBox->Index - battlefield->xLenght)];
				currentBox->ocupied = true;
				battlefield->grids[currentBox->Index] = currentBox;
				//Console.WriteLine($"PlayerB {PlayerIndex} walked up\n");
				return;
			}
			else if (currentBox->yIndex < target->currentBox->yIndex)
			{
				currentBox->ocupied = true;
				battlefield->grids[currentBox->Index] = currentBox;
				currentBox = battlefield->grids[currentBox->Index + battlefield->xLenght];
				currentBox->ocupied = false;
				battlefield->grids[currentBox->Index] = currentBox;
				//Console.WriteLine($"Player {PlayerIndex} walked down\n");
				battlefield->drawBattlefield();

				return;
			}
		}
	}
	//TODO: Call end of the game
	return;
}

bool Character::CheckCloseTargets(std::shared_ptr<Grid> battlefield, int range)
{
	std::shared_ptr<Types::GridBox> targetBox = target->currentBox;
	int distance = abs(targetBox->xIndex - currentBox->xIndex) + abs(targetBox->yIndex - currentBox->yIndex);
	return distance <= range;
}

void Character::Attack(std::shared_ptr<Character> target)
{
	target->TakeDamage(BaseDamage * DamageMultiplier);
	printf("Player %d Attacked player %d\n", PlayerIndex, target->PlayerIndex);
}

void Character::SetTarget(const std::shared_ptr<Character>& target)
{
	this->target = target;
}

