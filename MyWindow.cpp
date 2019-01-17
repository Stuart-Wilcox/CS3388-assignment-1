#include "MyWindow.hpp"
#include <math.h>

// simple abs function
int abs(int x){
  return x > 0 ? x : -1 * x;
}

// default constructor
MyWindow::MyWindow(){
  display = XOpenDisplay((char *)0); // create a display. Connect to XServer

  // make sure that actually worked. if not, give up and print error message
  if(display == NULL){
    fprintf(stderr, "Cannot open display");
    return;
  }

  // initialize member variables
  screen = DefaultScreen(display);
  black = BlackPixel(display, screen);
  white = WhitePixel(display, screen);

  // create a root window
  rootWindow = RootWindow(display, screen);

  // use member function to create a new window
  window = createWindow();

  // tell X what input you are willing to accept, in this case Exposure, KeyPress and ButtonPress (clicking)
  XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);

  // initialize graphics context. this will be used as default graphics settings in later calls
  gc = XCreateGC(display, window, 0, 0);

  // set defaults to the window
  initializeWindow();
}

// helper function
Window MyWindow::createWindow(){
  // use X to make a window and return it
  return XCreateSimpleWindow(display, rootWindow, 300, 300, 512, 512, 5, black, white);
}

// must be called before using any graphics stuff
void MyWindow::initializeWindow(){
  // set default properties to the window
  XSetStandardProperties(display, window, "My Window", "Hi!", None, NULL, 0, NULL);
	XSetBackground(display, gc, white);
	XSetForeground(display, gc, black);
	XSetFillStyle(display, gc, FillSolid);
}

// call this to show the contents of this.draw()
void MyWindow::show(){
  // map the window, then wait until the event "expose" occurs before calling draw
  XMapWindow(display, window);

  XEvent event; // var to hold events as they come up
	KeySym key; // needed to get key input
	char text[255]; // hold key input

	while(1){
		XNextEvent(display, &event); // get an event from the window, place into 'event'. This call blocks until an event is captured

		if(event.type == Expose && event.xexpose.count == 0){
			draw();
			XFlush(display);
		}

		if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1){
			printf("You pressed the %c key!\n", text[0]);
      if(text[0] == 'q'){
        close();
        break;
      }
		}

		if(event.type == ButtonPress){
			printf("You pressed a button at (%i, %i)\n", event.xbutton.x, event.xbutton.y);
		}
  }
}

// close the window
void MyWindow::close(){
  XFreeGC(display, gc);
  XDestroyWindow(display, window);
  XCloseDisplay(display);
}

// relies on lower level drawLine to make the required shape
void MyWindow::draw(){
  // code given by assignment
  double dt = 2.0 * M_PI / 200.0;
  for(double t = 0.0; t < 2.0 * M_PI; ){

    int x1 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t));
    int y1 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t));
     t += dt;
    int x2 = 256 + (int)100.0*(1.5*cos(t) - cos(13.0*t));
    int y2 = 256 + (int)100.0*(1.5*sin(t) - sin(13.0*t));

    drawLine(x1, y1, x2, y2);
  }


  // grid
  // int x1 = 256, y1 = 256;
  //
  //
  // for(int i = 0; i < 8; i++){
  //   drawLine(x1, y1, 64 * i, 0);
  // }
  // for(int i = 0; i < 8; i++){
  //   drawLine(x1, y1, 64 * i, 512);
  // }
  // for(int i = 0; i < 8; i++){
  //   drawLine(x1, y1, 0, 64 * i);
  // }
  // for(int i = 0; i <= 8; i++){
  //   drawLine(x1, y1, 512, 64 * i);
  // }
}

// bresenham's algorithm
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

// helper for drawLine
void MyWindow::drawLineLow(int x1, int y1, int x2, int y2){
  int dx = x2 - x1;
  int dy = y2 - y1;
  int yi = 1;

  if(dy < 0){
    yi = -1;
    dy *= -1;
  }

  int D = (2 * dy) - dx;
  int y = y1;

  // walk in x
  for(int x = x1; x <= x2; x++){
    drawPixel(x, y);
    if(D > 0){
      y += yi;
      D -= 2 * dx;
    }
    D += 2 * dy;
  }
}

// helper for drawLine
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

  // walk in y
  for(int y = y1; y <= y2; y++){
    drawPixel(x, y);
    if(D > 0){
      x += xi;
      D -= 2 * dy;
    }
    D += 2 * dx;
  }
}

// light one pixel at given position
void MyWindow::drawPixel(int x, int y){
  XSetForeground(display, gc, black); // draw pixel in black
  XDrawPoint(display, window, gc, x, y); // use lower level method to colour pixel
  XFlush(display); // flush to the display (could be optimized if only done once in draw(), but not an issue for now)
}
