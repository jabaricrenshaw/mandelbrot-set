make:
	g++ main.cpp -o mandelbrot mandelbrot.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -O2 -Wno-narrowing
