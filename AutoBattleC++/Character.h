#ifndef CHARACTER_H
#define CHARACTER_H

#include <memory>
#include <vector>
#include "Types.h"
#include "Grid.h"
#include <string>
#include "Events.h"

class AbilityComponent;

//Inherit from enable shared from this to allow creating a temporary shared ptr from the weak ptr when we want to notify battlefield on death
class Character : public std::enable_shared_from_this<Character>
{
public:

    Character(Types::CharacterClass charcaterClass, int index, std::shared_ptr<Grid> bfieldGrid, std::string icon = "X");
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

    virtual void PlayTurn();

    bool CheckCloseTargets(int range);

    virtual void Attack();

    bool SetNearestTarget(const std::vector<std::shared_ptr<Character>>& potentialTargets);

    std::shared_ptr<Character> GetTarget();

    int GetDistanceToTarget(const Character& target);

    void SetEventsSystem(std::shared_ptr<Events> EventsSystem);

private:
    float MaxHealth;
    std::shared_ptr<Events> eventsSystem;

protected:
    std::shared_ptr<Grid> battleFieldGrid;
    std::unique_ptr<AbilityComponent> Ability;
    std::shared_ptr<Character> target;

};
#endif // !CHARACTER_H
