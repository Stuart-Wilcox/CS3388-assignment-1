clean:
	rm -rf main
main: main.cpp MyWindow.hpp MyWindow.cpp
	gcc -o main main.cpp MyWindow.hpp MyWindow.cpp -lX11 -lm
