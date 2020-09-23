//
// Created by romain on 15/09/2020.
//

#ifndef CPP_DUMP_POKEMONENTRY_H
#define CPP_DUMP_POKEMONENTRY_H

#include <string>
#include <list>
#include <map>
#include "../Type.h"
#include "Statistics.h"
#include "../moves/MoveEntry.h"

using namespace std;

class PokemonEntry {
    friend class PokemonDex;
    friend class Pokemon;
    friend ostream;

public:
    static unsigned int ID_COUNTER;
private:
    static map<unsigned int, MoveEntry*> buildMapFromList(const list<MoveEntry*>& entries);
protected:
    const unsigned int id;
    const string name;
    const string description;
    const Type type1;
    const Type type2;

    const float height;
    const float weight;

    const unsigned short baseExperience;
    const Statistics baseStatistics;
    const map<unsigned int, MoveEntry*> movePool;

    const float captureRate;
public:
    explicit PokemonEntry(const string &name = "", const string &description = "", Type type1 = NEUTRAL,
                          Type type2 = NEUTRAL,
                          float height = 0, float weight = 0, unsigned short baseExperience = 10000,
                          const Statistics &baseStatistics = {100, 100, 100, 100, 100, 100},
                          const list<MoveEntry *> &movePool = {}, float captureRate = 1);

    bool canLearnMove(const MoveEntry* moveEntry) const;

    list<MoveEntry*> getListMove() const;

    friend ostream &operator<<(ostream &os, const PokemonEntry &entry);
};


#endif //CPP_DUMP_POKEMONENTRY_H
