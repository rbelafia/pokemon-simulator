//
// Created by romain on 15/09/2020.
//

#ifndef CPP_DUMP_STATISTICS_H
#define CPP_DUMP_STATISTICS_H

enum StatisticsName {
    PV,
    ATTACK,
    DEFENSE,
    SPE_ATTACK,
    SPE_DEFENSE,
    SPEED,
    ACCURACY,
    FLEE
};

typedef struct {
    unsigned short pv;
    unsigned short attack;
    unsigned short defense;
    unsigned short speAttack;
    unsigned short speDefense;
    unsigned short speed;
} Statistics;

#endif //CPP_DUMP_STATISTICS_H
