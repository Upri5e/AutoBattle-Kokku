#pragma once
#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include <memory>
#include <Vector>

class Character
{
public:

    Character(Types::CharacterClass charcaterClass, int index);
    ~Character();

    
    float Health;
    float BaseDamage;
    float DamageMultiplier;
    float AttackRange;
    //public GridBox currentBox;
    int PlayerIndex;
    //public Character Target{ get; set; }


    bool IsDead;
    char Icon;

    std::shared_ptr<Types::GridBox> currentBox;

    bool TakeDamage(float amount);

    //int getIndex(std::vector<Types::GridBox*> v, int index);

    void Die();

    //void WalkTo(bool CanWalk);

    void StartTurn(std::shared_ptr<Grid> battlefieldGrid);

    bool CheckCloseTargets(std::shared_ptr<Grid> battlefieldGrid, int range);

    void Attack(std::shared_ptr<Character> target);

    void SetTarget(const std::shared_ptr<Character>& target);

private:
    std::shared_ptr<Character> target; //Change to shared ptr to avoid memory leak

};

