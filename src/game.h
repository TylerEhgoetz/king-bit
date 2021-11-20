#ifndef GAME_H
#define GAME_H
#include "subject.h"
#include "position.h"
#include <memory>
#include <string>

class Agent;

class Game: public Subject {
    Position p;
    std::unique_ptr<Agent> agents[2];
    int score1, score2;
    public:
    //setup mode
    void enterSetupMode();
    void placePiece(int, int);
    void removePiece(int);
    void setColour(int);
    int getColor();
    char getPiece(int);
    //game mode
    void enterGameMode();
    Game startNewGame(std::string, std::string);
    void makePlayerMove(std::string);
    void makeComputerMove();
    void undoMoves(int);
    void increaseScore(int);
    int getScore1();
    int getScore2();
};

#endif
