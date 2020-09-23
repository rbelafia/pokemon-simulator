//
// Created by romain on 15/09/2020.
//

#ifndef CPP_DUMP_MOVEENTRY_H
#define CPP_DUMP_MOVEENTRY_H

/*!
 * \file MoveEntry.h
 * \brief Describe a pokemon move
 * \author Romain Belafia
 * \version 0.1
 */

#include <string>
#include <ostream>
#include "../Type.h"
#include "Category.h"

using namespace std;

/*! \class MoveEntry
 * \brief Define a pokemon move
 * */
class MoveEntry {
    friend class Move;
    friend class MoveDex;
    friend class PokemonEntry;

public:
    static unsigned int ID_COUNTER;     //!< A counter to compute the id of a pokemon

protected:
    const unsigned int id;              //!< The id of the move
    const string name;                  //!< The name of the move
    const string description;           //!< The description of the move

    const Category category;            //!< The category of the move
    const Type type;                    //!< The type of the move
    const unsigned short power;         //!< The power of the move (0 - 255)
    const unsigned short accuracy;      //!< The accuracy of the move (0 - 100)
    const unsigned short maxPp;
public:
    unsigned short getMaxPp() const;

protected:
    //!< The accuracy of the move (0 - 100)

    const unsigned short priority;      //!< The priority of the move (from 0 to 6)

public:

    MoveEntry();

    MoveEntry(const string &name = "", const string &description = "", const Category = PHYSICAL, const Type type = NEUTRAL,
              const unsigned short power = 0, const unsigned short precision = 100, const unsigned short pp = 20,
              const unsigned short priority = 0);

    //virtual void attack(PokemonInFight* user, PokemonInFight* target) const;

    friend ostream &operator<<(ostream &os, const MoveEntry &entry);
};
#endif //CPP_DUMP_MOVEENTRY_H
