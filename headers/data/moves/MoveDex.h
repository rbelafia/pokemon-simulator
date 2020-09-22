//
// Created by romain on 15/09/2020.
//

#ifndef CPP_DUMP_MOVEDEX_H
#define CPP_DUMP_MOVEDEX_H

/*!
 * \file MoveDex.h
 * \brief Define the singleton PokemonDex
 * \author Romain Belafia
 * \version 0.1
 */

#include <map>
#include "MoveEntry.h"

using namespace std;

/*!
 * \brief Define the singleton MoveDex. It contains every PokemonMoves possible.
 */
class MoveDex {
private:
    //! \static The unique instance of the class
    static MoveDex* INSTANCE;

    //! A map which contains the move entries
    map<unsigned int, MoveEntry*> entries;

    //! The constructor of the class (is not callable outside of the class scope)
    MoveDex();

public:
    //! Forbid the copy constructor
    MoveDex(const MoveDex&) = delete;

    //! Forbid the copy constructor
    MoveDex& operator=(const MoveDex&) = delete;

    //! Allow to get an instance of the class
    static MoveDex* getInstance();

    /*!
     * \brief Return a pokemon entry
     * \param index The index of the pokemon
     * \return A pointer to the move entry
     */
    MoveEntry* getEntry(unsigned int index);

    friend ostream &operator<<(ostream &os, const MoveDex &dex);
};



#endif //CPP_DUMP_MOVEDEX_H
