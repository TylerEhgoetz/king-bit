#include <cassert>
#include <iomanip>
#include "bitboard.h"

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

std::ostream &operator<<(std::ostream &out, const Bitboard &bb) {
    for (int i = 0; i < CHESS_SQ_NUM; ++i) {
        out << std::setw(4) << bb.bits[i];
        if ( i % 8 == 7 ) out << std::endl;
    }
    return out;
}

