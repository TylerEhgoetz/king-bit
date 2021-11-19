#include <cassert>
#include <iomanip>
#include "position.h"

// Bitboard helper functions
void placePieceOnBitboards(Bitboard *bbs, Piece p, int sq64) {
    bbs[EMPTY].clear(sq64);
    bbs[p].set(sq64);
    if (isPawn(p)) bbs[NUM_PIECES].set(sq64);
}

void removePieceOnBitboards(Bitboard *bbs, Piece p, int sq64) {
    bbs[EMPTY].set(sq64);
    bbs[p].clear(sq64);
    if (isPawn(p)) bbs[NUM_PIECES].clear(sq64);
}

// Position implementation
Position::Position() {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        squareList[i] = (isValidSquare(i)) ? EMPTY : OFFBOARD;
    }
    bbs[EMPTY] = FULL_BB;
}

void Position::placePiece(Piece p, Square s) {
    assert(isValidPiece(p));
    assert(isValidSquare(s));
    assert(squareList[s] == EMPTY);
    // Update bitboard
    placePieceOnBitboards(bbs, p, square120to64(s));
    // Update squarelist
    squareList[s] = p;
}

Piece Position::removePiece(Square s) {
    assert(isValidSquare(s));
    Piece p = squareList[s];
    assert(isValidPiece(p));
    // Update bitboard
    removePieceOnBitboards(bbs, p, square120to64(s));
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