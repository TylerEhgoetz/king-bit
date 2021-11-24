#include "boardGUI.h"

const int SQUARE_X = 2;
const int SQUARE_Y = 0;
const int SQUARE_INCREMENT = 5;
const int PIECE_X = 43;
const int PIECE_Y = 30;
const int PIECE_INCREMENT = 50;
const int RANK_X = 10;
const int RANK_Y = 25;
const int RANK_INCREMENT = 50;

BoardGUI::BoardGUI(Game *graphics) : game{graphics} {
    game->attach(this);
    for (int i = 0; i < BOARD_SQ_NUM; i++)  {
            prev.push_back(' ');
        }
    }

BoardGUI::~BoardGUI() {game->detach(this);}

void drawBox(int x, int y, int color, Xwindow &w) {
  for (int i = x; i <= x + 4; ++i) {
    for (int j = y; j <= y + 4; ++j) {
      if (j == y || j == y + 4 || i == x || i == x + 4) {
        w.fillRectangle(i * 10, j * 10, 10, 10, color);
      }
    }
  }
}

void BoardGUI::notify() {
    const int rank_x = RANK_X;
    int rank_y = RANK_Y;
    int square_x = SQUARE_X;
    int square_y = SQUARE_Y;
    int piece_x = PIECE_X;
    int piece_y = PIECE_Y;
    int rank = 8;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(Square(i))) {
            if (squareToFile(Square(i)) == FILE_A) {
                w.drawString(rank_x, rank_y, std::to_string(rank));
                rank_y += RANK_INCREMENT;
                --rank;
            }
            char p = game->getPiece(Square(i));
            if (((rank % 2 == 0 && i % 2 == 0) || (rank % 2 == 1 && i % 2 == 1))
             && !board_drawn) {
                drawBox(square_x, square_y, w.Black, w);
            } 
            if (prev[i] != p && prev[i] != ' ') {
                w.fillRectangle(piece_x, piece_y - 10, 10, 10, w.White);
            } 
            if (p != ' ') {
                w.drawString(piece_x, piece_y, std::string(1,p));
            }
            prev[i] == p;
            square_x += SQUARE_INCREMENT;
            piece_x += PIECE_INCREMENT;
            if (squareToFile(Square(i)) == FILE_H) {
                square_y += SQUARE_INCREMENT;
                piece_y += PIECE_INCREMENT;
                piece_x = PIECE_X;
                square_x = SQUARE_X;
            }
        }
    }
    if (!board_drawn) board_drawn = true;
}
