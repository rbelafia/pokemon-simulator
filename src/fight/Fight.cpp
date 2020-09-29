//
// Created by romain on 23/09/2020.
//

#include <algorithm>
#include <iostream>
#include <cmath>
#include "../../headers/fight/Fight.h"

Fight::Fight(Trainer *trainer1, Trainer *trainer2)
         {
    trainers[PLAYER_1] = trainer1;
    trainers[PLAYER_2] = trainer2;

    pokemonsInFight[PLAYER_1] = PokemonInFight(trainer1->team[0]);
    pokemonsInFight[PLAYER_2] = PokemonInFight(trainer2->team[0]);

}

bool Fight::isOver() {
    return
    none_of(trainers[PLAYER_1]->team.begin(), trainers[PLAYER_1]->team.end(), [](const Pokemon* p){return p->mainStatus != KO;}) ||
    none_of(trainers[PLAYER_2]->team.begin(), trainers[PLAYER_2]->team.end(), [](const Pokemon* p){return p->mainStatus != KO;});
}



void Fight::run() {
    while (!isOver()) {
        // Presentation of the players and their first pokemon
        cout << "Trainer 1 :" << endl;
        cout << pokemonsInFight[PLAYER_1] << endl;

        cout << "Trainer 2 :" << endl;
        cout << pokemonsInFight[PLAYER_2] << endl;

        sleep(3);

        // Ask the player 1 to chose his move
        cout << "Trainer 1, chose your move" << endl;
        cout << *pokemonsInFight[PLAYER_1].pokemon << endl;

        const MoveEntry* entries[2] = {nullptr, nullptr};

        unsigned short num_1;
        bool choice_incorrect = true;
        while (choice_incorrect) {
            cin >> num_1;
            if (num_1 < 1 || num_1 > pokemonsInFight[PLAYER_1].pokemon->moves.size())
                cout << "Please chose an index between 1 and " << pokemonsInFight[PLAYER_1].pokemon->moves.size() << endl;
            else choice_incorrect = false;
        }
        entries[PLAYER_1] = pokemonsInFight[PLAYER_1].pokemon->moves[num_1 - 1].entry;

        unsigned short num_2 = rand() % 4;

        // random selection of the player 2
        entries[PLAYER_2] = pokemonsInFight[PLAYER_2].pokemon->moves[num_2].entry;

        Player beginner = computePriority(entries[PLAYER_1], entries[PLAYER_2]);

        attack(beginner, entries[beginner], (beginner == PLAYER_1) ? num_1 - 1 : num_2);
        if(pokemonsInFight[1 - beginner].pokemon->mainStatus == KO)
            switchPokemon(1 - beginner);
        else
            attack(1 - beginner, entries[1 - beginner], 0);
    }

}

Fight::Player Fight::computePriority(const MoveEntry *moveEntry1, const MoveEntry *moveEntry2) const {
    if (moveEntry1->priority != moveEntry2->priority)
        return (moveEntry1->priority > moveEntry2->priority) ? PLAYER_1 : PLAYER_2;

    else {
        float speed_1 = pokemonsInFight[PLAYER_1].computeStat(SPEED);
        float speed_2 = pokemonsInFight[PLAYER_2].computeStat(SPEED);

        if (speed_1 != speed_2)
            return (speed_1 > speed_2) ? PLAYER_1 : PLAYER_2;
        else
            return (rand() % 1) ? PLAYER_1 : PLAYER_2;
    }

}

void Fight::attack(Fight::Player player, const MoveEntry *moveEntry, char index) {
    if(pokemonsInFight[player].pokemon->moves[index].pp != 0) {
        cout << pokemonsInFight[player].pokemon->nickName << " uses " << moveEntry->name << endl;
        sleep(2);
        pokemonsInFight[player].pokemon->moves[index].pp--;

        // get the level of the pokemon
        auto level = (float)pokemonsInFight[player].pokemon->level;

        // compute the attack or the special attack, depending of the category of the move after application
        // of the alterations
        float attack =
                (moveEntry->category == PHYSICAL) ? pokemonsInFight[player].computeStat(ATTACK) :
                ((moveEntry->category == SPECIAL) ? pokemonsInFight[player].computeStat(SPE_ATTACK) : 0);
        float defense =
                (moveEntry->category == PHYSICAL) ? pokemonsInFight[1 - player].computeStat(DEFENSE) :
                ((moveEntry->category == SPECIAL) ? pokemonsInFight[1 - player].computeStat(SPE_DEFENSE) : 1);

        // get the move power
        unsigned short power = moveEntry->power;

        // compute the stab
        float stab =
                (moveEntry->type == pokemonsInFight[player].pokemon->entry->type1 ||
                 moveEntry->type == pokemonsInFight[player].pokemon->entry->type2) ? 1.5 : 1;

        // compute the critical move
        float critical = (rand() % 16 == 0) ? 2 : 1;
        if (critical == 2) cout << "CRITICAL HIT !" << endl;

        // compute the effectiveness of the move
        float effective = computeTypeEffectiveness(moveEntry->type, pokemonsInFight[1 - player].pokemon->entry->type1);
        effective *= computeTypeEffectiveness(moveEntry->type, pokemonsInFight[1 - player].pokemon->entry->type2);
        if (effective == 0) cout << "It doesn't affect " << pokemonsInFight[1 - player].pokemon->entry->name << endl;
        else if (effective > 1) cout << "It's super effective !" << endl;
        else if (effective < 1) cout << "It's not really effective ..." << endl;

        // compute the random modification
        float random = ((float)(100 - (rand() % 15))) / 100;

        // compute the total modification
        float cm = stab * critical * effective * random;

        // compute the PV loss
        unsigned int pv_lost = floor(((((level * 0.4 + 2) * attack * power) / (defense * 50)) + 2) * cm);
        pokemonsInFight[1 - player].pokemon->pv -=
                (pokemonsInFight[1 - player].pokemon->pv > pv_lost) ? pv_lost : pokemonsInFight[1 - player].pokemon->pv;

        // set the pokemon K0
        if (pokemonsInFight[1 - player].pokemon->pv == 0) pokemonsInFight[1 - player].pokemon->mainStatus = KO;
        if (pokemonsInFight[1 - player].pokemon->mainStatus == KO) {
            cout << pokemonsInFight[1 - player].pokemon->entry->name << " is KO !" << endl;
            sleep(2);
        }
    }
}


void Fight::switchPokemon(Player player) {
    cout << "Trainer " << player + 1 << ", chose your pokemon" << endl;
    for (int i = 0; i < trainers[player]->team.size(); ++i)
        cout << i + 1 << ": " << trainers[player]->team[i]->nickName << " lv " << trainers[player]->team[i]->level << endl;

    unsigned short num = 0;
    bool choice_incorrect = true;

    while (choice_incorrect) {
        cin >> num;
        if (num < 1 || num > trainers[player]->team.size())
            cout << "Please chose an index between 2 and " <<  trainers[player]->team.size() << endl;
        else if (trainers[player]->team[num - 1]->mainStatus == KO)
            cout << "The pokemon is KO, chose another one" << endl;
        else choice_incorrect = false;
    }
    Pokemon* temp = trainers[player]->team[0];
    trainers[player]->team[0] = trainers[player]->team[num-1];
    trainers[player]->team[num-1] = temp;

    pokemonsInFight[player] = PokemonInFight(trainers[player]->team[0]);
}