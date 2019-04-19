#include <iostream>
#include <fstream>
#include <cstring>
#include "useritem.hpp"

void UserItem::MatrixBuilder(char *ratingsPath)
{
    std::string line;
    std::ifstream ratingsFile;
    ratingsFile.open(ratingsPath);

    // Discard header from csv
    getline(ratingsFile, line);

    while (getline(ratingsFile, line) && !line.empty())
    {
        char *token;

        char *cstr = new char[line.length() + 1];
        std::strcpy(cstr, line.c_str());

        token = strtok(cstr, ",ui");
        int user = atoi(token);

        token = strtok(NULL, ",ui");
        int item = atoi(token);

        token = strtok(NULL, ",ui");
        int rating = atoi(token);

        token = strtok(NULL, ",ui");
        int timestamp = atoi(token);

        insertUserItemRating(user, item, rating);
    }

    std::cout << "n_users: " << matrix.size() << std::endl;
    std::cout << "n_items: " << matrix[0].size() << std::endl;
}

void UserItem::insertUserItemRating(int userID, int itemID, int rating)
{
    int userXPos = getUserPosition(userID);
    int itemYPos = getItemPosition(itemID);

    // User is not inserted
    if (userXPos < 0)
    {
        userXPos = createUser(userID);
    }

    // Item is not inserted
    if (itemYPos < 0)
    {
        itemYPos = createItem(itemID);
    }

    matrix[userXPos][itemYPos] = rating;
}

int UserItem::getUserPosition(int userID)
{
    for (unsigned int i = 0; i < userLookup.size(); i++)
    {
        // If the userID is found in the userLookup, returns the index that corresponds to useritem matrix coordenate X
        if (userID == userLookup[i])
            return i;
    }
    // If it's not found, return -1
    return -1;
}

int UserItem::getItemPosition(int itemID)
{
    for (unsigned int i = 0; i < itemLookup.size(); i++)
    {
        // If the itemID is found in the itemLookup, returns the index that corresponds to useritem matrix coordenate Y
        if (itemID == itemLookup[i])
            return i;
    }
    // If it's not found, return -1
    return -1;
}

int UserItem::createUser(int userID)
{
    nUser++;

    // Insert user to matrix
    matrix.push_back(std::vector<int>(nItem));

    // Insert user to userLookup
    userLookup.push_back(userID);

    // Return created position in matrix
    return nUser - 1;
}

int UserItem::createItem(int itemID)
{
    nItem++;

    // Insert item to matrix
    for (int i = 0; i < nUser; i++)
        matrix[i].push_back(0);

    // Insert item to itemLookup
    itemLookup.push_back(itemID);

    // Return created position in matrix
    return nItem - 1;
}
