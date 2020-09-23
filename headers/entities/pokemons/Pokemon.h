//
// Created by romain on 22/09/2020.
//

#ifndef POKEMON_SIMULATOR_POKEMON_H
#define POKEMON_SIMULATOR_POKEMON_H

/*!
 * \file Pokemon.h
 * \brief Describe a pokemon entity
 * \author Romain Belafia
 * \version 1.0
 */

#include <string>
#include <vector>
#include <ostream>
#include "../../data/pokemons/PokemonEntry.h"
#include "Nature.h"

using namespace std;

/*! \class Pokemon
 * \brief Describe a pokemon entity
 */
class Pokemon {
public:
    /*! \struct Move
     * \brief Describe a move of a given pokemon
     */
    struct Move {
        const MoveEntry* entry;    //!< The entry of the move
        unsigned int maxPp;        //!< The maximum number of PP for a move
        unsigned int pp;           //!< The actual number of PP for a move
    };


    typedef struct {
        unsigned int pv;
        unsigned int attack;
        unsigned int defense;
        unsigned int speAttack;
        unsigned int speDefense;
        unsigned int speed;
    } RealStatistics;

    static unsigned int ID_COUNTER;
protected:
    const unsigned int id;
    const PokemonEntry* entry;
    string nickName;

    const Nature nature;

    unsigned short level;

    unsigned int pv;

    const Statistics iv;
    Statistics ev;
    RealStatistics stats;

    vector<Move> moves;

public:
    Pokemon(const PokemonEntry *entry, const Nature nature, unsigned short level,
            const Statistics iv = {31, 31, 31, 31, 31, 31}, const Statistics ev = {0, 0, 0, 0, 0, 0});

    void addMove(const MoveEntry* moveEntry);

    void changeMove(const MoveEntry *moveEntry, unsigned short index);

    void changeName(const string& name);

    friend ostream &operator<<(ostream &os, const Pokemon &pokemon);

};


#endif //POKEMON_SIMULATOR_POKEMON_H
