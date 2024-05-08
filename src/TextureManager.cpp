#include "TextureManager.h"

TextureManager::TextureManager() {
    loadTexture("debug","files/images/debug.png");
    loadTexture("digits", "files/images/digits.png");
    loadTexture("face_happy", "files/images/face_happy.png");
    loadTexture("face_lose", "files/images/face_lose.png");
    loadTexture("face_win", "files/images/face_win.png");
    loadTexture("flag", "files/images/flag.png");
    loadTexture("leaderboard", "files/images/leaderboard.png");
    loadTexture("mine", "files/images/mine.png");
    loadTexture("1", "files/images/number_1.png");
    loadTexture("2", "files/images/number_2.png");
    loadTexture("3", "files/images/number_3.png");
    loadTexture("4", "files/images/number_4.png");
    loadTexture("5", "files/images/number_5.png");
    loadTexture("6", "files/images/number_6.png");
    loadTexture("7", "files/images/number_7.png");
    loadTexture("8", "files/images/number_8.png");
    loadTexture("pause", "files/images/pause.png");
    loadTexture("play", "files/images/play.png");
    loadTexture("tile_hidden", "files/images/tile_hidden.png");
    loadTexture("tile_revealed", "files/images/tile_revealed.png");
}


void TextureManager::loadTexture(string name, string fileName) {
    sf::Texture texture;
    if (!texture.loadFromFile(fileName)){
        throw runtime_error("Unable to open texture file");
    }
    textureMap[name] = texture;
}

sf::Texture TextureManager::getTexture(std::string name) {
    return textureMap[name];
}




