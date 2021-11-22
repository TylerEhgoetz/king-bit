#include <cassert>
#include <iomanip>
#include "bitboard.h"

// Helper Methods
chess_bits FileMask(int f) {
    chess_bits bits{};
    for (int i = 56; i >= 0; i -= 8)
        bits[i + f] = 1;
    return bits;
}

chess_bits RankMask(int r) {
    chess_bits bits{};
    int rank_start = 8 * (r - 1);
    for (int i = 0; i < 8; ++i)
        bits[rank_start + i] = 1;
    return bits;
}

//constexpr chess_bits FILE_H_MASK = getFileMask(7);

//constexpr chess_bits FILE_A_MASK = getFileMask(0);

chess_bits north(const chess_bits bits) { return bits << 8; }

chess_bits south(const chess_bits bits) { return bits >> 8; }

chess_bits west(const chess_bits bits) { return (bits >> 1) & FileMask(7).flip(); }

chess_bits east(const chess_bits bits) { return (bits << 1) & FileMask(0).flip(); }

// Bitboard Implementation
Bitboard::Bitboard() : bits{} {}

Bitboard::Bitboard(int bit) { bits.set(bit); }

Bitboard::Bitboard(std::bitset<CHESS_SQ_NUM> bitset) : bits{bitset} {}

bool Bitboard::operator==(const Bitboard &bb) const { return bits == bb.bits; }

void Bitboard::set(int bit) { bits[bit] = 1; }

void Bitboard::clear(int bit) { bits[bit] = 0; }

int Bitboard::get(int bit) const { return bits.test(bit); }

int Bitboard::count() const { return bits.count(); }

chess_bits Bitboard::getBits() const { return bits; }

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
    return CHESS_SQ_NUM;  // never reached: here to avoid the compiler warning 
}

Bitboard Bitboard::wPawnSinglePush(const Bitboard empty) const { 
    return Bitboard{north(bits) & empty.getBits()};
}

Bitboard Bitboard::bPawnSinglePush(const Bitboard empty) const { 
    return Bitboard{south(bits) & empty.getBits()};
}

Bitboard Bitboard::wPawnDoublePush(const Bitboard empty) const { 
    chess_bits singlePushes = wPawnSinglePush(empty).getBits();
    return Bitboard{north(singlePushes) & empty.getBits() & RankMask(4)};
}

Bitboard Bitboard::bPawnDoublePush(const Bitboard empty) const { 
    chess_bits singlePushes = bPawnSinglePush(empty).getBits();
    return Bitboard{south(singlePushes) & empty.getBits() & RankMask(5)};
}

Bitboard Bitboard::wPawnAttacks(const Bitboard bPieces) const {
    chess_bits attacks = north(east(bits)) | north(west(bits)); 
    return(attacks & bPieces.getBits());
}

Bitboard Bitboard::bPawnAttacks(const Bitboard wPieces) const {
    chess_bits attacks = south(east(bits)) | south(west(bits)); 
    return(attacks & wPieces.getBits());
}

Bitboard Bitboard::knightAttacks() const { 
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

Bitboard Bitboard::bishopAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::rookAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::queenAttacks() const { return EMPTY_BB; }

Bitboard Bitboard::kingAttacks() const { 
    chess_bits copy = bits;
    chess_bits attacks = east(copy) | west(copy);
    copy |= attacks;
    attacks |= north(copy) | south(copy);
    return Bitboard{attacks};
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

