//
// Created by romain on 18/09/2020.
//

#include "../../../headers/data/moves/MoveDex.h"
#include "../../../headers/utils/CsvReader.h"

MoveDex* MoveDex::INSTANCE = nullptr;

MoveDex::MoveDex() : entries(map<unsigned int, const MoveEntry*>()) {
    CsvReader reader("../csv/moves_compact.csv", ";");

    auto data_list = reader.getData();
    for(const auto& vec : data_list)
    {
        auto* entry = new MoveEntry(vec[1],
                                    vec[2],
                                    (Category)(stoi(vec[3])-1),
                                    (Type)stoi(vec[4]),
                                    (!vec[5].empty()) ? stoi(vec[5]) : 0,
                                    (!vec[6].empty()) ? stoi(vec[6]) : 100,
                                    stoi(vec[7]),
                                    stoi(vec[8]));

        entries.insert(pair<unsigned int, MoveEntry*>(stoi(vec[0]), entry));
    }
}

MoveDex *MoveDex::getInstance() {
    if(!INSTANCE) INSTANCE = new MoveDex();
    return INSTANCE;
}

const MoveEntry *MoveDex::getEntry(const unsigned int index) {
    return entries[index];
}

ostream &operator<<(ostream &os, const MoveDex &dex) {
    os << "Dex: \n";
    for (auto entry : dex.entries)
        os << entry.first << " - " << *(entry.second) << "\n";
    return os;
}
