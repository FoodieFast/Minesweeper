#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <unordered_map>
#include "tile.h"
#include "TextureManager.h"
#include "leaderboard.h"
#include <vector>


#ifndef SFML_EXAMPLE_BOARD_H
#define SFML_EXAMPLE_BOARD_H


class board {
    sf::RenderWindow boardWindow;
    int height;
    int width;
    int mines;
    int minesTall;
    int minesLong;
    int revealedTiles = 0;
    int totalNonMineTiles;
    tile bruh;
    TextureManager textures;
    string playerName;

    chrono::steady_clock::time_point startTime;
    int elapsedSeconds;
    int elapsedMinutes;
    int pausedSeconds = 0;
    chrono::steady_clock::time_point pauseStartTime;

    vector<vector<tile>> tileBoard;

    sf::Sprite face;
    sf::Texture faceHappy;
    sf::Sprite playPauseButton;
    sf::Sprite leaderBoardButton;
    bool isPaused = false;
    bool isGameWon = false;
    bool WinLeaderBoard = false;
    bool isDebugMode = false;






public:
    board(int width, int height, int amtMines, string nameinput);
    void initalizeBoard();
    void placeMines(int numMines);
    void debug_mode(sf::Texture &face_Happy, const int flagsPlaced, leaderboard &gameLeaderboard);
    void gameOver();
    void resetBoard();
    void flagCounterUpdate(int flagsPlaced, sf::Sprite &counterDigit1, sf::Sprite &counterDigit2,sf::Sprite &counterDigit3, sf::Sprite &counterDigitNegative);

    void TimerUpdate(int time, sf::Sprite &counterDigit1, sf::Sprite &counterDigit2);
    void updateClock();
    bool onLeftClick(int x, int y);
    int countAdjacentMines(int x, int y);
    void revealTile(int x, int y, sf::Texture &tileRevealed);

    void pause(sf::Texture &texture);


};


#endif //SFML_EXAMPLE_BOARD_H
