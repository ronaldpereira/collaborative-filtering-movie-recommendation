#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <string.h>
#include <stdlib.h>
#include "useritem.hpp"

void UserItem::MatrixBuilder(char *ratingsPath) {
    std::string line;
    std::ifstream ratingsFile;
    ratingsFile.open(ratingsPath);

    // Discard header from csv
    getline(ratingsFile, line);

    while(getline(ratingsFile, line) && !line.empty()) {
        char *token;

        char *cstr = new char [line.length()+1];
        std::strcpy(cstr, line.c_str());

        token = strtok(cstr, ",ui");
        int user = atoi(token);

        token = strtok(NULL, ",ui");
        int item = atoi(token);

        token = strtok(NULL, ",ui");
        int rating = atoi(token);

        token = strtok(NULL, ",ui");
        int timestamp = atoi(token);

        std::cout << user << " " << item << " " << rating << " " << timestamp << std::endl;
    }
}
