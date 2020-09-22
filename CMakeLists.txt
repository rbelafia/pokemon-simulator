cmake_minimum_required(VERSION 3.17)
project(pokemon-simulator)

set(CMAKE_CXX_STANDARD 14)

add_executable(pokemon-simulator main.cpp src/data/moves/MoveEntry.cpp headers/data/moves/MoveEntry.h headers/data/Type.h headers/data/moves/MoveDex.h src/data/pokemons/PokemonEntry.cpp headers/data/pokemons/PokemonEntry.h headers/data/pokemons/Statistics.h headers/data/moves/Category.h src/utils/CsvReader.cpp headers/utils/CsvReader.h src/data/moves/MoveDex.cpp src/data/pokemons/PokemonDex.cpp headers/data/pokemons/PokemonDex.h)