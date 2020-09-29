//
// Created by romain on 21/09/2020.
//

#include "../../../headers/data/pokemons/PokemonDex.h"
#include "../../../headers/utils/CsvReader.h"
#include "../../../headers/data/moves/MoveDex.h"

PokemonDex* PokemonDex::INSTANCE = nullptr;

PokemonDex::PokemonDex() : entries(map<unsigned int, const PokemonEntry*>()) {
    CsvReader reader("../csv/pokemons_compact.csv", ";");
    auto data_list = reader.getData();
    for (const auto& pokemon_row : data_list)
    {
        string index;
        if (stoi(pokemon_row[0]) < 10) index = "00" + pokemon_row[0];
        else if (stoi(pokemon_row[0]) < 100) index = "0" + pokemon_row[0];
        else index = pokemon_row[0];

        CsvReader reader_moves("../csv/moves/" + index + "-" + pokemon_row[1] + ".csv", ";");
        auto moves_list = reader_moves.getData();

        list<const MoveEntry*> moves;
        MoveDex* move_dex = MoveDex::getInstance();

        for (const auto& move_row : moves_list)
            moves.push_back(move_dex->getEntry(stoi(move_row[0])));

        auto* entry = new PokemonEntry(pokemon_row[1],
                                       pokemon_row[2],
                                       (Type) stoi(pokemon_row[3]),
                                       (!pokemon_row[4].empty()) ? (Type) stoi(pokemon_row[4]) : NEUTRAL,
                                       stof(pokemon_row[5]),
                                       stof(pokemon_row[6]),
                                       stoi(pokemon_row[7]),
                                       Statistics{
                                               (unsigned short) stoi(pokemon_row[8]),
                                               (unsigned short) stoi(pokemon_row[9]),
                                               (unsigned short) stoi(pokemon_row[10]),
                                               (unsigned short) stoi(pokemon_row[11]),
                                               (unsigned short) stoi(pokemon_row[12]),
                                               (unsigned short) stoi(pokemon_row[13])
                                       },
                                       moves);

        entries.insert(pair<unsigned int, PokemonEntry*>(stoi(pokemon_row[0]), entry));
    }
}

PokemonDex *PokemonDex::getInstance() {
    if(!INSTANCE) INSTANCE = new PokemonDex();
    return INSTANCE;
}

const PokemonEntry* PokemonDex::getEntry(unsigned int index) const {
    return INSTANCE->entries[index];
}

ostream &operator<<(ostream &os, const PokemonDex &dex) {
    os << "Dex: \n";
    for (auto entry : dex.entries)
        os << entry.first << " - " << *(entry.second) << "\n";
    return os;
}

PokemonDex::~PokemonDex() = default;
