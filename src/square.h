#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <cassert>

extern const int BOARD_SQ_NUM = 120;

enum Square { 
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3, 
    A4 = 51, B4, C4, D4, E4, F4, G4, H4, 
    A5 = 61, B5, C5, D5, E5, F5, G5, H5, 
    A6 = 71, B6, C6, D6, E6, F6, G6, H6, 
    A7 = 81, B7, C7, D7, E7, F7, G7, H7, 
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ
};

enum File { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };

enum Rank { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

int squareToFile(int square) {
    if (A1 <= square && square <= H8) {
        switch (square % 10) {
          case 1: return FILE_A;
          case 2: return FILE_B; 
          case 3: return FILE_C;
          case 4: return FILE_D;
          case 5: return FILE_E;
          case 6: return FILE_F; 
          case 7: return FILE_G;
          case 8: return FILE_H;
        }
    }
    return FILE_NONE;
}

int squareToRank(int square) {
    if ( !(square % 10 == 0 || square % 10 == 9) ) {
        switch (square / 10) {
          case 2: return RANK_1; 
          case 3: return RANK_2;
          case 4: return RANK_3;
          case 5: return RANK_4;
          case 6: return RANK_5; 
          case 7: return RANK_6;
          case 8: return RANK_7;
          case 9: return RANK_8;
        }
    }
    return RANK_NONE;
}

// TODO: square120to64(), square64to120()

int square120to64(int sq120) {
    assert(!(squareToFile(sq120) == FILE_NONE || squareToRank(sq120) == RANK_NONE));
    return 8 * squareToRank(sq120) + squareToFile(sq120);
}

int square64to120(int sq64) {
    assert(0 <= sq64 && sq64 <= 63);
    if (sq64 < 8)  return A1 + sq64;
    if (sq64 < 16) return A2 + sq64 % 8;
    if (sq64 < 24) return A3 + sq64 % 8;
    if (sq64 < 32) return A4 + sq64 % 8;
    if (sq64 < 40) return A5 + sq64 % 8;
    if (sq64 < 48) return A6 + sq64 % 8;
    if (sq64 < 56) return A7 + sq64 % 8;
    return A8 + sq64 % 8;
}


#endif