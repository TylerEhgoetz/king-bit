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

// PieceList helper functions
void addPieceToPieceList(Position::PieceList *pl, Piece p, int sq120) {
    int num_pieces = pl[p].count;
    assert(num_pieces < MAX_ON_BOARD);
    pl[p].squares[num_pieces] = Square(sq120);
    pl[p].count++;
}

void removePieceToPieceList(Position::PieceList *pl, Piece p, int sq120) {
    int i = 0;
    // Get i to be the index of sq120 in pl[p].squares
    while (i < pl[p].count && pl[p].squares[i] != sq120) ++i;
    assert(pl[p].squares[i] == sq120);
    for (; pl[p].squares[i] != NO_SQ; ++i) pl[p].squares[i] = pl[p].squares[i+1];
    pl[p].count--;
}

// Position implementation
Position::Position() {
    // Set the empty bitboard to full
    bbs[EMPTY] = FULL_BB;
    // Set all piece lists to count 0 and squares NO_SQ
    for (int i = 0; i < NUM_PIECES; ++i) {
        pieceList[i].count = 0;
        for (int j = 0; j < MAX_ON_BOARD; ++j)
            pieceList[i].squares[j] = NO_SQ;
    }
    // Set square list to EMPTY and OFFBOARD
    for (int i = 0; i < BOARD_SQ_NUM; ++i) 
        squareList[i] = (isValidSquare(i)) ? EMPTY : OFFBOARD;
}

bool Position::isConsistent() {
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(i)) {
            Piece p = squareList[i];
            // Assert that the p bitboard has the square i set to 1
            assert(bbs[p].get(square120to64(i)));
            if (p != EMPTY) {
                bool foundSquare = false;
                for (int j = 0; j < pieceList[p].count; ++j) {
                    if (pieceList[p].squares[j] == i) {
                        foundSquare = true;
                        break;
                    }
                }
                // Assert that the p pieceList contains the square i in its squarelist
                assert(foundSquare);
            }
        }
    }
}

void Position::placePiece(Piece p, Square s) {
    assert(isValidPiece(p));
    assert(isValidSquare(s));
    assert(squareList[s] == EMPTY);
    // Update bitboard
    placePieceOnBitboards(bbs, p, square120to64(s));
    // Update piecelist
    addPieceToPieceList(pieceList, p, s);
    // Update squarelist
    squareList[s] = p;
}

Piece Position::removePiece(Square s) {
    assert(isValidSquare(s));
    Piece p = squareList[s];
    assert(isValidPiece(p));
    // Update bitboard
    removePieceOnBitboards(bbs, p, square120to64(s));
    // Update piecelist
    removePieceToPieceList(pieceList, p, s);
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
        if (p.bbs[i].count()) {
            out << "Piece type " << i << ":" << std::endl;
            if (0 < i && i < NUM_PIECES) {
                out << "Count = " << p.pieceList[i].count << std::endl;
                out << "Squares = ";
                for (int j = 0; j < p.pieceList[i].count; ++j) out << p.pieceList[i].squares[j] << ", ";
                out << std::endl;
            }
            out << p.bbs[i];
        }
    }
    return out;
}