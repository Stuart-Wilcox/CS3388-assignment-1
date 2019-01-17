#include "MyWindow.hpp"
#include <math.h>

int abs(int x){
  return x > 0 ? x : -1 * x;
}

MyWindow::MyWindow(){
  display = XOpenDisplay((char *)0);

  if(display == NULL){
    fprintf(stderr, "Cannot open display");
    return;
  }

  screen = DefaultScreen(display);
  black = BlackPixel(display, screen);
  white = WhitePixel(display, screen);

  rootWindow = RootWindow(display, screen);
  window = createWindow();

  XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);

  gc = XCreateGC(display, window, 0, 0);

  initializeWindow();
}

Window MyWindow::createWindow(){
  return XCreateSimpleWindow(display, rootWindow, 300, 300, 512, 512, 5, black, white);
}

void MyWindow::initializeWindow(){
  XSetStandardProperties(display, window, "My Window", "Hi!", None, NULL, 0, NULL);
	XSetBackground(display, gc, white);
	XSetForeground(display, gc, black);
	XSetFillStyle(display, gc, FillSolid);
}

void MyWindow::show(){
  XMapWindow(display, window);

  XEvent event;
	KeySym key;
	char text[255];

	while(1){
		XNextEvent(display, &event);

		if(event.type == Expose && event.xexpose.count == 0){
			draw();
			XFlush(display);
		}

		if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1){
			printf("You pressed the %c key!\n", text[0]);
		}

		if(event.type == ButtonPress){
			printf("You pressed a button at (%i, %i)\n", event.xbutton.x, event.xbutton.y);
		}
  }
}

void MyWindow::draw(){
  double dt = 2.0 * M_PI / 200.0;
  for(double t = 0.0; t < 2.0 * M_PI; ){

    int x1 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t));
    int y1 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t));
     t += dt;
    int x2 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t));
    int y2 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t));

    drawLine(x1, y1, x2, y2);
  }
}

void MyWindow::drawLine(int x1, int y1, int x2, int y2){
  if(abs(y2 - y1) < abs(x2 - x1)){
    if(x1 > x2){
      // draw line low, reverse ends
      drawLineLow(x2, y2, x1, y1);
    }
    else {
      // draw line low, normal
      drawLineLow(x1, y1, x2, y2);
    }
  }
  else {
    if(y1 > y2){
      // draw line high, reverse ends
      drawLineHigh(x2, y2, x1, y1);
    }
    else {
      // draw line low, reverse ends
      drawLineHigh(x1, y1, x2, y2);
    }
  }
}

void MyWindow::drawLineLow(int x1, int y1, int x2, int y2){
  int dx = x2 - x1;
  int dy = y2 - y1;
  int yi = 1;

  if(dy < 0){
    yi = -1;
    dy *= dy;
  }

  int D = (2 * dy) - dx;
  int y = y1;

  for(int x = x1; x <= x2; x++){
    drawPixel(x, y);
    if(D > 0){
      y += yi;
      D -= 2 * dx;
    }
    D += 2 * dy;
  }
}

void MyWindow::drawLineHigh(int x1, int y1, int x2, int y2){
  int dx = x2 - x1;
  int dy = y2 - y1;
  int xi = 1;

  if(dx < 0){
    xi = -1;
    dx *= -1;
  }

  int D = (2 * dx) - dy;
  int x = x1;

  for(int y = y1; y <= y2; y++){
    drawPixel(x, y);
    if(D > 0){
      x += xi;
      D -= 2 * dy;
    }
    D += 2 * dx;
  }
}

void MyWindow::drawPixel(int x, int y){
  XSetForeground(display, gc, black);
  XDrawPoint(display, window, gc, x, y);
  XFlush(display);
}
