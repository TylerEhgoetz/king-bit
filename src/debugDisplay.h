#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include "observer.h"
#include "game.h"
#include <memory>
#include "square.h"

extern const int BOARD_SQ_NUM;

class DebugDisplay: public Observer {
  Game *game;
  std::ostream &out = std::cout;
  std::unique_ptr<Observer> o;
  
 public:
  DebugDisplay( Game *text);
  void notify() override;
  ~DebugDisplay();
};

#endif
