#include "leaderboard.h"
#include <algorithm>

void leaderboard::loadLeaderboardFromFile() {
    ifstream file("files/leaderboard.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string timeStr;
            string name;
            if (getline(iss, timeStr, ',') && getline(iss, name)) {
                name.erase(0, name.find_first_not_of(" "));

                // Turn the time string into seconds
                int minutes = stoi(timeStr.substr(0, 2));
                int seconds = stoi(timeStr.substr(3, 2));
                int totalSeconds = minutes * 60 + seconds;

                // Add the record to the leaderboard vector
                leaderboardData.emplace_back(totalSeconds, name);
            }
        }
        file.close();
    }
}

leaderboard::leaderboard(string currPlayer) {
    currentPlayer = currPlayer;
    loadLeaderboardFromFile();
}

void leaderboard::showLeaderBoard(int minesLong, int minesTall, string &playerName, int time) {
    int height = (minesTall * 16) + 50;
    int width = (minesLong * 16);
    sf::RenderWindow Leaderboard(sf::VideoMode(width, height), "Leaderboard");

    if (!default_font.loadFromFile("files/font.ttf"))
        throw runtime_error("Unable to Load Font");

    sf::Text titleText("LEADERBOARD", default_font, 20);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    setText(titleText, (width/2), (height/2)-120);

    vector<sf::Text> leaderboardEntries;

    int rank = 1;

    for (const auto& record : leaderboardData) {
        stringstream ss;
        ss << rank << ". ";

        // Add an asterisk if the player's record is updated
        if (record.second == playerName && record.first == time) {
            ss << record.second << "*";
        } else {
            ss << record.second;
        }

        ss << ": ";

        // Format the time as "MM:SS"
        int minutes = record.first / 60;
        int seconds = record.first % 60;
        ss << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;

        sf::Text entry(ss.str(), default_font, 18);
        entry.setFillColor(sf::Color::White);
        entry.setStyle(sf::Text::Bold);
        setText(entry, (width/2), (height/2) + 20 + (rank - 1) * 30);

        leaderboardEntries.push_back(entry);
        rank++;
    }

    while (Leaderboard.isOpen()) {
        sf::Event event;

        // Close Function
        while (Leaderboard.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                Leaderboard.close();
            }
        }

        // Display the leaderboard
        Leaderboard.clear(sf::Color::Blue);
        Leaderboard.draw(titleText);
        for (const auto& entry : leaderboardEntries) {
            Leaderboard.draw(entry);
        }
        Leaderboard.display();
    }
}

void leaderboard::saveLeaderboardToFile() {
    ofstream file("files/leaderboard.txt");
    if (file.is_open()) {
        for (const auto& record : leaderboardData) {
            int minutes = record.first / 60;
            int seconds = record.first % 60;
            // Format the time
            ostringstream oss;
            oss << setw(2) << setfill('0') << minutes << ":" << setw(2) << setfill('0') << seconds;
            file << oss.str() << ", " << record.second << "\n";
        }
        file.close();
    }
}

void leaderboard::updateLeaderboard(const string &name, const int time) {
    leaderboardData.emplace_back(time, name);

    // Sort the leaderboard vector based on time
    sort(leaderboardData.begin(), leaderboardData.end(), [](const auto& a, const auto& b) {
        return a.first < b.first;
    });

    // Remove the last record if there's more than 5
    if (leaderboardData.size() > 5) {
        leaderboardData.pop_back();
    }
    saveLeaderboardToFile();
}
