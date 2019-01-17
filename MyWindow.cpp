#include "MyWindow.hpp"

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
  return XCreateSimpleWindow(display, rootWindow, 100, 100, 1000, 1000, 5, white, black);
}

void MyWindow::initializeWindow(){
  XSetStandardProperties(display, window, "My Window", "Hi!", None, NULL, 0, NULL);
	XSetBackground(display, gc, black);
	XSetForeground(display, gc, white);
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
  int x1 = 10, y1 = 10, x2 = 400, y2 = 400;
  drawLine(x1, y1, x2, y2);
}

void MyWindow::drawLine(int x1, int y1, int x2, int y2){
  /* LOGIC GOES HERE */
  for(int x = 100; x < 400; x++){
    drawPixel(x, x);
  }
}

void MyWindow::drawPixel(int x, int y){
  XSetForeground(display, gc, white);
  XDrawPoint(display, window, gc, x, y);
  XFlush(display);
}
