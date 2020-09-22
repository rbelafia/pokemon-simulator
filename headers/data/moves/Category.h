//
// Created by romain on 16/09/2020.
//

#ifndef CPP_DUMP_CATEGORY_H
#define CPP_DUMP_CATEGORY_H

/*!
 * \file Category.h
 * \brief Describe a move category
 */
#include <string>

using namespace std;
/**
 * \enum Category
 * \brief Define the category of a move
 */
enum Category {
    STATUS,       /**< Impact status */
    PHYSICAL,     /**< A physical based move (attack and defense used) */
    SPECIAL,      /**< A special based move (attack. spe. and defense. spe. used) */
};

/*!
 * \brief Convert a Category to a string
 * \param category
 * \return The category name
 */
inline string cToString(Category category) {
    string result;
    switch (category) {
        case PHYSICAL:
            result = "PHYSICAL";
            break;
        case SPECIAL:
            result = "SPECIAL";
            break;
        case STATUS:
            result = "STATUS";
            break;
    }
    return result;
}


#endif //CPP_DUMP_CATEGORY_H
