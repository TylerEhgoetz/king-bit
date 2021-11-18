#ifndef GAME_H
#define GAME_H
#include "subject.h"
#include <memory>
#include <string>

class Position;
class Agent;

class Game: public Subject {
    std::shared_ptr<Position> p;
    std::unique_ptr<Agent> agents[2];
    public:
    //setup mode;
    void placePiece(int, int);
    void removePiece(int);
    void setColour(int);
    //game mode
    void startNewGame(std::string, std::string);
    void makePlayerMove(std::string);
    void makeComputerMove();
    void undoMoves(int);
};

#endif
