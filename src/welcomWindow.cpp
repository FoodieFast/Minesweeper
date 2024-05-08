#include "welcomeWindow.h"

welcomeWindow::welcomeWindow(std::ifstream &configFile) {
    colCount = 0;
    rowCount = 0;
    mineCount = 0;
    if (configFile.is_open()) {
        string line;
        if (std::getline(configFile, line)) {
            std::istringstream split(line);
            split >> colCount;
        }
        if (std::getline(configFile, line)) {
            std::istringstream split(line);
            split >> rowCount;
        }
        if (std::getline(configFile, line)) {
            std::istringstream split(line);
            split >> mineCount;
        }
        configFile.close();
    }
    else
        throw std::runtime_error("Unable to open File");

    cout << "Number of columns: " << colCount << endl;
    cout << "Number of rows: " << rowCount << endl;
    cout << "Number of mines: " << mineCount<< endl;

    width = (colCount*32);
    height = (rowCount*32)+100;

    if (!default_font.loadFromFile("files/font.ttf"))
        throw runtime_error("Unable to Load Font");

    welcome_text.setFont(default_font);
    welcome_text.setCharacterSize(24);
    welcome_text.setString("WELCOME TO MINESWEEPER!");
    welcome_text.setStyle(sf::Text::Bold);
    welcome_text.setStyle(sf::Text::Underlined);
    welcome_text.setFillColor(sf::Color::White);
    setText(welcome_text, (width/2), (height/2)-150);

    enter_name_text.setFont(default_font);
    enter_name_text.setString("Enter your name:");
    enter_name_text.setFillColor(sf::Color::White);
    enter_name_text.setCharacterSize(20);
    enter_name_text.setStyle(sf::Text::Bold);
    setText(enter_name_text, (width/2), (height/2)-75);

    actual_name_text.setFont(default_font);
    actual_name_text.setFillColor(sf::Color::White);
    actual_name_text.setCharacterSize(20);
    actual_name_text.setStyle(sf::Text::Bold);
    actual_name_text.setString('|');
    setText(actual_name_text, (width/2), (height/2)-45);
}

bool welcomeWindow::display() {
    sf::RenderWindow welcomeWindow(sf::VideoMode(width, height), "Minesweeper");

    while (welcomeWindow.isOpen()) {
        sf::Event event;
        welcomeWindow.clear(sf::Color::Blue);
        welcomeWindow.draw(welcome_text);
        welcomeWindow.draw(enter_name_text);
        welcomeWindow.draw(actual_name_text);
        welcomeWindow.display();
        // Welcome
        while (welcomeWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                welcomeWindow.close();
                return false;
            }

            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char inputedSymbol = static_cast<char>(event.text.unicode);

                    //quit
                    if (inputedSymbol == '\n' && Name.length() > 0) {
                        welcomeWindow.close();
                        return true;
                    } else { // Add char to Name Display
                        charInput(Name, inputedSymbol);
                        actual_name_text.setString(Name + '|');
                        setText(actual_name_text, (width / 2), (height / 2) - 45);
                    }
                }
            }
        }
    }
}
int welcomeWindow::getHeight(){
    return height;
}

int welcomeWindow::getWidth() {
    return width;
}

int welcomeWindow::getMineCount() {
    return mineCount;
}

string welcomeWindow::getName(){
    return Name;

}



