#ifndef _PIECE_H_
#define _PIECE_H_

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

const int MoveRules[NUM_PIECES][10] {
    {0},
    {10},                                // WHITE PAWN
    {-12, -21, -19, -8, 12, 21, 19, 8},  // WHITE KNIGHT
    {0}
};

inline bool isValidPiece(int p) {
    // Produces true if the piece is not EMPTY or OFFBOARD
    return !(p == EMPTY || p == OFFBOARD);
}

inline bool isPawn(int p) {
    return p == wP || p == bP;
}

#endif
