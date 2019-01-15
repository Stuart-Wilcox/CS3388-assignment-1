clean:
	rm -rf main
main: main.cpp
	gcc -o main main.cpp -lX11
