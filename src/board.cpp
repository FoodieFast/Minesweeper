#include "board.h"
#include <iostream>

// Trying out Experimental Branch

board::board(int width, int height, int mines, string nameinput){
    // Setup of variables
    this->width = width;
    this->height = height;
    this->mines = mines;

    playerName = nameinput;

    minesTall = static_cast<int>((height- 100) / 32) ;
    minesLong = static_cast<int>(width / 32) ;
    totalNonMineTiles = (minesTall*minesLong) - mines;
    tileBoard.resize(minesTall, vector<tile>(minesLong));
    boardWindow.create(sf::VideoMode( width, height), "Minesweeper");

    // First initialization of board
    initalizeBoard();
}


// Creates board, tiles, tile grid/map, buttons
void board::initalizeBoard() {
    bool isgameOver = false;
    isDebugMode = false;
    bool isGameWon = false;
    WinLeaderBoard = false;

    leaderboard gameLeaderboard(playerName);

    sf::Texture tile_Hidden = textures.getTexture("tile_hidden");
    sf::Texture tile_Revealed = textures.getTexture("tile_revealed");
    sf::Texture mine = textures.getTexture("mine");
    sf::Texture flag = textures.getTexture("flag");
    sf::Texture debug_texture = textures.getTexture("debug");
    sf::Texture faceHappy = textures.getTexture("face_happy");
    sf::Texture faceLose = textures.getTexture("face_lose");
    sf::Texture face_Win = textures.getTexture("face_win");
    sf::Texture digitsTexture = textures.getTexture("digits");
    sf::Texture dig1 = textures.getTexture("1");
    sf::Texture dig2 = textures.getTexture("2");
    sf::Texture dig3 = textures.getTexture("3");
    sf::Texture dig4 = textures.getTexture("4");
    sf::Texture dig5 = textures.getTexture("5");
    sf::Texture dig6 = textures.getTexture("6");
    sf::Texture dig7 = textures.getTexture("7");
    sf::Texture dig8 = textures.getTexture("8");
    sf::Texture playButton = textures.getTexture("play");
    sf::Texture pauseButton = textures.getTexture("pause");
    sf::Texture leaderboardTexture = textures.getTexture("leaderboard");

    // Mines flagged counter setup
    sf::Sprite counterDigitNegative;
    sf::Sprite counterDigit1;
    sf::Sprite counterDigit2;
    sf::Sprite counterDigit3;
    counterDigitNegative.setTexture(digitsTexture);
    counterDigit1.setTexture(digitsTexture);
    counterDigit2.setTexture(digitsTexture);
    counterDigit3.setTexture(digitsTexture);
    counterDigit1.setPosition(sf::Vector2f(33, (minesTall+.5)*32));
    counterDigit2.setPosition(sf::Vector2f(54, (minesTall+.5)*32));
    counterDigit3.setPosition(sf::Vector2f(75, (minesTall+.5)*32));

    //Timer
    startTime = chrono::steady_clock::now();
    sf::Sprite timerSecDigit1;
    sf::Sprite timerSecDigit2;
    sf::Sprite timerMinDigit1;
    sf::Sprite timerMinDigit2;
    timerSecDigit1.setTexture(digitsTexture);
    timerSecDigit2.setTexture(digitsTexture);
    timerMinDigit1.setTexture(digitsTexture);
    timerMinDigit2.setTexture(digitsTexture);
    timerSecDigit1.setPosition(sf::Vector2f(width-54, (minesTall+.5)*32));
    timerSecDigit2.setPosition(sf::Vector2f(width-33, (minesTall+.5)*32));
    timerMinDigit1.setPosition(sf::Vector2f(width-97, (minesTall+.5)*32));
    timerMinDigit2.setPosition(sf::Vector2f(width-76, (minesTall+.5)*32));



    int flagsPlaced = 0;

    //Debug button:
    sf::Sprite debugButton;
    debugButton.setTexture(debug_texture);
    debugButton.setPosition(sf::Vector2f(width-304, (minesTall+.5)*32));

    // Face Sprite
    face.setTexture(faceHappy);
    face.setPosition(sf::Vector2f((width/2)-32, (minesTall+.5)*32));

    // Pause Button Sprite
    playPauseButton.setTexture(pauseButton);
    playPauseButton.setPosition(sf::Vector2f((width)-240, (minesTall+.5)*32));

    // Leaderboard Button Sprite
    leaderBoardButton.setTexture(leaderboardTexture);
    leaderBoardButton.setPosition(sf::Vector2f((width)-176, (minesTall+.5)*32));

    // Sound
    if (!clickBuffer.loadFromFile("files/sounds/shovel_sound.mp3")){
        std::cerr << "Error loading click sound file!" << std::endl;
    }
    clickSound.setBuffer(clickBuffer);

    if (!victoryBuffer.loadFromFile("files/sounds/victory.mp3")){
        std::cerr << "Error loading win sound file!" << std::endl;
    }
    victorySound.setBuffer(victoryBuffer);

    if (!buttonBuffer.loadFromFile("files/sounds/click_button.mp3")){
        std::cerr << "Error loading button sound file!" << std::endl;
    }
    buttonSound.setBuffer(buttonBuffer);

    if (!boomBuffer.loadFromFile("files/sounds/explosion.mp3")){
        std::cerr << "Error loading explosion sound file!" << std::endl;
    }
    boomSound.setBuffer(boomBuffer);


    // Initialize the Tiles and add them to the grid
    for (int curr_vert = 0; curr_vert < minesTall; curr_vert++) {
        for (int curr_horz = 0; curr_horz < minesLong; curr_horz++) {
            tileBoard[curr_vert][curr_horz] = tile(curr_horz * 32, curr_vert * 32,false,
                                                   tile_Hidden,tile_Revealed, mine, flag,dig1,
                                                   dig2,dig3, dig4, dig5, dig6, dig7, dig8);
        }
    }


    placeMines(mines);

    for (int curr_vert = 0; curr_vert < minesTall; curr_vert++) {
        for (int curr_horz = 0; curr_horz < minesLong; curr_horz++) {
            int adjacentMines = countAdjacentMines(curr_horz, curr_vert);
            tileBoard[curr_vert][curr_horz].setAdjacentMines(adjacentMines);
        }
    }

//Game Running Code
// Code that runs every frame

    while (boardWindow.isOpen()) {

        sf::Event event;
        boardWindow.clear(sf::Color::White);

        // Draw Buttons
        boardWindow.draw(debugButton);
        boardWindow.draw(face);
        boardWindow.draw(playPauseButton);
        boardWindow.draw(leaderBoardButton);


        // Counter
        flagCounterUpdate(mines-flagsPlaced, counterDigit1, counterDigit2, counterDigit3, counterDigitNegative);
        if (flagsPlaced < 0) {
            boardWindow.draw(counterDigitNegative);
        }
        boardWindow.draw(counterDigit1);
        boardWindow.draw(counterDigit2);
        boardWindow.draw(counterDigit3);

        // Time Update
        if (!isPaused && !isGameWon && !isgameOver){
            auto currentTime = chrono::steady_clock::now();
            auto elapsedTime = chrono::duration_cast<chrono::seconds>(currentTime - startTime);
            elapsedSeconds = elapsedTime.count();
            elapsedSeconds -= pausedSeconds;
            elapsedMinutes = elapsedSeconds / 60;
            elapsedSeconds %= 60;
        }
        else{

        }

        TimerUpdate(elapsedSeconds, timerSecDigit1, timerSecDigit2);
        TimerUpdate(elapsedMinutes, timerMinDigit1, timerMinDigit2);
        boardWindow.draw(timerSecDigit1);
        boardWindow.draw(timerSecDigit2);
        boardWindow.draw(timerMinDigit1);
        boardWindow.draw(timerMinDigit2);


        // Tile Generation

        if (isGameWon && !WinLeaderBoard){
            gameLeaderboard.showLeaderBoard(minesLong, minesTall, playerName, elapsedSeconds);
            WinLeaderBoard = true;
        }
        else if (isPaused){
            pause(tile_Revealed);
        }
        // Checks for Game Over
        else if (isgameOver){
            gameOver();
        }
        else{
            // Draw the Tiles
            drawBoard(face_Win, flagsPlaced, gameLeaderboard);
        }


        while (boardWindow.pollEvent(event)) {
            // Close Screen
            if (event.type == sf::Event::Closed) {
                boardWindow.close();
            }

            // Handles Clicking
            if (event.type == sf::Event::MouseButtonPressed) {
                int x = static_cast<int>(event.mouseButton.x / 32);
                int y = static_cast<int>(event.mouseButton.y / 32);


                // Handles Right Click, Control + Left Click
                if (event.mouseButton.button == sf::Mouse::Left && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                || event.mouseButton.button == sf::Mouse::Right){
                    // Checks bounds
                    if (y <= minesTall) {
                        if (!tileBoard[y][x].is_Revealed()){
                            if(tileBoard[y][x].RightClick(flag)){
                                flagsPlaced -= 1;
                                cout << "flags placed:" << flagsPlaced << endl;
                            }
                            else{
                                flagsPlaced += 1;
                                cout << "flags placed:" << flagsPlaced << endl;
                            }
                        }
                    }
                }

                // Handle left click
                else if (event.mouseButton.button == sf::Mouse::Left) {
                    // Checks if clicked on leaderboard button
                    if (event.mouseButton.x >= width-176 && event.mouseButton.x <= width-110 &&
                        event.mouseButton.y >= (minesTall+.5)*32 && event.mouseButton.y <= ((minesTall+.5)*32)+64){
                        buttonSound.play();
                        if (!isPaused){
                            isPaused = true;
                            playPauseButton.setTexture(playButton);

                            pauseStartTime = chrono::steady_clock::now();
                            pause(tile_Revealed);
                            boardWindow.display();
                            gameLeaderboard.showLeaderBoard(minesLong, minesTall, playerName, elapsedSeconds);

                            isPaused = false;
                            auto pauseEndTime = chrono::steady_clock::now();
                            pausedSeconds += chrono::duration_cast<chrono::seconds>(pauseEndTime - pauseStartTime).count();
                            playPauseButton.setTexture(pauseButton);


                        }
                        else{
                            isPaused = false;
                            playPauseButton.setTexture(pauseButton);
                            auto pauseEndTime = chrono::steady_clock::now();
                            pausedSeconds += chrono::duration_cast<chrono::seconds>(pauseEndTime - pauseStartTime).count();
                        }
                    }

                    // Checks if clicked on Pause button
                    if (event.mouseButton.x >= width-240 && event.mouseButton.x <= width-176 &&
                        event.mouseButton.y >= (minesTall+.5)*32 && event.mouseButton.y <= ((minesTall+.5)*32)+64){
                        buttonSound.play();
                        if (!isPaused){
                            isPaused = true;
                            playPauseButton.setTexture(playButton);
                            pause(tile_Revealed);
                            boardWindow.display();
                            pauseStartTime = chrono::steady_clock::now();
                        }
                        else{
                            isPaused = false;
                            playPauseButton.setTexture(pauseButton);
                            auto pauseEndTime = chrono::steady_clock::now();
                            pausedSeconds += chrono::duration_cast<chrono::seconds>(pauseEndTime - pauseStartTime).count();
                        }
                    }

                    // Checks if click in bounds of debug mode button
                    if (event.mouseButton.x >= width-304 && event.mouseButton.x <= width-240 &&
                    event.mouseButton.y >= (minesTall+.5)*32 && event.mouseButton.y <= ((minesTall+.5)*32)+64){
                        buttonSound.play();
                        if (!isDebugMode){
                            isDebugMode = true;
                        }
                        else{
                            isDebugMode = false;
                        }
                    }

                    //Checks for happy face button
                    if (event.mouseButton.x >= (width/2)-32 && event.mouseButton.x <= (width/2)+32 &&
                            event.mouseButton.y >= (minesTall+.5)*32 && event.mouseButton.y <= ((minesTall+.5)*32)+64) {
                        cout << "Reset Board!" << endl;
                        buttonSound.play();
                        sf::sleep(sf::seconds(.4));
                        initalizeBoard();
                    }

                    //Checks if Game not Over
                    if (!isgameOver){
                        // Checks if in bounds of mine
                        if (y < minesTall) {
                            tile currTile = tileBoard[y][x];

                            // If no flag, reveals tile
                            if (!tileBoard[y][x].is_Flagged()) {
                                // Check if clicked on a mine or not
                                if (!tileBoard[y][x].LeftClick(tile_Revealed)) {
                                    isgameOver = true;
                                    boomSound.play();
                                    face.setTexture(faceLose);
                                }
                                // If tile bordering mine, prints number of mines bordering, else recursively
                                // checks tiles next to it:
                                // Plays Shovel sound
                                else{
                                    if (!currTile.is_Revealed()){
                                        clickSound.play();
                                    }
                                    revealTile(x, y, tile_Revealed);
                                }
                            }
                        }
                    }
                }
            }
        }
        boardWindow.display();
    }
}

void board::placeMines(int numMines) {
    int minesPlaced = 0;
    while (minesPlaced < numMines) {
        int randomX = rand() % minesLong;
        int randomY = rand() % minesTall;
        if (!tileBoard[randomY][randomX].is_Mine()) {
            tileBoard[randomY][randomX].setMineState(true);
            minesPlaced++;
        }
    }
}

void board::drawBoard(sf::Texture &face_Happy, const int flagsPlaced, leaderboard &gameLeaderboard) {
    int unRevealeaedTileCount = 0;
    for (int curr_vert = 0; curr_vert < minesTall; curr_vert++) {
        for (int curr_horz = 0; curr_horz < minesLong; curr_horz++) {

            tile currTile = tileBoard[curr_vert][curr_horz];
            sf::Sprite currSprite = currTile.getSprite();
            boardWindow.draw(currSprite);

            // If Debug Mode is true, draws mine
            if (currTile.is_Mine() && isDebugMode){
                boardWindow.draw(currTile.getMineSprite());
            }

            // Conditions for flag to be drawn: flag is placed, tile is not revealed
            if (currTile.is_Flagged() && !currTile.is_Revealed()){
                boardWindow.draw(currTile.getFlagSprite());
            }

            if (!currTile.is_Revealed()) {
                unRevealeaedTileCount ++;
            }

            if (currTile.is_Revealed() && currTile.getAdjacentMines() > 0) {
                if (currTile.getAdjacentMines() == 1){boardWindow.draw(currTile.getSprite1());}
                else if (currTile.getAdjacentMines() == 2){boardWindow.draw(currTile.getSprite2());}
                else if (currTile.getAdjacentMines() == 3){boardWindow.draw(currTile.getSprite3());}
                else if (currTile.getAdjacentMines() == 4){boardWindow.draw(currTile.getSprite4());}
                else if (currTile.getAdjacentMines() == 5){boardWindow.draw(currTile.getSprite5());}
                else if (currTile.getAdjacentMines() == 6){boardWindow.draw(currTile.getSprite6());}
                else if (currTile.getAdjacentMines() == 7){boardWindow.draw(currTile.getSprite7());}
                else if (currTile.getAdjacentMines() == 8){boardWindow.draw(currTile.getSprite8());}
            }
        }
    }

    // Game ends in a win
    if (unRevealeaedTileCount <= mines && mines - flagsPlaced == 0){
        face.setTexture(face_Happy);
        if (!isGameWon){
            victorySound.play();
            gameLeaderboard.updateLeaderboard(playerName, elapsedSeconds);
        }
        isGameWon = true;
        isDebugMode = false;

    }
}

void board::gameOver() {
    // Reveal all mines
    for (int curr_vert = 0; curr_vert < minesTall; curr_vert++) {
        for (int curr_horz = 0; curr_horz < minesLong; curr_horz++) {
            tile currTile = tileBoard[curr_vert][curr_horz];
            boardWindow.draw(currTile.getSprite());
            if (currTile.is_Mine()) {
                boardWindow.draw(currTile.getMineSprite());
            }
            if (currTile.is_Flagged() && !currTile.is_Revealed()){
                boardWindow.draw(currTile.getFlagSprite());
            }

            if (currTile.is_Revealed() && currTile.getAdjacentMines() > 0) {
                if (currTile.getAdjacentMines() == 1){
                    boardWindow.draw(currTile.getSprite1());

                }
            }
        }
    }
}

void board::resetBoard() {
    initalizeBoard();
}

void board::flagCounterUpdate(int flagsPlaced, sf::Sprite &counterDigit1, sf::Sprite &counterDigit2,
                              sf::Sprite &counterDigit3, sf::Sprite &counterDigitNegative) {

    int digit1 = flagsPlaced / 100;
    int digit2 = (flagsPlaced / 10);
    int digit3 = flagsPlaced % 10;

    int digitWidth = 21;
    int digitHeight = 32;

    counterDigit1.setTextureRect(sf::IntRect(digit1 * digitWidth, 0, digitWidth, digitHeight));
    counterDigit2.setTextureRect(sf::IntRect(digit2 * digitWidth, 0, digitWidth, digitHeight));
    counterDigit3.setTextureRect(sf::IntRect(digit3 * digitWidth, 0, digitWidth, digitHeight));
}

void board::TimerUpdate(int time, sf::Sprite &counterDigit1, sf::Sprite &counterDigit2) {
    int digit1 = (time / 10);
    int digit2 = time % 10;

    int digitWidth = 21;
    int digitHeight = 32;

    counterDigit1.setTextureRect(sf::IntRect(digit1 * digitWidth, 0, digitWidth, digitHeight));
    counterDigit2.setTextureRect(sf::IntRect(digit2 * digitWidth, 0, digitWidth, digitHeight));
}




int board::countAdjacentMines(int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue;
            int newX = x + i;
            int newY = y + j;
            if (newX >= 0 && newX < minesLong && newY >= 0 && newY < minesTall &&
                tileBoard[newY][newX].is_Mine()) {
                count++;
            }
        }
    }
    return count;
}


void board::revealTile(int x, int y, sf::Texture &tileRevealed) {
    int adjacentMines = countAdjacentMines(x, y);

    if (tileBoard[y][x].is_Mine()) {
        totalNonMineTiles +=1 ;
        return;
    }

    if (adjacentMines > 0) {
        tileBoard[y][x].LeftClick(tileRevealed);
        totalNonMineTiles -= 1;
    }
    else{
        totalNonMineTiles -= 1;

        // Recursively reveal adjacent tiles
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                if (i == 0 && j == 0) continue;
                int newX = x + i;
                int newY = y + j;
                if (newX >= 0 && newX < minesLong && newY >= 0 && newY < minesTall &&
                    !tileBoard[newY][newX].is_Revealed() && !tileBoard[newY][newX].is_Mine()) {
                    revealTile(newX, newY, tileRevealed);
                }
                tileBoard[y][x].LeftClick(tileRevealed);
            }
        }
    }
}

void board::pause(sf::Texture &texture) {
    for (int curr_vert = 0; curr_vert < minesTall; curr_vert++) {
        for (int curr_horz = 0; curr_horz < minesLong; curr_horz++) {
            tile currTile = tileBoard[curr_vert][curr_horz];
            currTile.setSpriteTexture(texture);
            boardWindow.draw(currTile.getSprite());
        }
    }

}

