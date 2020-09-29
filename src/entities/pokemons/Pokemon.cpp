//
// Created by romain on 22/09/2020.
//

#include <cmath>
#include "../../../headers/entities/pokemons/Pokemon.h"
#include "../../../headers/data/pokemons/PokemonDex.h"

unsigned int computePv(unsigned short base, unsigned short iv, unsigned short ev, unsigned short level) {
    return (unsigned short)(floor((2 * base + iv  + (unsigned short)floor(ev/4)) * level / 100)) + level + 10;
}

unsigned int computeStat(unsigned short base, unsigned short iv, unsigned short ev, unsigned short level, float nature) {
    return (unsigned short)floor(floor((2 * base + iv  + (unsigned short)floor(ev/4)) * level / 100 + 5) * nature);
}

Pokemon::Pokemon(const PokemonEntry *entry, const Nature nature, unsigned short level, const Statistics iv,
                 const Statistics ev) :
                 id(ID_COUNTER), entry(entry), nickName(entry->name), nature(nature), level(level), iv(iv), ev(ev),
                 moves(vector<Move>(4)), mainStatus(CLEAN) {
    ID_COUNTER++;
    pv = computePv(entry->baseStatistics.pv, iv.pv, ev.pv, level);

    stats = {pv,
             computeStat(entry->baseStatistics.attack,
                         iv.attack,
                         ev.attack,
                         level,
                         computeNature(ATTACK, nature)),
             computeStat(entry->baseStatistics.defense,
                         iv.defense,
                         ev.defense,
                         level,
                         computeNature(DEFENSE, nature)),
             computeStat(entry->baseStatistics.speAttack,
                         iv.speAttack,
                         ev.speAttack,
                         level,
                         computeNature(SPE_ATTACK, nature)),
             computeStat(entry->baseStatistics.speDefense,
                         iv.speDefense,
                         ev.speDefense,
                         level,
                         computeNature(SPE_DEFENSE, nature)),
             computeStat(entry->baseStatistics.speed,
                         iv.speed,
                         ev.speed,
                         level,
                         computeNature(SPEED, nature))
    };


    list<const MoveEntry*> pool = entry->getListMove();

    for (int i = 0; i < 4; ++i) {
        auto it = pool.begin();
        int rand_number = (int) (rand() % pool.size());
        std::advance(it, rand_number);
        moves[i] = {*it, (*it)->getMaxPp(), (*it)->getMaxPp()};
        pool.remove(*it);
    }
}


void Pokemon::changeName(const string& name) {
    nickName = name;
}

void Pokemon::addMove(const MoveEntry *moveEntry) {
    if(moves.size() < 4)
        changeMove(moveEntry, moves.size());
}

void Pokemon::changeMove(const MoveEntry *moveEntry, unsigned short index) {
    if (entry->canLearnMove(moveEntry))
        moves[index] = Move{moveEntry, moveEntry->getMaxPp(), moveEntry->getMaxPp()};
}

ostream &operator<<(ostream &os, const Pokemon &pokemon) {
    os  << pokemon.nickName << "(" << *pokemon.entry << ") n°" << pokemon.level <<
    " pv: " << pokemon.pv << "\n" <<
    "________________________\n" <<
    "| Stats:\t\t\t\t|\n" << "|_______________________|\n"
    "| PV           |  " << pokemon.stats.pv << "\t|\n" <<
    "| Attack       |  " << pokemon.stats.attack << "\t|\n" <<
    "| Defense      |  " << pokemon.stats.defense << "\t|\n" <<
    "| Spe. Attack  |  " << pokemon.stats.speAttack << "\t|\n" <<
    "| Spe. Defense |  " << pokemon.stats.speDefense << "\t|\n" <<
    "| Speed:       |  " << pokemon.stats.speed << "\t|\n" <<
    "|______________|________|\n" <<
    "Moves:\n";
    for (Pokemon::Move m : pokemon.moves) {
        os << *m.entry << " [" << m.pp << "/" << m.maxPp << "]\n";
    }
    return os;
}

const string &Pokemon::getNickName() const {
    return nickName;
}

unsigned short Pokemon::getLevel() const {
    return level;
}

unsigned int Pokemon::getPv() const {
    return pv;
}

const Pokemon::RealStatistics &Pokemon::getStats() const {
    return stats;
}

