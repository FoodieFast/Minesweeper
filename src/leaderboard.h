#include "SFML/Graphics.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
#include "helper_functions.h"

#ifndef SFML_EXAMPLE_LEADERBOARD_H
#define SFML_EXAMPLE_LEADERBOARD_H

class leaderboard {
    vector<pair<int, string>> leaderboardData;
    sf::Font default_font;
    string currentPlayer;

public:
    leaderboard(string currPlayer);

    void saveLeaderboardToFile();
    void loadLeaderboardFromFile();
    void showLeaderBoard(int minesLong, int minesTall, string &playerName, int time);
    void updateLeaderboard(const string &name, const int time);
};




#endif //SFML_EXAMPLE_LEADERBOARD_H
