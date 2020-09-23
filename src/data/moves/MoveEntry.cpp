//
// Created by romain on 15/09/2020.
//

#include "../../../headers/data/moves/MoveEntry.h"
#include "../../../headers/data/moves/MoveDex.h"

MoveEntry::MoveEntry(const string &name, const string &description, const Category category, const Type type,
                     const unsigned short power, const unsigned short precision, const unsigned short pp,
                     const unsigned short priority) :
                     id(ID_COUNTER), name(name), description(description), category(category), type(type),
                     power(power), accuracy(precision), maxPp(pp), priority(priority) {
    ID_COUNTER++;
}

ostream &operator<<(ostream &os, const MoveEntry &entry) {
    os << entry.name << " - " << cToString(entry.category) << " - " << tToString(entry.type) << " - POWER: " << entry.power << " - PRECISION: " << entry.accuracy;
    return os;
}

MoveEntry::MoveEntry() : id(MoveEntry::ID_COUNTER), name(""), description(""), category(PHYSICAL), type(NEUTRAL), power(1), accuracy(100), maxPp(25), priority(0){}

unsigned short MoveEntry::getMaxPp() const {
    return maxPp;
}