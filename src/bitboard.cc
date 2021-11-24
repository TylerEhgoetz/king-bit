#include <cassert>
#include <iomanip>
#include <iostream>
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

chess_bits north(const chess_bits bits) { return bits << 8; }

chess_bits south(const chess_bits bits) { return bits >> 8; }

chess_bits west(const chess_bits bits) { return (bits >> 1) & FileMask(7).flip(); }

chess_bits east(const chess_bits bits) { return (bits << 1) & FileMask(0).flip(); }

chess_bits northWest(const chess_bits bits) { return north(west(bits)); }

chess_bits northEast(const chess_bits bits) { return north(east(bits)); }

chess_bits southWest(const chess_bits bits) { return south(west(bits)); }

chess_bits southEast(const chess_bits bits) { return south(east(bits)); }

int bitScanForward(chess_bits bits) {
    assert(bits.any());
    for (int i = 0; i < CHESS_SQ_NUM; ++i)
        if (bits.test(i))
            return i;
    return CHESS_SQ_NUM;  // never reached: here to avoid the compiler warning 
}

int bitScanReverse(chess_bits bits) {
    assert(bits.any());
    for (int i = CHESS_SQ_NUM - 1; i >= 0; --i)
        if (bits.test(i))
            return i;
    return CHESS_SQ_NUM;  // never reached: here to avoid the compiler warning 
}

int bitScan(chess_bits bits, chess_bits (*dir)(const chess_bits bits)) {
    if (dir == &northWest || dir == &north || dir == &northEast || dir == &east)
        return bitScanForward(bits);
    return bitScanReverse(bits);
}

chess_bits getRay(const chess_bits bits, chess_bits (*dir)(const chess_bits bits)) {
    chess_bits ray{};
    chess_bits next = (*dir)(bits);
    while (next.any()) {
        ray |= next;
        next = (*dir)(next);
    }
    return ray;
}

chess_bits getRayAttacks(const chess_bits bits, const chess_bits occupied, chess_bits (*dir)(const chess_bits bits)) {
   chess_bits attacks = getRay(bits, dir);
   chess_bits blocker = attacks & occupied;
   if (blocker.any()) {
      chess_bits blocker_bit{};
      blocker_bit.set(bitScan(blocker, dir));
      attacks ^= getRay(blocker_bit, dir);
   }
   return attacks;
}

// Bitboard Implementation
Bitboard::Bitboard() : bits{} {}

Bitboard::Bitboard(int bit) { bits.set(bit); }

Bitboard::Bitboard(std::bitset<CHESS_SQ_NUM> bitset) : bits{bitset} {}

bool Bitboard::operator==(const Bitboard &bb) const { return bits == bb.bits; }

bool Bitboard::operator!=(const Bitboard &bb) const { return bits != bb.bits; }

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

Bitboard Bitboard::knightAttacks(const Bitboard occupied) const { 
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

Bitboard Bitboard::bishopAttacks(const Bitboard occupied) const { 
    assert(count() == 1);
    chess_bits noWeRay = getRayAttacks(bits, occupied.getBits(), &northWest);
    chess_bits noEaRay = getRayAttacks(bits, occupied.getBits(), &northEast);
    chess_bits soEaRay = getRayAttacks(bits, occupied.getBits(), &southEast);
    chess_bits soWeRay = getRayAttacks(bits, occupied.getBits(), &southWest);
    return Bitboard{noWeRay | noEaRay | soEaRay | soWeRay};
}

Bitboard Bitboard::rookAttacks(const Bitboard occupied) const {
    assert(count() == 1);
    chess_bits noRay = getRayAttacks(bits, occupied.getBits(), &north);
    chess_bits eaRay = getRayAttacks(bits, occupied.getBits(), &east);
    chess_bits soRay = getRayAttacks(bits, occupied.getBits(), &south);
    chess_bits weRay = getRayAttacks(bits, occupied.getBits(), &west);
    return Bitboard{noRay | eaRay | soRay | weRay};
}

Bitboard Bitboard::queenAttacks(const Bitboard occupied) const { 
    assert(count() == 1);
    chess_bits rook = rookAttacks(occupied).getBits();
    chess_bits bishop = bishopAttacks(occupied).getBits();
    return Bitboard{rook | bishop};
}

Bitboard Bitboard::kingAttacks(const Bitboard occupied) const { 
    chess_bits copy = bits;
    chess_bits attacks = east(copy) | west(copy);
    copy |= attacks;
    attacks |= north(copy) | south(copy);
    return Bitboard{attacks};
}

std::ostream &operator<<(std::ostream &out, const Bitboard &bb) {
    for (int i = 56; i >= 0; i -= 8) {
        for (int j = 0; j < 8; ++j) {
            out << std::setw(4) << bb.bits[i + j];
        }
        out << std::endl;
    }

    return out;
}

