//
// Created by romain on 15/09/2020.
//

#ifndef CPP_DUMP_TYPE_H
#define CPP_DUMP_TYPE_H

#include "../utils/CsvReader.h"

using namespace std;

enum Type {
    NEUTRAL,    // 0
    NORMAL,     // 1
    FIGHT,      // 2
    FLYING,     // 3
    POISON,     // 4
    GROUND,     // 5
    ROCK,       // 6
    BUG,        // 7
    GHOST,      // 8
    STEEL,      // 9
    FIRE,       // 10
    WATER,      // 11
    GRASS,      // 12
    ELECTRIC,   // 13
    PSY,        // 14
    ICE,        // 15
    DRAGON,     // 16
    DARK,       // 17
    FAIRY       // 18
};

inline string tToString(const Type &entry) {
    string result;
    switch (entry) {
        case NEUTRAL:
            result = "NEUTRAL";
            break;
        case NORMAL:
            result = "NORMAL";
            break;
        case FIGHT:
            result = "FIGHT";
            break;
        case FLYING:
            result = "FLYING";
            break;
        case POISON:
            result = "POISON";
            break;
        case GROUND:
            result = "GROUND";
            break;
        case ROCK:
            result = "ROCK";
            break;
        case BUG:
            result = "BUG";
            break;
        case GHOST:
            result = "GHOST";
            break;
        case STEEL:
            result = "STEEL";
            break;
        case FIRE:
            result = "FIRE";
            break;
        case WATER:
            result = "WATER";
            break;
        case GRASS:
            result = "GRASS";
            break;
        case ELECTRIC:
            result = "ELECTRIC";
            break;
        case PSY:
            result = "PSY";
            break;
        case ICE:
            result = "ICE";
            break;
        case DRAGON:
            result = "DRAGON";
            break;
        case DARK:
            result = "DARK";
            break;
        case FAIRY:
            result = "FAIRY";
            break;
    }
    return result;
}

inline float computeTypeEffectiveness(Type sender, Type target) {
    CsvReader reader("../csv/types_compact.csv", ";", false);
    auto data_list = reader.getData();
    return stof(data_list[(unsigned int)(sender)][(unsigned int)(target)]) / 100;
}
#endif //CPP_DUMP_TYPE_H
