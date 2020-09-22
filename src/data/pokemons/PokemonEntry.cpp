//
// Created by romain on 15/09/2020.
//

#include "../../../headers/data/pokemons/PokemonEntry.h"

PokemonEntry::PokemonEntry(const string &name, const string &description, Type type1, Type type2, float height,
                           float weight,
                           unsigned short baseExperience, const Statistics &baseStatistics,
                           const list<MoveEntry *> &movePool,
                           float captureRate) : id(ID_COUNTER), name(name),
                                                description(description), type1(type1), type2(type2), height(height), weight(weight),
                                                baseStatistics(baseStatistics), captureRate(captureRate), baseExperience(baseExperience), movePool(buildMapFromList(movePool)) {
    ID_COUNTER++;

}

map<unsigned int, MoveEntry *> PokemonEntry::buildMapFromList(const list<MoveEntry *> &entries) {
    map<unsigned int, MoveEntry*> result;
    for(auto* entry : entries)
        result.insert(pair<unsigned int, MoveEntry*>(entry->id, entry));
    return result;

}

ostream &operator<<(ostream &os, const PokemonEntry &entry) {
    os << entry.name << " - " << tToString(entry.type1);
    if (entry.type2 != NEUTRAL) os << "/" << tToString(entry.type2);
    return os;
}


bool PokemonEntry::canLearnMove(const MoveEntry* moveEntry) {
    return movePool.find(moveEntry->id) != movePool.end();
}


