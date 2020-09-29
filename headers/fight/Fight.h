//
// Created by romain on 23/09/2020.
//

#ifndef POKEMON_SIMULATOR_FIGHT_H
#define POKEMON_SIMULATOR_FIGHT_H
#define PLAYER_1 0
#define PLAYER_2 1

#include "../entities/trainer/Trainer.h"
#include "PokemonInFight.h"

class Fight {
public:
    typedef char Player;
private:
    Trainer* trainers[2];

    PokemonInFight pokemonsInFight[2];

    bool isOver();

    Player computePriority(const MoveEntry* moveEntry1, const MoveEntry* moveEntry2) const;

    void attack(Fight::Player player, const MoveEntry *moveEntry, char index);

    void switchPokemon(Player player);

public:
    Fight(Trainer *trainer1, Trainer *trainer2);

    void run();


};



#endif //POKEMON_SIMULATOR_FIGHT_H
