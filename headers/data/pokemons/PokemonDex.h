//
// Created by romain on 21/09/2020.
//

#ifndef CPP_DUMP_POKEMONDEX_H
#define CPP_DUMP_POKEMONDEX_H


#include "PokemonEntry.h"

class PokemonDex {
private:
    static PokemonDex* INSTANCE;

    map<unsigned int, const PokemonEntry*> entries;

    PokemonDex();
public:
    PokemonDex(const PokemonDex&) = delete;

    PokemonDex& operator=(const PokemonDex&) = delete;

    static PokemonDex* getInstance();

    const PokemonEntry* getEntry(unsigned int index) const;

    friend ostream &operator<<(ostream &os, const PokemonDex &dex);

    virtual ~PokemonDex();

};


#endif //CPP_DUMP_POKEMONDEX_H
