#include <string>
#include <iostream>
#include <vector>
#include "game.h"
#include "position.h"
using namespace std;

int main() {
    vector<Game> games;
    string command;
    vector<shared_ptr<Observer>> obs;

    while (cin >> command) {
        if (command == "game") {
            string player1, player2;
            cin >> player1 >> player2;
            games.emplace_back(games.back().startNewGame(player1, player2));
        } else if (command == "setup") {
            games.back().enterSetupMode();
        } else {
            cout << "Unrecognized Command!" << endl;
        }
    }
    int score1 = 0;
    int score2 = 0;
    for (int i = 0; i < games.size(); i++) {
        score1 += games[i].getScore1();
        score2 += games[i].getScore2();
    }

    cout << "Final Score:" << endl << "White: " << score1 << endl << "Black: " << score2 << endl;
}