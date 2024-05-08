#include "tile.h"





tile::tile(float horizontalNum, float verticalNum, bool isMine, sf::Texture &tileHidden, sf::Texture &tileRevealed,
           sf::Texture &mine, sf::Texture &flag, sf::Texture &num1, sf::Texture &num2, sf::Texture &num3,
           sf::Texture &num4, sf::Texture &num5, sf::Texture &num6, sf::Texture &num7, sf::Texture &num8){
    tileSprite.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    tileSpriteFlag.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    tileSpriteMine.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    this->isMine = isMine;
    tileSprite.setTexture(tileHidden);
    tileSpriteFlag.setTexture(flag);
    tileSpriteMine.setTexture(mine);
    sprite1.setTexture(num1);
    sprite2.setTexture(num2);
    sprite3.setTexture(num3);
    sprite4.setTexture(num4);
    sprite5.setTexture(num5);
    sprite6.setTexture(num6);
    sprite7.setTexture(num7);
    sprite8.setTexture(num8);
    sprite1.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    sprite2.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    sprite3.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    sprite4.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    sprite5.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    sprite6.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    sprite7.setPosition(sf::Vector2f(horizontalNum, verticalNum));
    sprite8.setPosition(sf::Vector2f(horizontalNum, verticalNum));
}


tile::tile() {
    tileSprite.setPosition(sf::Vector2f(0, 0));
    isMine = false;
    tileSprite.setTexture(tileHidden);
}




sf::Sprite tile::getSprite() {
    return tileSprite;
}



bool tile::LeftClick(sf::Texture &tileRevealed) {
    isReavealed = true;
    tileSprite.setTexture(tileRevealed);
    if (isMine) {
        return false;
    }
    return true;
}



// Returns true if there is a flag already, false if no flag
bool tile::RightClick(sf::Texture &flag) {
    if (isFlagged){
        isFlagged = false;
        return true;
    }
    else{
        tileSpriteFlag.setTexture(flag);
        isFlagged = true;
        return false;
    }

}


sf::Sprite tile::getFlagSprite() {
    return tileSpriteFlag;
}

bool tile::is_Flagged() {
    return isFlagged;
}

bool tile::is_Revealed() {
    return isReavealed;
}

bool tile::is_Mine() {
    return isMine;
}

sf::Sprite tile::getMineSprite() {
    return tileSpriteMine;
}

sf::Sprite tile::getSprite1() {
    return sprite1;
}

void tile::setAdjacentMines(int amtMines) {
    adjacentMines = amtMines;
}

int tile::getAdjacentMines() const{
    return adjacentMines;
}

void tile::setMineState(bool state) {
    isMine = state;
}

sf::Sprite tile::getSprite2() {
    return sprite2;
}

sf::Sprite tile::getSprite3() {
    return sprite3;
}

sf::Sprite tile::getSprite4() {
    return sprite4;
}

sf::Sprite tile::getSprite5() {
    return sprite5;
}

sf::Sprite tile::getSprite6() {
    return sprite6;
}

sf::Sprite tile::getSprite7() {
    return sprite7;
}

sf::Sprite tile::getSprite8() {
    return sprite8;
}

void tile::setSpriteTexture(sf::Texture &texture) {
    tileSprite.setTexture(texture);
}