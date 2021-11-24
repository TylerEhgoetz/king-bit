#include "debugDisplay.h"
#include <memory>

DebugDisplay::DebugDisplay( Game *debug) 
    : game{debug} {game->attach(this);}

DebugDisplay::~DebugDisplay() {
    game->detach(this);
}


void DebugDisplay::notify() {
    int rank = 8;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(Square(i))) {
            if (squareToFile(Square(i)) == FILE_A) {
                out << rank << ' ';
                --rank;
            }
            char p = game->getPiece(Square(i));
            if ((p == ' ' && rank % 2 == 0 && i % 2 == 0) ||
            (p == ' ' && rank % 2 == 1 && i % 2 != 0)) {
                out << '_';
            } else {
                out << p;
            }
            if (squareToFile(Square(i)) == FILE_H) out << std::endl;
        }
    }
    out << std::endl;
}
