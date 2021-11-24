#ifndef WINDOW_H
#define WINDOW_H
#include <X11/Xlib.h>
#include <iostream>
#include <string>

class Xwindow {
  Display *d;
  Window w;
  int s;
  GC gc;
  unsigned long colours[10];

  public:
  Xwindow(int width = 500, int height = 500);
  ~Xwindow();
  
  // Available Colours.
  enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown};

  // Draws a rectangle
  void fillRectangle(int x, int y, int width, int heigh, int colour=Black);

  // Draws a string
  void drawString(int x, int y, std::string msg);

};

#endif
