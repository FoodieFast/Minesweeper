#include "helper_functions.h"




#ifndef SFML_EXAMPLE_TEXTUREMANAGER_H
#define SFML_EXAMPLE_TEXTUREMANAGER_H


class TextureManager {
    unordered_map<string, sf::Texture> textureMap;

public:
    TextureManager();

    void loadTexture(string name, string fileName);
    sf::Texture getTexture(string name);

};


#endif //SFML_EXAMPLE_TEXTUREMANAGER_H
