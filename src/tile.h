#include "SFML/Graphics.hpp"
#include "TextureManager.h"

#include <string>
#include <iostream>



#ifndef SFML_EXAMPLE_TILE_H
#define SFML_EXAMPLE_TILE_H


class tile {
    sf::Sprite tileSprite;
    sf::Texture tileHidden;
    sf::Texture bruh;
    sf::Sprite tileSpriteFlag;
    sf::Sprite tileSpriteMine;
    sf::Sprite sprite1;
    sf::Sprite sprite2;
    sf::Sprite sprite3;
    sf::Sprite sprite4;
    sf::Sprite sprite5;
    sf::Sprite sprite6;
    sf::Sprite sprite7;
    sf::Sprite sprite8;
    bool isMine = false;

    int adjacentMines;
    bool isReavealed = false;
    bool isFlagged = false;


public:

    tile(float horizontalNum, float verticalNum, bool isMine, sf::Texture &tileHidden, sf::Texture &tileRevealed,
         sf::Texture &mine, sf::Texture &flag, sf::Texture &num1, sf::Texture &num2, sf::Texture &num3,
         sf::Texture &num4, sf::Texture &num5, sf::Texture &num6, sf::Texture &num7, sf::Texture &num8);
    tile();
    bool LeftClick(sf::Texture &tileRevealed);
    bool RightClick(sf::Texture &flag);
    bool is_Flagged();
    bool is_Revealed();
    bool is_Mine();
    void setAdjacentMines(int amtMines);
    void setMineState(bool state);
    void setSpriteTexture(sf::Texture &texture);





    sf::Sprite getSprite();
    sf::Sprite getFlagSprite();
    sf::Sprite getMineSprite();
    sf::Sprite getSprite1();
    sf::Sprite getSprite2();
    sf::Sprite getSprite3();
    sf::Sprite getSprite4();
    sf::Sprite getSprite5();
    sf::Sprite getSprite6();
    sf::Sprite getSprite7();
    sf::Sprite getSprite8();

    int getAdjacentMines() const;








};


#endif //SFML_EXAMPLE_TILE_H
