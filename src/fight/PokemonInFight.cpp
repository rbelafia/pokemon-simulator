//
// Created by romain on 25/09/2020.
//

#include "../../headers/fight/PokemonInFight.h"

PokemonInFight::PokemonInFight(Pokemon *pokemon) :
pokemon(pokemon),
alterations({0, 0, 0, 0, 0, 0, 0}),
volatileStatus(set<VolatileStatus>()) {}

ostream &operator<<(ostream &os, const PokemonInFight &fight) {
    os << fight.pokemon->getNickName() << " n°" << fight.pokemon->getLevel() << " PV: " << fight.pokemon->getPv()
    << "/" << fight.pokemon->getStats().pv << "\n";
    return os;
}

float PokemonInFight::computeStat(StatisticsName statistics) const {
    short alt = ((short*)&alterations)[((unsigned int)(statistics) - 1)];
    float modification = 1;
    switch (statistics) {
        case ATTACK:
        case DEFENSE:
        case SPE_ATTACK:
        case SPE_DEFENSE:
        case SPEED:
        {
            if (alt >= 0) modification += alt/2;
            else modification = 2 / (2 - alt);
            return ((unsigned int*)&(pokemon->stats))[(unsigned int)statistics] * modification;
        }
        case ACCURACY:
        case FLEE:
        {
            if (alt >= 0) modification += ((float)alt)/3;
            else modification = 3 / (3 - alt);
            return modification;
        }
        case PV:
            return (float)(pokemon->stats.pv);

    }

}

PokemonInFight::PokemonInFight() : pokemon(nullptr),
alterations({0, 0, 0, 0, 0, 0, 0}),
volatileStatus(set<VolatileStatus>()) {}
