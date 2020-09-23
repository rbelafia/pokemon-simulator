//
// Created by romain on 22/09/2020.
//

#ifndef POKEMON_SIMULATOR_NATURE_H
#define POKEMON_SIMULATOR_NATURE_H

#include <map>
#include <vector>
#include "../../data/pokemons/Statistics.h"

enum Nature {
    HARDY,
    LONELY,
    BRAVE,
    ADAMANT,
    NAUGHTY,
    BOLD,
    DOCILE,
    RELAXED,
    IMPISH,
    LAX,
    TIMID,
    HASTY,
    SERIOUS,
    JOLLY,
    NAIVE,
    MODEST,
    MILD,
    QUIET,
    BASHFUL,
    RASH,
    CALM,
    GENTLE,
    SASSY,
    CAREFUL,
    QUIRKY
};

static std::map<Nature, std::vector<float>> converter;

inline float computeNature(StatisticsName stat, Nature nature) {
    if (converter.empty()) {
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 5; ++j) {
                std::vector<float> vec = {1, 1, 1, 1, 1};
                vec[i] += 0.1;
                vec[j] -= 0.1;
                converter.insert(std::pair<Nature, std::vector<float>>(nature, vec));
            }
        }
    }

    switch (stat) {
        case ATTACK:
        case DEFENSE:
        case SPE_ATTACK:
            return converter[nature][stat - 1];
            break;
        case SPE_DEFENSE:
            return converter[nature][4];
            break;
        case SPEED:
            return converter[nature][2];
            break;
        case PV:
            return 1;

    }


}
#endif //POKEMON_SIMULATOR_NATURE_H
