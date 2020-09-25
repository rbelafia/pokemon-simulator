//
// Created by romain on 23/09/2020.
//

#include "../../../headers/entities/trainer/Trainer.h"
#include "../../../headers/data/pokemons/PokemonDex.h"

unsigned int Trainer::ID_COUNTER = 1;

Trainer::Trainer(const string &name) : id(ID_COUNTER), name(name) {
    ID_COUNTER++;
    PokemonDex* dex = PokemonDex::getInstance();
    srand((unsigned) time(0));
    for (auto & i : team) {
        auto rand_number = (unsigned int)((rand() % 807) + 1);

        const auto* pokemon_entry = dex->getEntry(rand_number);
        auto nat = (Nature)(HARDY + (rand() % 24));
        unsigned short level = rand() %100 + 1;

        i = new Pokemon(pokemon_entry, nat,level);
    }
}

ostream &operator<<(ostream &os, const Trainer &trainer) {
    os << " name: " << trainer.name << "\nTeam: ";
    for (auto & i : trainer.team)
        os << *i << "\n";
    return os;
}
