#pragma once
#include <String>
class Types
{
public:

    struct GridBox
    {
    private:
        bool ocupied;

    public:
        char icon;
        int xIndex;
        int yIndex;
        int Index;


        GridBox() : xIndex(0), yIndex(0), ocupied(false), Index(0), icon(' ') //Default Cstr        
        {

        }

        GridBox(int x, int y, bool ocupied, int index)
        {
            xIndex = x;
            yIndex = y;
            this->ocupied = ocupied; //Use this to make sure we are setting the structs variable as the value of the param
            Index = index;
            icon = ' ';
        }

        void SetOccupy(bool status, char icon)
        {
            ocupied = status;
            this->icon = icon;
        }
        bool GetOccupied() {
            return ocupied;
        }
    };

    enum CharacterClass
    {
        Paladin = 1,
        Warrior = 2,
        Cleric = 3,
        Archer = 4
    };

    static const char* GetCharacterClassName(CharacterClass characterClass)
    {
        switch (characterClass)
        {
        case Types::Paladin:
            return "Paladin";
        case Types::Warrior:
            return "Warrior";
        case Types::Cleric:
            return "Cleric";
        case Types::Archer:
            return "Archer";
        default:
            return "Invalid Class";
        }
    }
};

