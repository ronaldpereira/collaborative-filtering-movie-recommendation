#include <fstream>
#include <cstring>
#include "itemuser.hpp"

void ItemUser::ItemUserRatingsBuilder(char *ratingsPath)
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

        ItemUserRatings[item][user] = rating;

        UserConsumedItems[user].push_back(item);
    }

    calculateItemsAvgRating();
    calculateGlobalItemsAvgRating();

    ratingsFile.close();
}

void ItemUser::calculateItemsAvgRating()
{
    for (auto &item : ItemUserRatings)
    {
        int sum = 0;
        int count = 0;
        for (auto &user : item.second)
        {
            sum += user.second;
            count++;
        }
        ItemAvgRating[item.first] = double(sum) / count;
    }
}

void ItemUser::calculateGlobalItemsAvgRating()
{
    double sum = 0;
    int count = 0;
    for (auto &item : ItemAvgRating)
    {
        sum += item.second;
        count++;
    }
    GlobalItemsAvg = double(sum) / count;
}
