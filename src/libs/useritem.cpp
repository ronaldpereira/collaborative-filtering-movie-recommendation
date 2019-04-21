#include <fstream>
#include <cstring>
#include "useritem.hpp"

UserItem::~UserItem()
{
    for (auto &uir : UserItemRatings)
        uir.second.clear();

    UserItemRatings.clear();

    UserAvgRating.clear();
}

void UserItem::UserItemRatingsBuilder(char *ratingsPath)
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

        UserItemRatings[user][item] = rating;

        ItemUser[item].push_back(user);
    }

    calculateUsersAvgRating();

    ratingsFile.close();
}

void UserItem::calculateUsersAvgRating()
{
    for (auto &user : UserItemRatings)
    {
        int sum = 0;
        int count = 0;
        for (auto &item : user.second)
        {
            sum += item.second;
            count++;
        }
        UserAvgRating[user.first] = double(sum) / count;
    }
}
