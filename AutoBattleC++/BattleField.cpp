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

	grid = std::make_shared<Grid>(5, 5);
	//AllPlayers = new list<Character>(); No need to initialize
	currentTurn = 0;
	numberOfPossibleTiles = grid->grids.size();
	//Setup();
}

void BattleField::Setup()
{

	GetPlayerChoice();
}

void BattleField::GetPlayerChoice()
{
	int choice = 0;
	while (true) //Keep looping till player inputs a correct choice
	{
		//asks for the player to choose between four possible classes via console.
		printf("Choose Between One of these Classes:\n");

		printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");

		choice = 0;
		//std::getline(std::cin, choice);
		std::cin >> choice;
		if (std::cin.fail())
		{
			//Clear cin error flag
			std::cin.clear();
			//Ignore rest of invalid input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("Invalid input. Please enter a number between 1 and 4.\n");
		}
		else
		{
			if (choice >= 1 && choice <= 4)
			{
				CreatePlayerCharacter(choice);
				return;
			}
			else {
				printf("%d is not a valid choice!\n", choice);
			}
		}
	}
}

void BattleField::CreatePlayerCharacter(int classIndex)
{

	Types::CharacterClass characterClass = static_cast<Types::CharacterClass>(classIndex);
	printf("Player Class Choice: %s\n", Types::GetCharacterClassName(characterClass));

	PlayerCharacter = std::make_shared<Character>(characterClass);

	PlayerCharacter->Health = 100;
	PlayerCharacter->BaseDamage = 20;
	PlayerCharacter->PlayerIndex = 0;

	CreateEnemyCharacter();

}

void BattleField::CreateEnemyCharacter()
{
	//randomly choose the enemy class and set up vital variables

	int randomInteger = GetRandomInt(1, 4);
	Types::CharacterClass enemyClass = static_cast<Types::CharacterClass>(randomInteger); //Safer casting with static to ensure value is not out of range
	printf("Enemy Class Choice: %s\n", Types::GetCharacterClassName(enemyClass));
	EnemyCharacter = std::make_shared<Character>(enemyClass); //Correct way to make a shared ptr
	EnemyCharacter->Health = 100;
	PlayerCharacter->BaseDamage = 20;
	PlayerCharacter->PlayerIndex = 1;
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
	StartTurn();
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
	srand(time(NULL)); //Generate rand seed
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
	auto l_front = grid->grids.begin();
	std::advance(l_front, random);
	std::shared_ptr<Types::GridBox> RandomLocation = *l_front;

	if (!RandomLocation->ocupied)
	{
		//Types::GridBox* PlayerCurrentLocation = RandomLocation;
		RandomLocation->ocupied = true;
		PlayerCharacter->currentBox = RandomLocation;
		AlocateEnemyCharacter();
	}
	else
	{
		AlocatePlayerCharacter();
	}
}

void BattleField::AlocateEnemyCharacter()
{

	int random = 24;
	auto l_front = grid->grids.begin();
	advance(l_front, random);
	std::shared_ptr<Types::GridBox> RandomLocation = *l_front;

	if (!RandomLocation->ocupied)
	{
		RandomLocation->ocupied = true;
		EnemyCharacter->currentBox = RandomLocation;
		grid->drawBattlefield(5, 5);
	}
	else
	{
		AlocateEnemyCharacter();
	}


}