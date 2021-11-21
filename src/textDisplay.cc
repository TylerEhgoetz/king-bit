#include "textDisplay.h"
#include <memory>

TextDisplay::TextDisplay( Game *text) 
    : game{text} {game->attach(this);}

TextDisplay::~TextDisplay() {
    game->detach(this);
}

// Needed method:
// getPiece(int) gets the piece at 120 int representation
void TextDisplay::notify() {
    int rank = 8;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(Square(i))) {
            if (squareToFile(Square(i)) == FILE_A) {
                out << rank << ' ';
                --rank;
            }
            /*char p = game->getPiece(i);
            if ((p == ' ' && rank % 2 == 0 && i % 2 == 0) ||
            (p == ' ' && rank % 2 == 1 && i % 2 != 0)) {
                out << '_';
            } else {
                out << p;
            }*/
            out << '_';
            if (squareToFile(Square(i)) == FILE_H) out << std::endl;
        }
    }
}
