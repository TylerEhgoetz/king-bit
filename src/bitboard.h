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
    void set(int bit);
    void clear(int bit);
    int get(int bit) const;
    int count() const;
    chess_bits getBitset() const;

    // flip produces the complement of the current bitboard
    Bitboard flip() const;

    // pop unsets the least significant bit that is set to 1, and returns its index
    // Requires: bits is not empty
    int pop();

    // Piece attack patterns
    Bitboard getPawnAttacks() const;
    Bitboard getKnightAttacks() const;
    Bitboard getBishopAttacks() const;
    Bitboard getRookAttacks() const;
    Bitboard getQueenAttacks() const;
    Bitboard getKingAttacks() const;

    // friends
    friend std::ostream &operator<<(std::ostream &, const Bitboard &);
};

const Bitboard EMPTY_BB = Bitboard();

const Bitboard FULL_BB = Bitboard().flip();

#endif
