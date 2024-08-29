#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <vector>
#include "Types.h"
#include "Grid.h"
#include <string>
#include "BattleField.h"
#include "Events.h"

class BattleField;

//Inherit from enable shared from this to allow creating a temporary shared ptr from the weak ptr when we want to notify battlefield on death
class Character : public std::enable_shared_from_this<Character>
{
public:

    Character(Types::CharacterClass charcaterClass, int index, std::string icon = "X");
    ~Character();

    
    float CurrentHealth;
    float BaseDamage;
    float DamageMultiplier;
    float AttackRange;

    std::shared_ptr<Types::Team> currentTeam;

    int PlayerIndex;

    bool IsDead;
    std::string Icon;

    std::shared_ptr<Types::GridBox> currentBox;

    void TakeDamage(float amount);

    void Die();

    void PlayTurn(std::shared_ptr<Grid> battlefieldGrid);

    bool CheckCloseTargets(std::shared_ptr<Grid> battlefieldGrid, int range);

    void Attack(std::shared_ptr<Character> target);

    bool SetNearestTarget(const std::vector<std::shared_ptr<Character>>& potentialTargets, const std::shared_ptr<Grid>& battlefieldGrid);

    std::shared_ptr<Character> GetTarget();

    int GetDistanceToTarget(const Character& target);

    void SetEventsSystem(std::shared_ptr<Events> EventsSystem);
private:
    std::shared_ptr<Character> target; //Change to shared ptr to avoid memory leak
    float MaxHealth;
    std::shared_ptr<Events> eventsSystem;
};
#endif // !CHARACTER_H
