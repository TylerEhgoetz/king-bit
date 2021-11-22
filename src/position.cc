#include <bitset>
#include <cassert>
#include <iomanip>
#include "position.h"

// Bitboard helper functions
void placePieceOnBitboards(Bitboard *bbs, Piece p, int sq64) {
    bbs[EMPTY].clear(sq64);
    bbs[p].set(sq64);
    if (isPawn(p)) bbs[NUM_PIECES].set(sq64);
}

void removePieceOnBitboards(Bitboard *bbs, Piece p, int sq64) {
    bbs[EMPTY].set(sq64);
    bbs[p].clear(sq64);
    if (isPawn(p)) bbs[NUM_PIECES].clear(sq64);
}

// PieceList helper functions
void addPieceToPieceList(Position::PieceList *pl, Piece p, Square sq120) {
    int num_pieces = pl[p].count;
    assert(num_pieces < MAX_ON_BOARD);
    pl[p].squares[num_pieces] = Square(sq120);
    pl[p].count++;
}

void removePieceToPieceList(Position::PieceList *pl, Piece p, Square sq120) {
    int i = 0;
    // Get i to be the index of sq120 in pl[p].squares
    while (i < pl[p].count && pl[p].squares[i] != sq120) ++i;
    assert(pl[p].squares[i] == sq120);
    for (; pl[p].squares[i] != NO_SQ; ++i) pl[p].squares[i] = pl[p].squares[i+1];
    pl[p].count--;
}

bool isPieceOnSquare(Position::PieceList *pl, Piece p, Square sq120) {
    for (int i = 0; i < pl[p].count; ++i)
        if (pl[p].squares[i] == sq120) return true;
    return false;
}

// Move flags
const std::bitset<4> QUIET{"0000"};
const std::bitset<4> DOUBLE_PAWN_PUSH{"0001"};
const std::bitset<4> CAPTURES{"0100"};

// Move generation helper functions
void addPawnPushes(Square src, Color col, Position *p, std::vector<Position::Move> &moves) {
    assert(isValidSquare(src));
    assert(col == WHITE || col == BLACK);
    auto pawnSinglePush = (col == WHITE) ? &Bitboard::wPawnSinglePush : &Bitboard::bPawnSinglePush;
    auto pawnDoublePush = (col == WHITE) ? &Bitboard::wPawnDoublePush : &Bitboard::bPawnDoublePush;
    Bitboard empty = p->getBitboards()[EMPTY];
    Bitboard pawn{square120to64(src)};
    Bitboard singlePush = (pawn.*pawnSinglePush)(empty);
    if (singlePush.count()) {
        Square dest = square64to120(singlePush.pop());
        assert(!p->getPiece(dest));
        moves.emplace_back(src, dest, QUIET, EMPTY);
        Bitboard doublePush = (pawn.*pawnDoublePush)(empty);
        if (doublePush.count()) {
            dest = square64to120(doublePush.pop());
            assert(!p->getPiece(dest));
            moves.emplace_back(src, dest, DOUBLE_PAWN_PUSH, EMPTY);
        }
    }
}

void addPawnAttacks(Square src, Color col, Position *p, std::vector<Position::Move> &moves) {
    assert(isValidSquare(src));
    assert(col == WHITE || col == BLACK);
    auto pawnAttacks = (col == WHITE) ? &Bitboard::wPawnAttacks : &Bitboard::bPawnAttacks;
    Color opposingColor = (col == WHITE) ? BLACK : WHITE;
    Bitboard pawn{square120to64(src)};
    Bitboard opposingPieces = p->getBitboardOfColor(opposingColor);
    Square enPass = p->getEnPassSquare();
    if (enPass != NO_SQ) opposingPieces.set(square120to64(enPass));
    Bitboard attacks = (pawn.*pawnAttacks)(opposingPieces);
    while (attacks.count()) {
        Square dest = square64to120(attacks.pop());
        assert(PieceColor[p->getPiece(dest)] == opposingColor || (enPass && !p->getPiece(dest)));
        moves.emplace_back(src, dest, CAPTURES, p->getPiece(dest));
    }
}

// Position implementation
Position::Position() {
    bbs[EMPTY] = FULL_BB;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) 
        squareList[i] = (isValidSquare(Square(i))) ? EMPTY : OFFBOARD;
}

Color Position::getSideToMove() const { return metadata.to_move; }

Square Position::getEnPassSquare() const { return metadata.en_pass; }

Bitboard Position::getBitboardOfColor(Color col) const {
    std::bitset<CHESS_SQ_NUM> ret{};
    for (int piece = wP; piece < OFFBOARD; ++piece)
        if (PieceColor[piece] == col) ret |= bbs[piece].getBits();
    return Bitboard{ret};
}

const Bitboard * Position::getBitboards() const { return bbs; }

Piece Position::getPiece(Square s) const { return squareList[s]; }

bool Position::isEmpty() const { return bbs[EMPTY] == FULL_BB; }

void Position::setSideToMove(Color col) { metadata.to_move = col; }

bool Position::isConsistent() {
    for (int sq120 = 0; sq120 < BOARD_SQ_NUM; ++sq120) {
        if (isValidSquare(Square(sq120))) {
            Piece p = squareList[sq120];
            for (int piece = EMPTY; piece < OFFBOARD; ++piece) {
                if (piece == p) {
                    assert(bbs[piece].get(square120to64(Square(sq120))));
                    if (piece != EMPTY) assert(isPieceOnSquare(pieceList, Piece(piece), Square(sq120)));
                } else {
                    assert(!bbs[piece].get(square120to64(Square(sq120))));
                    assert(!isPieceOnSquare(pieceList, Piece(piece), Square(sq120)));
                }
            }
        }
    }
    return true;
}

void Position::placePiece(Piece p, Square s) {
    assert(isValidPiece(p));
    assert(isValidSquare(s));
    assert(squareList[s] == EMPTY);
    // Update bitboard
    placePieceOnBitboards(bbs, p, square120to64(s));
    // Update piecelist
    addPieceToPieceList(pieceList, p, s);
    // Update squarelist
    squareList[s] = p;
}

int Position::removePiece(Square s) {
    assert(isValidSquare(s));
    Piece p = squareList[s];
    assert(isValidPiece(p));
    // Update bitboard
    removePieceOnBitboards(bbs, p, square120to64(s));
    // Update piecelist
    removePieceToPieceList(pieceList, p, s);
    // Update squarelist
    squareList[s] = EMPTY;
    return p;
}

std::vector<Position::Move> Position::generateMoves() {
    std::vector<Position::Move> moves;
    for (int piece = wP; piece < OFFBOARD; ++piece) {
        for (int j = 0; j < pieceList[piece].count; ++j) {
            Square sq120 = Square(pieceList[piece].squares[j]);
            assert(piece == squareList[sq120]);
            switch (piece) {
                case wP: {
                    addPawnPushes(sq120, WHITE, this, moves);
                    addPawnAttacks(sq120, WHITE, this, moves);
                    break;
                }
                case wN: {
                }
                case wB: {
                }
                case wR: {
                }
                case wQ: {
                }
                case wK: {
                }
                case bP: {
                }
                case bN: {
                }
                case bB: {
                }
                case bQ: {
                }
                case bK: {
                }
                default: {
                }
            }
        }
    }
    return moves;
}

std::ostream &operator<<(std::ostream &out, const Position &p) {
    out << "Square List:" << std::endl;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(Square(i))) {
            out << std::setw(4) << p.squareList[i];
            if (squareToFile(Square(i)) == FILE_H) out << std::endl;
        }
    }
    out << std::endl;
    for (int i = 0; i < NUM_PIECES + 1; ++i) {
        if (p.bbs[i].count()) {
            out << "Piece type " << i << ":" << std::endl;
            if (0 < i && i < NUM_PIECES) {
                out << "Count = " << p.pieceList[i].count << std::endl;
                out << "Squares = ";
                for (int j = 0; j < p.pieceList[i].count; ++j) out << p.pieceList[i].squares[j] << ", ";
                out << std::endl;
            }
            out << p.bbs[i];
        }
    }
    return out;
}