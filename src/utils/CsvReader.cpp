//
// Created by romain on 18/09/2020.
//


#include "../../headers/utils/CsvReader.h"
vector<vector<string>> CsvReader::getData()
{
    ifstream file(fileName);
    vector<vector<string>> dataList;
    string line;
    // Iterate through each line and split the content using delimiter
    getline(file, line);
    while (getline(file, line))
        if(!line.empty()) {
            vector<string> vec;
            boost::algorithm::split(vec, line, boost::is_any_of(delimiter + "\r"));
            dataList.push_back(vec);
        }
    // Close the File
    file.close();
    return dataList;
}