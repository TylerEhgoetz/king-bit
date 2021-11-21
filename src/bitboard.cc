#include <cassert>
#include <iomanip>
#include "bitboard.h"

// Helper Methods
Bitboard north(const Bitboard bb) {
    assert(bb.count() == 1);
    Bitboard ret{bb};
    int index = ret.pop();
    ret.set(index + 8);
    return ret;
}

// Bitboard Implementation
Bitboard::Bitboard() : bits{} {}

Bitboard::Bitboard(int bit) { bits.set(bit); }

void Bitboard::set(int bit) { bits[bit] = 1; }

void Bitboard::clear(int bit) { bits[bit] = 0; }

int Bitboard::get(int bit) const { return bits.test(bit); }

int Bitboard::count() const { return bits.count(); }

Bitboard Bitboard::flip() const { 
    Bitboard bb{*this};
    bb.bits.flip();
    return bb; 
}

int Bitboard::pop() { 
    assert(bits.any());
    for (int i = 0; i < CHESS_SQ_NUM; ++i) {
        if (bits.test(i)) {
            bits[i] = 0;
            return i;
        }
    }
}

Bitboard Bitboard::getPawnAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::getKnightAttacks() const { return north(*this); }

Bitboard Bitboard::getBishopAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::getRookAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::getQueenAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::getKingAttacks() const { return EMPTY_BB; }

std::ostream &operator<<(std::ostream &out, const Bitboard &bb) {
    /* 
    for (int i = 0; i < CHESS_SQ_NUM; ++i) {
        out << std::setw(4) << bb.bits[i];
        if ( i % 8 == 7 ) out << std::endl;
    }
    */
    for (int i = CHESS_SQ_NUM - 1; i >= 0; --i) {
        out << std::setw(4) << bb.bits[i];
        if ( i % 8 == 0 ) out << std::endl;
    }
    return out;
}

