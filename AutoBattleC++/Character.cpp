#include "Character.h"
#include <math.h>
//using namespace std;

Character::Character(Types::CharacterClass charClass, int index, BattleField* battlefield, std::string icon)
	: PlayerIndex(index), MaxHealth(100), BaseDamage(50), DamageMultiplier(1), Icon(icon), IsDead(false), AttackRange(1), battleField(battlefield)
{
	CurrentHealth = MaxHealth;
}

Character::~Character()
{

}

//Apply damage calculation to health and check for death
void Character::TakeDamage(float amount)
{
	//Check if damage kills character
	if ((CurrentHealth -= amount) <= 0)
	{
		Die();
		return;
	}
	printf("Player %s health: %f\n", Icon.c_str(), CurrentHealth);
}


//When character dies reset values and notify battlefield
void Character::Die()
{
	CurrentHealth = 0;
	IsDead = true;
	currentBox->SetOccupy(false, " ");

	printf("Player %s died!\n", Icon.c_str());
	if (battleField != nullptr)
		battleField->NotifyCharacterDied(shared_from_this()); //Pass this character as shared ptr
}


//character plays there turn
//Check if their target is in range, they attack
//If not they move towards their target
void Character::PlayTurn(std::shared_ptr<Grid> battlefieldGrid) {
	if (target && !target->IsDead)
	{
		printf("Player %s turn\n", Icon.c_str());
		if (CheckCloseTargets(battlefieldGrid, AttackRange)) //If target is within range, character attacks
		{
			Attack(target);
			return;
		}
		else
		{   
			// if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
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

			if (currentBox->yIndex != target->currentBox->yIndex)
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

			if (newBoxX >= 0 && newBoxX < battlefieldGrid->xLength && newBoxY >= 0 && newBoxY < battlefieldGrid->yLength)
			{
				//Get index of next horizontal and vertical boxes to character => towards its target
				int horizontalBoxIndex = battlefieldGrid->GetBoxIndexByLocation(newBoxX, currentBox->yIndex);
				int verticalBoxIndex = battlefieldGrid->GetBoxIndexByLocation(currentBox->xIndex, newBoxY);

				//Set the index based on whether first box is occupied or not
				int resultBoxIndex = battlefieldGrid->grids[horizontalBoxIndex]->GetOccupied() ? verticalBoxIndex : horizontalBoxIndex;

				auto newBox = battlefieldGrid->grids[resultBoxIndex];

				//Check if the chosen box is not occupied so character can occupy it
				if (!newBox->GetOccupied())
				{
					currentBox->SetOccupy(false, " ");
					currentBox = newBox;
					currentBox->SetOccupy(true, Icon);
					battlefieldGrid->drawBattlefield();
				}
			}
		}
	}
	else 
	{
		//Go through available teams and get the nearest target from one of them
		for (auto team : battleField->Teams)
		{
			if (team->teamIndex == teamIndex)
				continue;
			if (SetNearestTarget(team->TeamMembers, battlefieldGrid))
			{
				PlayTurn(battlefieldGrid); //play the turn again after assigning a nerw target				
				return;
			}
		}
		//printf("Should not reach this");
	}
}

bool Character::CheckCloseTargets(std::shared_ptr<Grid> battlefield, int range)
{
	std::shared_ptr<Types::GridBox> targetBox = target->currentBox;
	int distance = sqrt((targetBox->xIndex - currentBox->xIndex) * (targetBox->xIndex - currentBox->xIndex) + (targetBox->yIndex - currentBox->yIndex) * (targetBox->yIndex - currentBox->yIndex)); //Get the distance between character and its target
	return distance <= range; //If distance is within range it returns true
}

void Character::Attack(std::shared_ptr<Character> target)
{
	printf("Player %s Attacked player %s\n", Icon.c_str(), target->Icon.c_str());
	target->TakeDamage(BaseDamage * DamageMultiplier);
}

bool Character::SetNearestTarget(const std::vector<std::shared_ptr<Character>>& potentialTargets, const std::shared_ptr<Grid>& battlefieldGrid)
{
	//Search for a target around an expanding radius
	std::shared_ptr<Character> nearestTarget = nullptr;
	int maxRadius = sqrt((battlefieldGrid->xLength * battlefieldGrid->xLength) + (battlefieldGrid->yLength * battlefieldGrid->yLength));
	int closestDistance = maxRadius;
	
	for (int radius = 1; radius <= maxRadius; radius++) //Increase radius with every iteration
	{
		for (auto Target : potentialTargets)//iterate through potential target and get the distance to character
		{
			if (Target->teamIndex == teamIndex)
				continue;

			int thisDistance = GetDistanceToTarget(*Target);
			if (thisDistance <= radius && thisDistance < closestDistance)
			{
				closestDistance = thisDistance;
				nearestTarget = Target;
			}
		}
		if (nearestTarget && nearestTarget != target) //If the nearest target is set after going through all targets, we break
		{
			target = nearestTarget;
			break;
		}//otherwise we extend the radius
	}
	if (nearestTarget == nullptr)
	{
		printf("There are no more targets\n");
		return false;
	}
	printf("Player %s assigned target: %s\n", Icon.c_str(), nearestTarget->Icon.c_str());
	return true;
}

std::shared_ptr<Character> Character::GetTarget()
{
	return target;
}


int Character::GetDistanceToTarget(const Character& target)
{
	std::shared_ptr<Types::GridBox> targetBox = target.currentBox;
	return sqrt((targetBox->xIndex - currentBox->xIndex) * (targetBox->yIndex - currentBox->yIndex));
}

