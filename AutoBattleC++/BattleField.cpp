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
			printf("Invalid input. Please enter a number greater than 0.\n");
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
			printf("Invalid input. Please enter a number greater than 0.\n");
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
	PlayerCharacter = std::make_shared<Character>(characterClass);

	//TODO: make dynamic to class type and players count
	PlayerCharacter->Health = 100;
	PlayerCharacter->BaseDamage = 20;
	PlayerCharacter->PlayerIndex = 0;//TODO: take from Allplayers last index

	CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
	//randomly choose the enemy class and set up vital variables
	int randomInteger = GetRandomInt(1, 4);
	Types::CharacterClass enemyClass = static_cast<Types::CharacterClass>(randomInteger); //Safer casting with static to ensure value is not out of range
	printf("Enemy Class Choice: %s\n", Types::GetCharacterClassName(enemyClass));
	EnemyCharacter = std::make_shared<Character>(enemyClass); //Create enemy character with chosen character class

	//TODO: make dynamic to class type 
	EnemyCharacter->Health = 100;
	EnemyCharacter->BaseDamage = 20;
	EnemyCharacter->PlayerIndex = 1; //TODO: take from Allplayers last index
	StartGame();
}

void BattleField::StartGame()
{
	//populates the character variables and targets
	EnemyCharacter->SetTarget(PlayerCharacter);
	PlayerCharacter->SetTarget(EnemyCharacter);
	AllPlayers.push_back(PlayerCharacter);
	AllPlayers.push_back(EnemyCharacter);
	AlocatePlayers();
	//StartTurn();
}

void BattleField::StartTurn() {

	if (currentTurn == 0)
	{
		//AllPlayers.Sort();  
	}
	std::list<std::shared_ptr<Character>>::iterator it;

	for (it = AllPlayers.begin(); it != AllPlayers.end(); ++it) {
		(*it)->StartTurn(grid);
	}

	currentTurn++;
	HandleTurn();
}

void BattleField::HandleTurn()
{
	if (PlayerCharacter->Health == 0)
	{
		return;
	}
	else if (EnemyCharacter->Health == 0)
	{
		printf("\n");

		// endgame?

		printf("\n");

		return;
	}
	else
	{
		printf("\n");
		printf("Click on any key to start the next turn...\n");
		printf("\n");

		//TODO
		//ConsoleKeyInfo key = Console.ReadKey();
		StartTurn();
	}
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

	if (!RandomLocation->ocupied)
	{
		//Types::GridBox* PlayerCurrentLocation = RandomLocation;
		RandomLocation->ocupied = true;
		PlayerCharacter->currentBox = RandomLocation;
		printf("Player grid location: X= %d, Y= %d\n", RandomLocation->xIndex, RandomLocation->yIndex);
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

	if (!RandomLocation->ocupied)
	{
		RandomLocation->ocupied = true;
		EnemyCharacter->currentBox = RandomLocation;
		printf("Enemy grid location: X= %d, Y= %d\n", RandomLocation->xIndex, RandomLocation->yIndex);
		grid->drawBattlefield();
	}
	else
	{
		AlocateEnemyCharacter();
	}
}