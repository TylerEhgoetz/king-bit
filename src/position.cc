#include <cassert>
#include <iomanip>
#include "position.h"

Position::Position() {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        squareList[i] = (isValidSquare(i)) ? EMPTY : OFFBOARD;
    }
}

void Position::placePiece(int p, int s) {
    assert(isValidPiece(p));
    assert(isValidSquare(s));
    squareList[s] = p;
}

int Position::removePiece(int s) {
    assert(isValidSquare(s));
    assert(isValidPiece(squareList[s]));
    int p = squareList[s];
    squareList[s] = EMPTY;
    return p;
}

std::ostream &operator<<(std::ostream &out, const Position &p) {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(i)) {
            out << std::setw(4) << p.squareList[i];
            if (squareToFile(i) == FILE_H) out << std::endl;
        }
    }
    return out;
}