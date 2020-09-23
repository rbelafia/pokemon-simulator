//
// Created by romain on 22/09/2020.
//

#ifndef POKEMON_SIMULATOR_ITEMENTRY_H
#define POKEMON_SIMULATOR_ITEMENTRY_H

/*!
 * \file ItemEntry.h
 * \brief Describe an item Entry
 * \author Romain Belafia
 * \version 0.1
 */

#include <string>

using namespace std;

class Item {
public:
    static unsigned int ID_COUNTER;     //!< A counter to compute the id of an Item

protected:
    const unsigned int id;              //!< The id of the item
    const string name;                  //!< The name of the item
    const string description;           //!< The description of the item

public:
    Item(const unsigned int id, const string &name, const string &description);

};

#endif //POKEMON_SIMULATOR_ITEMENTRY_H
