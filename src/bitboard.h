#ifndef _BITBOARD_H_
#define _BITBOARD_H_
#include <bitset>
#include <iostream>

const int CHESS_SQ_NUM = 64;

class Bitboard {
  private:
    std::bitset<CHESS_SQ_NUM> bits;

  public:
    // Default constructor constructs the empty bitboard
    Bitboard();

    // Constructor constructs a bitboard with the indicated bit set
    Bitboard(int bit);

    // Basic operations
    void set(int bit);
    void clear(int bit);
    int get(int bit) const;
    int count() const;

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
