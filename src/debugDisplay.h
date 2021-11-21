#ifndef DEBUG_DISPLAY_H
#define DEBUG_DISPLAY_H
#include "observer.h"
#include "game.h"
#include <memory>
#include "square.h"

extern const int BOARD_SQ_NUM;

class DebugDisplay: public Observer {
  Game *game;
  std::ostream &out = std::cout;
  
 public:
  DebugDisplay(Game *debug);
  void notify() override;
  ~DebugDisplay();
};

#endif
