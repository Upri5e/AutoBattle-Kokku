#pragma once
#include "Character.h"
#include "Types.h"
#include <list>
#include <iostream>
#include "Grid.h"

class BattleField
{
public:

	BattleField();

	std::shared_ptr<Grid> grid;
	//std::shared_ptr<Types::GridBox> PlayerCurrentLocation;
	//std::shared_ptr<Types::GridBox> EnemyCurrentLocation;
	std::list<std::shared_ptr<Character>> AllPlayers; //We are using shared ptr now for all characters
	std::shared_ptr<Character> PlayerCharacter;
	//Character* PlayerCharacter;
	std::shared_ptr<Character> EnemyCharacter; //Declaring shared ptr does not need *
	int currentTurn;
	int numberOfPossibleTiles;


	void Setup();

	void GetPlayerChoice();

	void CreatePlayerCharacter(int classIndex);

	void CreateEnemyCharacter();

	void StartGame();

	void StartTurn();

	void HandleTurn();

	int GetRandomInt(int min, int max);

	void AlocatePlayers();

	void AlocatePlayerCharacter();

	void AlocateEnemyCharacter();
};


