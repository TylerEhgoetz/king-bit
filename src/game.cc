#include "game.h"
#include "piece.h"
#include "square.h"
#include <string>
#include <iostream>

void Game::placePiece(Piece piece, Square square) { p.placePiece(piece, square); }

void Game::removePiece(Square square) { p.removePiece(square); }

void Game::setColour(Color color) { p.setSideToMove(color); }

Color Game::getColor() const { return p.getSideToMove(); }

char Game::getPiece(Square s) { return PieceChar[p.getPiece(s)]; }

void Game::enterSetupMode() {
    std::string command;
    while (std::cin >> command) {
        if (command == "+") {
            char piece;
            std::string square;
            std::cin >> piece >> square;
            placePiece(charToPiece(piece), stringToSquare120(square));
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
