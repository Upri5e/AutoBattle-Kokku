#pragma once
#include "Character.h"
#include "Types.h"
#include <vector>
#include <iostream>
#include "Grid.h"

class BattleField
{
public:

	BattleField();

	std::shared_ptr<Grid> grid;
	//std::shared_ptr<Types::GridBox> PlayerCurrentLocation;
	//std::shared_ptr<Types::GridBox> EnemyCurrentLocation;
	std::vector<std::shared_ptr<Character>> AllPlayers; //We are using shared ptr now for all characters
	int currentTurn;
	int numberOfPossibleTiles;
	int maxTeamsCount;

	//Teams Setup
	int charactersPerTeam;

	std::vector<std::shared_ptr<Types::Team>> Teams;

	void Setup();

	void GetPlayerChoice();

	void CreateGameCharacters(int playerClassIndex);

	void StartGame();

	void StartTurn();

	void HandleTurn();

	int GetRandomInt(int min, int max);

	void EndGame();

	void RemoveTeam(std::shared_ptr<Types::Team> team);

	void RemoveTeamMember(std::shared_ptr<Character> member);

	void NotifyCharacterDied(const std::shared_ptr<Character>& character);
};


