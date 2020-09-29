//
// Created by romain on 23/09/2020.
//

#ifndef POKEMON_SIMULATOR_TRAINER_H
#define POKEMON_SIMULATOR_TRAINER_H

#include <string>
#include <ostream>
#include "../pokemons/Pokemon.h"

using namespace std;

class Trainer {
    friend class Fight;

private:
    static unsigned int ID_COUNTER;

protected:
    const unsigned int id;
    const string name;
    vector<Pokemon*> team;
public:
    Trainer(const string &name);

    friend ostream &operator<<(ostream &os, const Trainer &trainer);


};


#endif //POKEMON_SIMULATOR_TRAINER_H
