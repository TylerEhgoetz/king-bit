#ifndef _SQUARE_H_
#define _SQUARE_H_
#include <cassert>

const int BOARD_SQ_NUM = 120;

enum Square {
    NO_SQ, 
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3, 
    A4 = 51, B4, C4, D4, E4, F4, G4, H4, 
    A5 = 61, B5, C5, D5, E5, F5, G5, H5, 
    A6 = 71, B6, C6, D6, E6, F6, G6, H6, 
    A7 = 81, B7, C7, D7, E7, F7, G7, H7, 
    A8 = 91, B8, C8, D8, E8, F8, G8, H8
};

enum File { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, FILE_NONE };

enum Rank { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, RANK_NONE };

inline int squareToFile(Square square) {
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

inline int squareToRank(Square square) {
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

inline bool isValidSquare(Square sq120) {
    // Produces true if the square is not on FILE_NONE and not on RANK_NONE
    return !(squareToFile(sq120) == FILE_NONE || squareToRank(sq120) == RANK_NONE);
}

inline int square120to64(Square sq120) {
    assert(isValidSquare(sq120));
    return 8 * squareToRank(sq120) + squareToFile(sq120);
}

inline Square square64to120(int sq64) {
    assert(0 <= sq64 && sq64 <= 63);
    if (sq64 < 8)  return Square(A1 + sq64);
    if (sq64 < 16) return Square(A2 + sq64 % 8);
    if (sq64 < 24) return Square(A3 + sq64 % 8);
    if (sq64 < 32) return Square(A4 + sq64 % 8);
    if (sq64 < 40) return Square(A5 + sq64 % 8);
    if (sq64 < 48) return Square(A6 + sq64 % 8);
    if (sq64 < 56) return Square(A7 + sq64 % 8);
    return Square(A8 + sq64 % 8);
}

inline Square stringToSquare120(std::string square) {
    char file = square[0];
    char rank = square[1];
    Square s = Square((file - 'a' + A1) + ((rank - '1') * 10));
    assert(isValidSquare(Square(s)));
    return s;
}

inline std::string squareToString(Square s) {
    std::string ret;
    switch (squareToFile(s)) {
        case FILE_A: ret += 'A'; break;
        case FILE_B: ret += 'B'; break;
        case FILE_C: ret += 'C'; break;
        case FILE_D: ret += 'D'; break;
        case FILE_E: ret += 'E'; break;
        case FILE_F: ret += 'F'; break;
        case FILE_G: ret += 'G'; break;
        case FILE_H: ret += 'H'; break;
    }
    switch (squareToRank(s)) { 
        case RANK_1: ret += '1'; break;
        case RANK_2: ret += '2'; break;
        case RANK_3: ret += '3'; break;
        case RANK_4: ret += '4'; break;
        case RANK_5: ret += '5'; break;
        case RANK_6: ret += '6'; break;
        case RANK_7: ret += '7'; break;
        case RANK_8: ret += '8'; break;
    }
    return ret;
}

#endif
