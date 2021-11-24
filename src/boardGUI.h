#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "observer.h"
#include "game.h"
#include "window.h"
#include <vector>

class BoardGUI: public Observer {
 public:
  BoardGUI( Game *graphics);
  /* 
   * Notify's the graphic observer to display the section it is observing 
   * to an X server and color codes the characters for display
   */
  void notify() override;
  ~BoardGUI();
  private:
  Game *game;
  Xwindow w;
  std::vector<char> prev;
  bool board_drawn = false;
};

#endif
