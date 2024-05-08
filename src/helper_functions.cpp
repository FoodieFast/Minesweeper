#include "SFML/Graphics.hpp"
#include <cctype>
#include <iostream>
#include <stdexcept>
using namespace std;

void setText(sf::Text &text, float x, float y){
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(x, y));
}

void charInput(string &name, char character){
    if (isalpha(character) != 0){
        if (name.length() < 10) {
            if (name.length() == 0) {
                name += toupper(character);
            } else
                name += tolower(character);
        }
    }
    if (character == '\b'){
        if (name.length() != 0) {
            name.pop_back();
        }
    }
}



