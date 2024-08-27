// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "BattleField.h"
#include <iostream>
#include <memory>

int main()
{
    std::unique_ptr<BattleField> battleField = std::make_unique<BattleField>();
    battleField->Setup();
}


