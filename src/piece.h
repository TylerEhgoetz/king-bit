#ifndef _PIECE_H_
#define _PIECE_H_
#include <cassert>

enum Color { WHITE, BLACK, BOTH };

enum Piece { 
    EMPTY, 
    wP, wN, wB, wR, wQ, wK, 
    bP, bN, bB, bR, bQ, bK, 
    OFFBOARD 
};

const int NUM_PIECES = 13;

const int MAX_ON_BOARD = 10;

const int PieceVal[NUM_PIECES] = {
    0,
    100, 325, 325, 550, 1000, 9999,
    100, 325, 325, 550, 1000, 9999
};

const int PieceColor[NUM_PIECES] = {
    BOTH,
    WHITE, WHITE, WHITE, WHITE, WHITE, WHITE,
    BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

const bool IsSlidingPiece[NUM_PIECES] {
    false,
    false, false, true, true, true, false,
    false, false, true, true, true, false,
};

const char PieceChar[] = {
    ' ',
    'P', 'N', 'B', 'R', 'Q', 'K',
    'p', 'n', 'b', 'r', 'q', 'k',
    '\0'
};

inline bool isValidPiece(Piece p) {
    // Produces true if the piece is not EMPTY or OFFBOARD
    return !(p == EMPTY || p == OFFBOARD);
}

inline Piece charToPiece(char piece, Color color) {
    return EMPTY; // TODO: change to real piece value when finished
}

inline Color stringToColor(std::string color) {
    Color c;
    if (color == "white") c = WHITE;
    if (color == "black") c = BLACK;
    assert(c == WHITE || c == BLACK);
    return c;
}

inline bool isPawn(Piece p) {
    return p == wP || p == bP;
}

#endif
