#include "textDisplay.h"
#include <memory>

TextDisplay::TextDisplay( Game *game) 
    : text{game} {
        auto obs = std::make_unique<Observer>(this);
        game->attach(std::move(obs));
        }

TextDisplay::~TextDisplay() {
    text->detach(this);
}

void TextDisplay::notify() {
    int rank = 8;
    out << rank;
    for (int i = 0; i < BOARD_SQ_NUM; ++i) {
        if (isValidSquare(i)) {
            char p = text->getPiece(i);
            if ((p == ' ' && rank % 2 == 0 && i % 2 == 0) ||
            (p == ' ' && rank % 2 == 1 && i % 2 != 0)) {
                out << '_';
            } else {
                out << p;
            }
            if (squareToFile(i) == FILE_H) {
                --rank;
                out << std::endl << rank;
            }
        }
    }
}
