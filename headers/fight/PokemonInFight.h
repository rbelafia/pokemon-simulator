//
// Created by romain on 25/09/2020.
//

#ifndef POKEMON_SIMULATOR_POKEMONINFIGHT_H
#define POKEMON_SIMULATOR_POKEMONINFIGHT_H


#include <set>
#include <ostream>
#include "../entities/pokemons/Pokemon.h"
#include "VolatileStatus.h"

class PokemonInFight {
    friend class Fight;

public:

    struct StatsAlterations {
        short attack;
        short defense;
        short speAttack;
        short speDef;
        short speed;
        short accuracy;
        short flee;
    };
protected:
    Pokemon* pokemon;
    StatsAlterations alterations;
    set<VolatileStatus> volatileStatus;
public:
    PokemonInFight();
    PokemonInFight(Pokemon *pokemon);

    friend ostream &operator<<(ostream &os, const PokemonInFight &fight);

    float computeStat(StatisticsName statistics) const;

};


#endif //POKEMON_SIMULATOR_POKEMONINFIGHT_H
