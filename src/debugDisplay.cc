#include "debugDisplay.h"
#include <memory>

DebugDisplay::DebugDisplay( Game *text) 
    : game{text} {game->attach(this);}

DebugDisplay::~DebugDisplay() {
    game->detach(this);
}

void DebugDisplay::notify() {
    int rank = 8;
    out << rank;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(i)) {
            char p = game->getPiece(i);
            if ((p == ' ' && rank % 2 == 0 && i % 2 == 0) ||
            (p == ' ' && rank % 2 == 1 && i % 2 != 0)) {
                out << '_';
            } else {
                out << p;
            }
            if (squareToFile(i) == FILE_H) {
                --rank;
                out << std::endl << rank;
            }
        }
    }
}
