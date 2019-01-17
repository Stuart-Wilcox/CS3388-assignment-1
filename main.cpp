#include <stdio.h>
#include <stdlib.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

void drawPixel(Display *dis, Window win, GC gc, int x, int y, int colour){
	XSetForeground(dis, gc, colour);
	XDrawPoint(dis, win, gc, x, y);
}

Window createWindow(Display *display, Window rootWindow, int screen, int white, int black){
	return XCreateSimpleWindow(display, rootWindow, 100, 100, 1000, 1000, 5, white, black);
}

int main(int argc, char *argv[]){
	Display *display = XOpenDisplay((char *)0); //XOpenDisplay(getenv("Display"));

	if(display == NULL){
		fprintf(stderr, "Cannot open display\n");
		return 1;
	}

	int screen = DefaultScreen(display);
	int black = BlackPixel(display, screen);	/* get color black */
	int white = WhitePixel(display, screen);  /* get color white */

	Window rootWindow = RootWindow(display, screen);
	Window window = createWindow(display, rootWindow, screen, white, black);
	XSetStandardProperties(display, window, "My Window", "Hi!", None, NULL, 0, NULL);

	XSelectInput(display, window, ExposureMask | KeyPressMask | ButtonPressMask);
	GC gc = XCreateGC(display, window, 0, 0);

	XSetBackground(display, gc, black);
	XSetForeground(display, gc, white);
	XSetFillStyle(display, gc, FillSolid);

	//XDrawRectangle(display, window, gc, 100, 100, 100, white);
	XMapWindow(display, window);


/*
	for(int i = 0; i < 50; i++){
		drawPixel(display, window, gc, 100 + i, 100 + i, WhitePixel(display, screen));
	}
*/


	XEvent event;
	KeySym key;
	char text[255];

	while(1){
		XNextEvent(display, &event);

		if(event.type == Expose && event.xexpose.count == 0){
			for(int i = 0; i < 50; i++){
				drawPixel(display, window, gc, 100 + i, 100 + i, WhitePixel(display, screen));
			}
			XFlush(display);
		}

		if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key, 0) == 1){
			printf("You pressed the %c key!\n", text[0]);
		}

		if(event.type == ButtonPress){
			printf("You pressed a button at (%i, %i)\n", event.xbutton.x, event.xbutton.y);
		}
	}

	return 0;
}
