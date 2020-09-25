#include <iostream>
#include "headers/data/moves/MoveEntry.h"
#include "headers/data/moves/MoveDex.h"
#include "headers/data/pokemons/PokemonEntry.h"
#include "headers/data/pokemons/PokemonDex.h"
#include "headers/entities/pokemons/Pokemon.h"
#include "headers/entities/trainer/Trainer.h"

unsigned int MoveEntry::ID_COUNTER = 1;
unsigned int PokemonEntry::ID_COUNTER = 1;
unsigned int Pokemon::ID_COUNTER = 0;

int main() {
    std::cout << "Battle begin" << std::endl;


    MoveDex* move_dex = MoveDex::getInstance();
    std::cout << *move_dex << std::endl;

    PokemonDex* pokemon_dex = PokemonDex::getInstance();
    std::cout << *pokemon_dex << std::endl;

    cout << pokemon_dex->getEntry(1)->canLearnMove(move_dex->getEntry(76)) << endl;
    cout << pokemon_dex->getEntry(4)->canLearnMove(move_dex->getEntry(76)) << endl;

    //Pokemon charizard = Pokemon(pokemon_dex->getEntry(6), HARDY, 50);

    //cout << charizard << endl;

    Trainer trainer = Trainer("Georges");

    cout << trainer << endl;

    return 0;
}
