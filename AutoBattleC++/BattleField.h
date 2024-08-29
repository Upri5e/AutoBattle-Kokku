#ifndef BATTLEFIELD_H
#define	BATTLEFIELD_H

#include "Character.h"
#include "Types.h"
#include <vector>
#include <iostream>
#include "Grid.h"
#include "Events.h"

class BattleField
{
private:

	std::shared_ptr<Events> eventsSystem;

	int currentTurn;
	int numberOfPossibleTiles;

	//Characters Setup
	int maxTeamsCount;
	int charactersPerTeam;
	std::vector<std::shared_ptr<Character>> AllPlayers; //We are using shared ptr now for all characters
	std::vector<std::shared_ptr<Types::Team>> Teams;

	void OnCharacterDeath(const std::shared_ptr<Character>& character);

	void RemoveTeam(std::shared_ptr<Types::Team> team);

	void RemoveTeamMember(std::shared_ptr<Character> member);

public:

	BattleField();

	std::shared_ptr<Grid> grid;

	void Setup();

	void GetPlayerChoice();

	void CreateGameCharacters(int playerClassIndex);

	void StartGame();

	void PlayTurn();

	void HandleTurn();

	int GetRandomInt(int min, int max);

	void EndGame();
};
#endif // !BATTLEFIELD_H

