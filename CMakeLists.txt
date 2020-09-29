cmake_minimum_required(VERSION 3.17)
project(pokemon-simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(pokemon-simulator main.cpp src/data/moves/MoveEntry.cpp headers/data/moves/MoveEntry.h headers/data/Type.h headers/data/moves/MoveDex.h src/data/pokemons/PokemonEntry.cpp headers/data/pokemons/PokemonEntry.h headers/data/pokemons/Statistics.h headers/data/moves/Category.h src/utils/CsvReader.cpp headers/utils/CsvReader.h src/data/moves/MoveDex.cpp src/data/pokemons/PokemonDex.cpp headers/data/pokemons/PokemonDex.h headers/data/items/ItemEntry.h src/data/items/ItemEntry.cpp src/entities/pokemons/Pokemon.cpp headers/entities/pokemons/Pokemon.h headers/entities/pokemons/Nature.h src/fight/Fight.cpp headers/fight/Fight.h src/entities/trainer/Trainer.cpp headers/entities/trainer/Trainer.h src/fight/PokemonInFight.cpp headers/fight/PokemonInFight.h headers/entities/pokemons/MainStatus.h headers/fight/VolatileStatus.h)