#include "Character.h"
#include <math.h>
//using namespace std;
#include "Abilities/AbilityComponent.h"

Character::Character(Types::CharacterClass charClass, int index, std::shared_ptr<Grid> bfieldGrid, std::string icon)
	: PlayerIndex(index), MaxHealth(100), BaseDamage(50), DamageMultiplier(1), Icon(icon), IsDead(false), AttackRange(1), battleFieldGrid(bfieldGrid)
{
	CurrentHealth = MaxHealth;
	canBeAttacked = true;
	canBeChased = true;
}

Character::~Character()
{

}

//Apply damage calculation to health and check for death (Can be used for healing by setting a negative amount)
void Character::TakeDamage(float amount)
{
	CurrentHealth -= amount;
	//Check if damage kills character
	if ((CurrentHealth) <= 0)
	{
		Die();
		return;
	}
	//Make sure if we are healing, it never exceeds maxhealth
	if (CurrentHealth > MaxHealth)
	{
		CurrentHealth = MaxHealth;
	}

	printf("Player %s health: %f\n", Icon.c_str(), CurrentHealth);

}

//When character dies reset values and call event
void Character::Die()
{
	CurrentHealth = 0;
	canBeAttacked = false;
	canBeChased = false;
	IsDead = true;
	currentBox->SetOccupy(false, " ");

	printf("Player %s died!\n", Icon.c_str());
	if (eventsSystem)
		eventsSystem->NotifyCharacterDeath(shared_from_this());
}

//character plays there turn
//Check if their target is in range, they attack
//If not they move towards their target

void Character::PlayTurn() {
	if (target && !target->IsDead && target->canBeChased)
	{
		printf("Player %s turn\n", Icon.c_str());
		if (CheckCloseTargets(AttackRange) && target->canBeAttacked) //If target is within range, character attacks
		{
			Attack();
			return;
		}

		Move();

	}
}

void Character::Move()
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

	if (newBoxX >= 0 && newBoxX < battleFieldGrid->xLength && newBoxY >= 0 && newBoxY < battleFieldGrid->yLength)
	{
		//TODO: Make them a little smarter, check for direction of target and move around blocked box in that direction
		//Get index of next horizontal and vertical boxes to character => towards its target
		int horizontalBoxIndex = battleFieldGrid->GetBoxIndexByLocation(newBoxX, currentBox->yIndex);
		int verticalBoxIndex = battleFieldGrid->GetBoxIndexByLocation(currentBox->xIndex, newBoxY);

		//Set the index based on whether first box is occupied or not
		int resultBoxIndex = battleFieldGrid->grids[horizontalBoxIndex]->GetOccupied() ? verticalBoxIndex : horizontalBoxIndex;

		auto newBox = battleFieldGrid->grids[resultBoxIndex];

		//Check if the chosen box is not occupied so character can occupy it
		if (!newBox->GetOccupied())
		{
			currentBox->SetOccupy(false, " ");
			currentBox = newBox;
			currentBox->SetOccupy(true, Icon);
			battleFieldGrid->drawBattlefield();
		}
	}
}
bool Character::CheckCloseTargets(int range)
{
	std::shared_ptr<Types::GridBox> targetBox = target->currentBox;
	//Get the distance between character and its target
	int distance = abs(targetBox->xIndex - currentBox->xIndex) + abs(targetBox->yIndex - currentBox->yIndex);
	return distance <= range; //If distance is within range it returns true
}

void Character::Attack()
{
	printf("Player %s Attacked player %s\n", Icon.c_str(), target->Icon.c_str());
	target->TakeDamage(BaseDamage * DamageMultiplier);
}

bool Character::SetNearestTarget(const std::vector<std::shared_ptr<Character>>& potentialTargets)
{
	//Search for a target around an expanding radius
	std::shared_ptr<Character> nearestTarget = nullptr;
	int maxRadius = sqrt((battleFieldGrid->xLength * battleFieldGrid->xLength) + (battleFieldGrid->yLength * battleFieldGrid->yLength));
	int closestDistance = maxRadius;

	for (int radius = 1; radius <= maxRadius; radius++) //Increase radius with every iteration
	{
		for (auto Target : potentialTargets)//iterate through potential target and get the distance to character
		{
			if (Target->currentTeam->teamIndex == currentTeam->teamIndex || !Target->canBeChased) //Add check for if target cant be chased
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

void Character::SetEventsSystem(std::shared_ptr<Events> EventsSystem)
{
	eventsSystem = EventsSystem;
}
