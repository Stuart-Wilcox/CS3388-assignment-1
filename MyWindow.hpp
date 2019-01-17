#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

class MyWindow {
  private:
  Window rootWindow;
  Window window;
  GC gc;
  Display *display;
  int screen;
  int black;
  int white;

  Window createWindow();
  void initializeWindow();
  void drawPixel(int x, int y);
  void drawLine(int x1, int y1, int x2, int y2);
  void drawLineLow(int x1, int y1, int x2, int y2);
  void drawLineHigh(int x1, int y1, int x2, int y2);

  public:
  MyWindow();
  void show();
  void draw();
};
