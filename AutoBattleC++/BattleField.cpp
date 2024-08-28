#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include "BattleField.h"
#include <list>
#include <string>

//using namespace std; Bad practice

BattleField::BattleField() {

	//AllPlayers = new list<Character>(); No need to initialize
	currentTurn = 0;
	numberOfPossibleTiles = 0;
	srand(time(NULL)); //Seed random number generator

	//Setup();
}

void BattleField::Setup()
{
	//Setup battlefield grid width and height from player input
	int width, height = 0;
	while (true) //Keep looping till player inputs a correct choice
	{
		printf("Enter the battlefield width:\n");

		std::cin >> width;
		if (std::cin.fail() || width <= 0)
		{
			//Clear cin error flag
			std::cin.clear();
			//Ignore rest of invalid input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("Please enter a number greater than 0.\n");
			continue;
		}

		printf("Enter the battlefield height:\n");
		std::cin >> height;
		if (std::cin.fail() || height <= 0)
		{
			//Clear cin error flag
			std::cin.clear();
			//Ignore rest of invalid input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("Please enter a number greater than 0.\n");
			continue;
		}

		//Do not allow grid of 1 x 1 since it results in 1 box
		if (width == 1 && height == 1)
		{
			printf("Battlefield cannot be 1x1. Please enter larger dimensions.\n");
			continue;
		}
		grid = std::make_shared<Grid>(width, height);
		numberOfPossibleTiles = grid->grids.size();
		break;
	}
	printf("Battlefield of %d X %d created\n", width, height);
	GetPlayerChoice();
}

void BattleField::GetPlayerChoice()
{
	int choice = 0;
	while (true) //Keep looping till player inputs a correct choice
	{
		//asks for the player to choose between four possible classes via console.
		printf("Choose Between One of these Classes:\n");
		//TODO: Make more dynamic if we added different classes in the future
		printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");

		std::cin >> choice;
		if (std::cin.fail() || choice < 1 || choice > 4)
		{
			//Clear cin error flag
			std::cin.clear();
			//Ignore rest of invalid input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("Invalid input. Please enter a number between 1 and 4.\n");
			continue;
		}

		CreatePlayerCharacter(choice);
		return;
	}
}

void BattleField::CreatePlayerCharacter(int classIndex)
{
	//Cast the chosen index to the character class enum
	Types::CharacterClass characterClass = static_cast<Types::CharacterClass>(classIndex);
	printf("Player Class Choice: %s\n", Types::GetCharacterClassName(characterClass));

	//Create player character with chosen character class
	PlayerCharacter = std::make_shared<Character>(characterClass, AllPlayers.size());
	PlayerCharacter->Icon = 'A';
	AllPlayers.push_back(PlayerCharacter);
	printf("Player %c created!\n", PlayerCharacter->Icon);

	//TODO setup based on class in character itself
	//PlayerCharacter->Health = 100;
	//PlayerCharacter->BaseDamage = 20;
	//PlayerCharacter->PlayerIndex = 0; Handled on character creation

	CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
	//randomly choose the enemy class and set up vital variables
	int randomInteger = GetRandomInt(1, 4);
	Types::CharacterClass enemyClass = static_cast<Types::CharacterClass>(randomInteger); //Safer casting with static to ensure value is not out of range
	printf("Enemy Class Choice: %s\n", Types::GetCharacterClassName(enemyClass));
	EnemyCharacter = std::make_shared<Character>(enemyClass, AllPlayers.size()); //Create enemy character with chosen character class
	AllPlayers.push_back(EnemyCharacter);
	printf("Player %d created!\n", EnemyCharacter->PlayerIndex);

	StartGame();
}

void BattleField::StartGame()
{
	//populates the character variables and targets
	EnemyCharacter->SetTarget(PlayerCharacter);
	PlayerCharacter->SetTarget(EnemyCharacter);
	AlocatePlayers();
	StartTurn();
}

void BattleField::StartTurn() {
	printf("\n");
	printf("Turn #%d\n", currentTurn);
	//Iterate through players
	for (auto i = AllPlayers.begin(); i != AllPlayers.end();)
	{
		auto player = (*i);
		//Check if player is dead, remove it from the list
		if (player->IsDead)
		{
			i = AllPlayers.erase(i); //Remove player if dead
			break;
		}
		player->StartTurn(grid);
		i++;
	}
	//Handle end of turn checks
	HandleTurn();
}

void BattleField::HandleTurn()
{
	if (AllPlayers.size() <= 1) //If there is only 1 player or less left, game ends
	{
		EndGame();
	}
	else //Otherwise play next turn
	{
		printf("Click on any key for next turn...\n");
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cin.get();

		//Next turn starts
		currentTurn++;
		StartTurn();
	}
}

void BattleField::EndGame()
{
	if (AllPlayers.size() > 0)
		printf("Player %d Won!", AllPlayers.front()->PlayerIndex);
	else
		printf("Game Over!");
	AllPlayers.clear();
	EnemyCharacter.reset();
	PlayerCharacter.reset();
}
int BattleField::GetRandomInt(int min, int max)
{
	int range = max - min + 1; //Get the range with max included
	int index = rand() % range + min;
	printf("Rand: %d\n", index);
	return index;
}

void BattleField::AlocatePlayers()
{
	AlocatePlayerCharacter();

}

void BattleField::AlocatePlayerCharacter()
{
	int random = GetRandomInt(0, grid->grids.size() - 1);
	std::shared_ptr<Types::GridBox> RandomLocation = grid->grids[random];

	if (!RandomLocation->GetOccupied())
	{
		//Types::GridBox* PlayerCurrentLocation = RandomLocation;
		RandomLocation->SetOccupy(true, PlayerCharacter->Icon);
		PlayerCharacter->currentBox = RandomLocation; //Set player box location
		printf("Player %c grid location: X= %d, Y= %d\n", PlayerCharacter->Icon, PlayerCharacter->currentBox->xIndex, PlayerCharacter->currentBox->yIndex);
		AlocateEnemyCharacter();
	}
	else
	{
		AlocatePlayerCharacter();
	}
}

void BattleField::AlocateEnemyCharacter()
{

	int random = GetRandomInt(0, grid->grids.size() - 1);
	std::shared_ptr<Types::GridBox> RandomLocation = grid->grids[random];

	if (!RandomLocation->GetOccupied())
	{
		RandomLocation->SetOccupy(true, EnemyCharacter->Icon);
		EnemyCharacter->currentBox = RandomLocation;//Set enemy box location
		printf("Player %c grid location: X= %d, Y= %d\n",EnemyCharacter->Icon, RandomLocation->xIndex, RandomLocation->yIndex);
		grid->drawBattlefield();
	}
	else
	{
		AlocateEnemyCharacter();
	}
}


