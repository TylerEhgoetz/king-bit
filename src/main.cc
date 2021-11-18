#include <string>
#include <iostream>
#include "game.h"
using namespace std;

int squareTo120Rep(string square) {
    return (square[0] - 'a' + 11) + ((square[1] - 48) * 10);
}

int pieceToEnum(char piece) {
    return 1; // TODO: change to real piece value when finished
}

int colourToEnum(string colour) {
    if (colour == "white") return 1;
    if (colour == "black") return 2;
    // TODO: change to real colour values when finished
}

int main() {
    auto game = make_unique<Game>();
    string command;
    string player_one, player_two;

    while (cin >> command) {
        if (command == "game") {
            cin >> player_one >> player_two;

        } else if (command == "move") {
            string from, to;
            cin >> from >> to;

        } else if (command == "setup") {
            string cmd;
            while (cin >> cmd) {
                if (cmd == "+") {
                    char piece;
                    string square;
                    cin >> piece >> square;
                    game->placePiece(piece, squareTo120Rep(square));
                } else if (cmd == "-") {
                    string square;
                    cin >> square;
                    game->removePiece(squareTo120Rep(square));
                } else if (cmd == "=") {
                    string colour;
                    cin >> colour;
                    game->setColour(colourToEnum(colour));
                } else if (cmd == "done") {
                    // TODO: check valid board state
                    break;
                } else {
                    cout << "Unrecognized Command!" << endl;
                }
            }
        } else if (command == "resign") {
            // TODO: increase opponents score.
            break;
        } else {
            cout << "Unrecognized Command!" << endl;
        }
    }
    cout << "Final Score:" << endl << "White: " << 2 << endl << "Balck: " << 1 << endl;
}