//
// Created by romain on 18/09/2020.
//

#ifndef CPP_DUMP_CSVREADER_H
#define CPP_DUMP_CSVREADER_H


#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>
/*
 * A class to read data from a csv file.
 */
using namespace std;

class CsvReader
{
    string fileName;
    string delimiter;
    bool header;
public:
    explicit CsvReader(string filename, string delm = ",", bool head = true) :
            fileName(move(filename)), delimiter(move(delm)), header(head)
    { }
    // Function to fetch data from a CSV File
    std::vector<std::vector<std::string> > getData();
};


#endif //CPP_DUMP_CSVREADER_H
