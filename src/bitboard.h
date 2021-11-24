#ifndef _BITBOARD_H_
#define _BITBOARD_H_
#include <bitset>
#include <iostream>

const int CHESS_SQ_NUM = 64;

typedef std::bitset<CHESS_SQ_NUM> chess_bits;

class Bitboard {
  private:
    chess_bits bits;

  public:
    Bitboard();
    Bitboard(int bit);
    Bitboard(chess_bits bitset);

    // Basic operations
    bool operator==(const Bitboard &bb) const;
    bool operator!=(const Bitboard &bb) const;
    void set(int bit);
    void clear(int bit);
    int get(int bit) const;
    int count() const;
    chess_bits getBits() const;

    // flip produces the complement of the current bitboard
    Bitboard flip() const;

    // pop unsets the least significant bit that is set to 1, and returns its index
    // Requires: bits is not empty
    int pop();

    // Piece attack patterns
    Bitboard wPawnSinglePush(const Bitboard empty) const;
    Bitboard wPawnDoublePush(const Bitboard empty) const;
    Bitboard wPawnAttacks(const Bitboard bPieces) const;

    Bitboard bPawnSinglePush(const Bitboard empty) const;
    Bitboard bPawnDoublePush(const Bitboard empty) const;
    Bitboard bPawnAttacks(const Bitboard wPieces) const;

    Bitboard knightAttacks(const Bitboard occupied) const;

    Bitboard bishopAttacks(const Bitboard occupied) const;

    Bitboard rookAttacks(const Bitboard occupied) const;

    Bitboard queenAttacks(const Bitboard occupied) const;

    Bitboard kingAttacks(const Bitboard occupied) const;

    // friends
    friend std::ostream &operator<<(std::ostream &, const Bitboard &);
};

const Bitboard EMPTY_BB = Bitboard();

const Bitboard FULL_BB = Bitboard().flip();

#endif
