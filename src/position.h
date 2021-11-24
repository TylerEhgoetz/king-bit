#ifndef _POSITION_H_
#define _POSITION_H_
#include <iostream>
#include <vector>
#include "piece.h"
#include "square.h"
#include "bitboard.h"

class Position {
  public:
    struct PieceList {
      int count;
      int squares[MAX_ON_BOARD];
      PieceList() : count{0}, squares{0} {}
    };

    struct MetaData {
      Color to_move;
      bool castling_rights[4]; 
      Square en_pass;
      int fifty_moves;
      MetaData() : to_move{WHITE}, castling_rights{true, true, true, true}, en_pass{NO_SQ}, fifty_moves{0} {}
    };

    struct Move {
      Square from;
      Square to;
      std::bitset<4> flags;
      Piece piece_captured;
      Move(Square f, Square t, std::bitset<4> fl, Piece pc) : from{f}, to{t}, flags{fl}, piece_captured{pc} {}
    };

    // Default constructor initializes the squareList
    Position();

    // Getter methods
    Color getSideToMove() const;
    Square getEnPassSquare() const;
    Bitboard getBitboardOfColor(Color col) const;
    const Bitboard * getBitboards() const;
    Piece getPiece(Square s) const;
    bool isEmpty() const;

    // Setter methods
    void setSideToMove(Color col);

    // Verifies that the bitboards, squarelist and piecelist are consistent with eachother
    bool isConsistent();

    // placePiece puts the given piece on the given square
    // Requires: 
    //  * piece is not EMPTY or OFFBOARD
    //  * square is a valid EMPTY square on the chess board
    void placePiece(Piece, Square);

    // removePiece removes and returns the piece on the given square
    // Requires:
    //  * square is a valid square on the chess board
    //  * the piece occupying the square is not EMPTY of OFFBOARD
    int removePiece(Square);

    // makeMove executed the given move on the current position
    // Requires: the given move is valid from the current position
    void makeMove(Move);

    // generateMoves produces a vector of all possible legal moves from the current position
    std::vector<Move> generateMoves();

    // Prints the pieces on each valid square
    friend std::ostream &operator<<(std::ostream &, const Position &);
    friend std::ostream &operator<<(std::ostream &, const Move &);

  private:
    // There is one Bitboard for each piece type, plus one extra for all pawns
    Bitboard bbs[NUM_PIECES + 1];
    PieceList pieceList[NUM_PIECES];
    Piece squareList[BOARD_SQ_NUM];
    MetaData metadata;

    // These methods are used for move generation, and DO NOT CONSIDER CHECKS
    void  addPawnMovesFrom(Square, std::vector<Move> &) const;
    void addPieceMovesFrom(Square, std::vector<Move> &) const;
};

#endif
