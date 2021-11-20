#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include "observer.h"
#include "game.h"
#include <memory>
#include "square.h"

extern const int BOARD_SQ_NUM;

class TextDisplay: public Observer {
  Game *text;
  std::ostream &out = std::cout;
  
 public:
  TextDisplay( Game *text);
  void notify() override;
  ~TextDisplay();
};

#endif
