#include <cassert>
#include <iomanip>
#include "position.h"

Position::Position() {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        squareList[i] = (isValidSquare(i)) ? EMPTY : OFFBOARD;
    }
    bbs[EMPTY] = FULL_BB;
}

void Position::placePiece(Piece p, Square s) {
    assert(isValidPiece(p));
    assert(isValidSquare(s));
    // Update bitboard
    int sq64 = square120to64(s);
    bbs[EMPTY].clear(sq64);
    bbs[p].set(sq64);
    if (isPawn(p)) bbs[NUM_PIECES].set(sq64);
    // Update squarelist
    squareList[s] = p;
}

Piece Position::removePiece(Square s) {
    assert(isValidSquare(s));
    Piece p = squareList[s];
    assert(isValidPiece(p));
    // Update bitboard
    int sq64 = square120to64(s);
    bbs[EMPTY].set(sq64);
    bbs[p].clear(sq64);
    if (isPawn(p)) bbs[NUM_PIECES].clear(sq64);
    // Update squarelist
    squareList[s] = EMPTY;
    return p;
}

std::ostream &operator<<(std::ostream &out, const Position &p) {
    out << "Square List:" << std::endl;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(i)) {
            out << std::setw(4) << p.squareList[i];
            if (squareToFile(i) == FILE_H) out << std::endl;
        }
    }
    out << std::endl;
    for (int i = 0; i < NUM_PIECES + 1; ++i) {
        out << "Piece type " << i << ":" << std::endl;
        out << p.bbs[i];
    }
    return out;
}