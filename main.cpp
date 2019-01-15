#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

void drawPixel(Display *dis, Window win, GC gc, int x, int y, int colour){
	XSetForeground(dis, gc, colour);
	XDrawPoint(dis, win, gc, x, y);
}

Window createWindow(Display *display, Window rootWindow, int screen){
	return XCreateSimpleWindow(display, rootWindow, 100, 100, 1000, 1000, 1, WhitePixel(display, screen), BlackPixel(display, screen));
}

int main(int argc, char *argv[]){
	Display *display = XOpenDisplay(getenv("Display"));
	
	if(display == NULL){
		fprintf(stderr, "Cannot open display\n");
		return 1;
	}

	int screen = DefaultScreen(display);

	Window rootWindow = RootWindow(display, screen);
	Window window = createWindow(display, rootWindow, screen);

	XSelectInput(display, window, ExposureMask | KeyPressMask);
	XMapWindow(display, window);

	
	GC gc = XCreateGC(display, rootWindow, 0, NULL);

/*
	for(int i = 0; i < 50; i++){
		drawPixel(display, window, gc, 100 + i, 100 + i, WhitePixel(display, screen));
	}
*/
	XDrawRectangle(display, window, gc, 100, 100, 100, 100);

	XMapWindow(display, window);
	XFlush(display);
	XSync(display, false);

	XEvent event;
	while(1){
		XNextEvent(display, &event);
	}

	return 0;
}
