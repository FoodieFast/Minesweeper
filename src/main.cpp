
#include "welcomeWindow.h"
#include "board.h"

using namespace std;

int main() {
    TextureManager Textures;
    ifstream cfgFile("files/config.cfg");
    welcomeWindow myWelcomeWindow(cfgFile);

    if (myWelcomeWindow.display()) {
        cout << "Time to continue!!" << endl;
        board myboard(myWelcomeWindow.getWidth(), myWelcomeWindow.getHeight(), myWelcomeWindow.getMineCount(), myWelcomeWindow.getName());
        return 0;

    } else {
        cout << "Program Closed" << endl;
        return 0;

    }


}

// I d











