CXX = g++
CXXFLAGS = -Wall -O2 -Wno-narrowing
LOADLIBES = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = 	main.cpp \
	mandelbrot.cpp
OBJS = $(SRC:.cpp=.o)


mandelbrot: main.o mandelbrot.o 
	$(CXX) $^ -o mandelbrot $(LOADLIBES) $(CXXFLAGS)

mandelbrot.o: mandelbrot.cpp
main.o: main.cpp mandelbrot.o 

clean: 
	rm -rf $(OBJS)

