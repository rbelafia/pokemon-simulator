//
// Created by romain on 15/09/2020.
//

#include "../../../headers/data/pokemons/PokemonEntry.h"

PokemonEntry::PokemonEntry(const string &name, const string &description, Type type1, Type type2, float height,
                           float weight,
                           unsigned short baseExperience, const Statistics &baseStatistics,
                           const list<const MoveEntry *> &movePool,
                           float captureRate) :
                           id(ID_COUNTER),
                           name(name),
                           description(description),
                           type1(type1),
                           type2(type2),
                           height(height),
                           weight(weight),
                           baseStatistics(baseStatistics),
                           captureRate(captureRate),
                           baseExperience(baseExperience),
                           movePool(buildMapFromList(movePool))
                           {
    ID_COUNTER++;

}

map<unsigned int, const MoveEntry*>* PokemonEntry::buildMapFromList(const list<const MoveEntry *> &entries) {
    auto* result = new map<unsigned int , const MoveEntry*>();
    for(auto* entry : entries)
        result->insert(pair<unsigned int, const MoveEntry*>(entry->id, entry));
    return result;

}

ostream &operator<<(ostream &os, const PokemonEntry &entry) {
    os << entry.name << " - " << tToString(entry.type1);
    if (entry.type2 != NEUTRAL) os << "/" << tToString(entry.type2);
    return os;
}


bool PokemonEntry::canLearnMove(const MoveEntry* moveEntry) const {
    return movePool->find(moveEntry->id) != movePool->end();
}

list<const MoveEntry *> PokemonEntry::getListMove() const {
    list<const MoveEntry *> res{};
    for(auto it: *movePool) res.push_back(it.second);
    return res;
}


