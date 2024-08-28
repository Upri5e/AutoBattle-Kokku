#pragma once
#include <string>
#include <memory>
#include <vector>

class Character;

class Types
{
public:
    struct GridBox
    {
    private:
        bool ocupied;

    public:

        std::string icon;
        int xIndex;
        int yIndex;
        int Index;

        GridBox(int x, int y, bool ocupied, int index)
        {
            xIndex = x;
            yIndex = y;
            this->ocupied = ocupied; // Use this to make sure we are setting the struct's variable
            Index = index;
            icon = " ";
        }

        void SetOccupy(bool status, std::string icon)
        {
            ocupied = status;
            this->icon = icon;
        }

        bool GetOccupied() const {
            return ocupied;
        }
    };

    struct Team
    {
        int teamIndex;
        char teamIcon;
        std::vector<std::shared_ptr<Character>> TeamMembers;

        Team(int index, char icon) :
            teamIndex(index), teamIcon(icon)
        {
        }

        void AddMember(std::shared_ptr<Character> newMember)
        {
            TeamMembers.push_back(newMember);
        }
        
        void RemoveMember(std::shared_ptr<Character> member)
        {
            //iterate through to find the team member then remove it
            auto i = std::find(TeamMembers.begin(), TeamMembers.end(), member);
            if (i != TeamMembers.end())
                TeamMembers.erase(i);
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
        case Paladin:
            return "Paladin";
        case Warrior:
            return "Warrior";
        case Cleric:
            return "Cleric";
        case Archer:
            return "Archer";
        default:
            return "Invalid Class";
        }
    }
};