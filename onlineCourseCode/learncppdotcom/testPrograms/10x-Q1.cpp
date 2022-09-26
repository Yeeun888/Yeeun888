#include <iostream>
#include <string>

enum MonstersType {
    Orge,
    Dragon,
    Orc,
    GiantSpider,
    Slime, 
};

struct Monster {
    MonstersType monsType{};
    std::string name{};
    int health{};
};


std::string& returnMonsterString(MonstersType mType) {
    switch(mType) {
        case Orge:
            static std::string oString{ "Orge" };
            return oString;
        case Dragon:
            static std::string dString{ "Dragon"};
            return dString;
        case Orc: 
            static std::string orString{ "Orc" };
            return orString;
        case GiantSpider:
            static std::string ogString{ "Orge" };
            return ogString;
        case Slime:
            static std::string sString{ "Slime"};
            return sString;
    }
}

void printMonster(Monster pmon) {

    std::cout << "This " << returnMonsterString(pmon.monsType) << " is named" <<
    pmon.name << " and has " << pmon.health << " health.\n";
}

int main() {
    Monster mons1{Orge, "Torg", 145};

    printMonster(mons1);
    return 0;
}