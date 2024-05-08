
#include "helper_functions.h"
using namespace std;

#ifndef SFML_EXAMPLE_WELCOMEWINDOW_H
#define SFML_EXAMPLE_WELCOMEWINDOW_H

class welcomeWindow{
    int colCount;
    int rowCount;
    int mineCount;


    sf::Text welcome_text;
    sf::Text enter_name_text;
    sf::Text actual_name_text;
    sf::Font default_font;


    int width;
    int height;



    string Name;

public:

    welcomeWindow(ifstream &configFile);
    bool display();

    int getWidth();
    int getHeight();
    int getMineCount();
    string getName();






};



#endif //SFML_EXAMPLE_WELCOMEWINDOW_H
