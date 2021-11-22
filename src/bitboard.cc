#include <cassert>
#include <iomanip>
#include "bitboard.h"

// Helper Methods
chess_bits getFileMask(int f) {
    chess_bits bits{};
    for (int i = 56; i >= 0; i -= 8)
        bits[i + f] = 1;
    return bits;
}

chess_bits north(const chess_bits bits) { return bits << 8; }

chess_bits south(const chess_bits bits) { return bits >> 8; }

chess_bits west(const chess_bits bits) { return (bits >> 1) & getFileMask(7).flip(); }

chess_bits east(const chess_bits bits) { return (bits << 1) & getFileMask(0).flip(); }

// Bitboard Implementation
Bitboard::Bitboard() : bits{} {}

Bitboard::Bitboard(int bit) { bits.set(bit); }

Bitboard::Bitboard(std::bitset<CHESS_SQ_NUM> bitset) : bits{bitset} {}

void Bitboard::set(int bit) { bits[bit] = 1; }

void Bitboard::clear(int bit) { bits[bit] = 0; }

int Bitboard::get(int bit) const { return bits.test(bit); }

int Bitboard::count() const { return bits.count(); }

chess_bits Bitboard::getBitset() const { return bits; }

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

Bitboard Bitboard::getKnightAttacks() const { 
    chess_bits noNoWe = north(north(west(bits)));
    chess_bits noNoEa = north(north(east(bits)));
    chess_bits eaEaNo = east(east(north(bits)));
    chess_bits eaEaSo = east(east(south(bits)));
    chess_bits soSoEa = south(south(east(bits)));
    chess_bits soSoWe = south(south(west(bits)));
    chess_bits weWeSo = west(west(south(bits)));
    chess_bits weWeNo = west(west(north(bits)));
    return Bitboard{noNoWe | noNoEa | eaEaNo | eaEaSo | soSoEa | soSoWe | weWeNo | weWeSo};
}

Bitboard Bitboard::getBishopAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::getRookAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::getQueenAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::getKingAttacks() const { 
    chess_bits copy = bits;
    chess_bits attacks = east(copy) | west(copy);
    copy |= attacks;
    attacks |= north(copy) | south(copy);
    return attacks;
}

std::ostream &operator<<(std::ostream &out, const Bitboard &bb) {
    /* 
    for (int i = 0; i < CHESS_SQ_NUM; ++i) {
        out << std::setw(4) << bb.bits[i];
        if ( i % 8 == 7 ) out << std::endl;
    }
    
    for (int i = CHESS_SQ_NUM - 1; i >= 0; --i) {
        out << std::setw(4) << bb.bits[i];
        if ( i % 8 == 0 ) out << std::endl;
    }
    */
    for (int i = 56; i >= 0; i -= 8) {
        for (int j = 0; j < 8; ++j) {
            out << std::setw(4) << bb.bits[i + j];
        }
        out << std::endl;
    }

    return out;
}

