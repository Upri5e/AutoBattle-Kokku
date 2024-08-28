#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include <iostream>
#include <list>
#include <string>

//using namespace std; Bad practice

BattleField::BattleField() {

	//AllPlayers = new list<Character>(); No need to initialize
	currentTurn = 0;
	numberOfPossibleTiles = 0;
	srand(time(NULL)); //Seed random number generator

	//TODO: Add restriction to number based on grid size
	//Can be changed to allow user input
	charactersPerTeam = 2;
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
//Get user input to choose a class and create the characters
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
		//After locking in the choice start creating characters
		CreateGameCharacters(choice);
		return;
	}
}

void BattleField::CreateGameCharacters(int playerClassIndex)
{
	bool playerCreated = false;

	//Create the gridbox cache for available locations to filter out the occupied ones
	std::vector<std::shared_ptr<Types::GridBox>> availableLocations = grid->grids;
	//TODO:changed to take user input for number of teams instead
	// Loop through the 2 teams
	for (int i = 0; i < 2; i++)
	{
		Teams.emplace_back(std::make_shared<Types::Team>(i, '0' + i + 1)); //Team icon set based on index
		for (int j = 0; j < charactersPerTeam; j++)
		{
			int currentIndex = i * charactersPerTeam + j;
			std::shared_ptr<Character> currentMember;
			//First we create the player character
			if (!playerCreated)
			{
				//Cast the chosen index to the character class enum
				Types::CharacterClass characterClass = static_cast<Types::CharacterClass>(playerClassIndex);
				printf("Player Class Choice: %s\n", Types::GetCharacterClassName(characterClass));
				std::string playerIcon = "A"; //Player icon is always A
				currentMember = std::make_shared<Character>(characterClass, currentIndex, this, playerIcon);
				Teams[i]->AddMember(currentMember);
				currentMember->teamIndex = i;
				printf("Player %s created!\n", currentMember->Icon.c_str());
				playerCreated = true;
			}
			else
			{
				int randomInteger = GetRandomInt(1, 4);
				Types::CharacterClass botClass = static_cast<Types::CharacterClass>(randomInteger); //Safer casting with static to ensure value is not out of range
				printf("Enemy Class Choice: %s\n", Types::GetCharacterClassName(botClass));
				std::string memberIcon = std::string(1, Teams[i]->teamIcon) + char('A' + i * charactersPerTeam + j); // Members icon is the team icon + next letter
				currentMember = std::make_shared<Character>(botClass, currentIndex, this, memberIcon);
				Teams[i]->AddMember(currentMember);
				currentMember->teamIndex = i;
			}
			//Check if there are no more locations available
			if (availableLocations.empty())
			{
				printf("No available locations left for character %s!\n", currentMember->Icon.c_str());
				RemoveTeamMember(currentMember);
				continue;
			}

			//Get a random location from the cached vector and remove it after assigning to character
			int random = GetRandomInt(0, availableLocations.size() - 1);
			std::shared_ptr<Types::GridBox> RandomLocation = availableLocations[random];
			RandomLocation->SetOccupy(true, currentMember->Icon);
			currentMember->currentBox = RandomLocation;
			availableLocations.erase(availableLocations.begin() + random);
			AllPlayers.push_back(currentMember);
		}
	}

	StartGame();
}

void BattleField::StartGame()
{
	for (int i = 0; i < Teams.size(); i++)
	{
		int enemyTeamIndex = (i + 1) % Teams.size();
		for (auto member : Teams[i]->TeamMembers)
		{
			if (member->GetTarget())
				continue;
			member->SetNearestTarget(Teams[enemyTeamIndex]->TeamMembers, grid);
		}
	}
	printf("Game Started...Have Fun!\n");
	grid->drawBattlefield();
	StartTurn();
}

void BattleField::StartTurn() {
	printf("\n");
	printf("Turn #%d\n", currentTurn);

	//Iterate through players
	for (auto i = AllPlayers.begin(); i != AllPlayers.end();)
	{
		auto player = (*i);
		if (player->IsDead)
		{
			i = AllPlayers.erase(i);
			continue;
		}
		player->PlayTurn(grid);
		i++;
	}
	//Handle end of turn checks
	HandleTurn();
}


void BattleField::HandleTurn()
{
	if (Teams.size() <= 1) //If there is only 1 player or less left, game ends
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
	if (Teams.size() > 0)
		printf("Team %c Won!\n", Teams.front()->teamIcon);
	else
		printf("Game Over!\n");
	AllPlayers.clear();
	Teams.clear();
}
void BattleField::RemoveTeam(std::shared_ptr<Types::Team> team)
{
	auto i = std::find(Teams.begin(), Teams.end(), team);
	if (i != Teams.end())
	{
		Teams.erase(i);
	}
}
void BattleField::RemoveTeamMember(std::shared_ptr<Character> member)
{
	Teams[member->teamIndex]->RemoveMember(member);
	//Check if team is empty after removing member
	if (Teams[member->teamIndex]->TeamMembers.size() == 0)
		RemoveTeam(Teams[member->teamIndex]);
}
void BattleField::NotifyCharacterDied(const std::shared_ptr<Character>& character)
{
	auto i = std::find(AllPlayers.begin(), AllPlayers.end(), character);
	if (i != AllPlayers.end())
	{
		auto characterToRemove = *i;
		RemoveTeamMember(characterToRemove);
	}
	grid->drawBattlefield();
}
int BattleField::GetRandomInt(int min, int max)
{
	int range = max - min + 1; //Get the range with max included
	int index = rand() % range + min;
	printf("Rand: %d\n", index);
	return index;
}



