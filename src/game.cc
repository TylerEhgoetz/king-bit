#include "game.h"
#include "piece.h"
#include "square.h"
#include <string>
#include <iostream>

void Game::placePiece(int piece, int square) {
    p.placePiece(piece, square);
}

void Game::removePiece(int square) {
    p.removePiece(square);
}

void Game::setColour(int colour) {
    // TODO: call position setColour once created
}

int Game::getColor() {
    // TODO: call position getColour once created
}

char Game::getPiece(int square) {
    // TODO: call position getPiece once created
}

void Game::enterSetupMode() {
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            char piece;
            std::string square;
            std::cin >> piece >> square;
            placePiece(charToPiece(piece, getColor()), stringToSquare120(square));
            notifyObservers();
        } else if (command == "-") {
            std::string square;
            std::cin >> square;
            removePiece(stringToSquare120(square));
            notifyObservers();
        } else if (command == "=") {
            std::string color;
            std::cin >> color;
            setColour(stringToColor(color));
        } else if (command == "done") {
            // TODO: check valid board state
            break;
        } else {
            std::cout << "Unrecognized Command!" << std::endl;
        }
    }
}
/*
void Game::increaseScore(int color) {
    if (color == WHITE) ++score1;
    else if (color == BLACK) ++score2;
}

int Game::getScore1() {return score1;}

int Game::getScore2() {return score2;}

void Game::enterGameMode() {
    std::string command;
    while (std::cin >> command) {
        if (command == "move") {
            std::string from, to;
            std::cin >> from >> to;
        } else if (command == "resign") {
            
            break;
        } else {
            std::cout << "Unrecognized Command!" << std::endl;
        }
    }
}


Game Game::startNewGame(std::string player1, std::string player2) {

} */
