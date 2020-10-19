all : prog
prog : main.o screen_display.o 3d_stuff.o math_n_co.o
	g++ -std=c++11 -o tiny_renderer main.o screen_display.o 3d_stuff.o math_n_co.o
main.o : main.cpp
	g++ -std=c++11 -o main.o -c main.cpp
screen_display.o : screen_display.cpp
	g++ -std=c++11 -o screen_display.o -c screen_display.cpp
3d_stuff.o : 3d_stuff.cpp
	g++ -std=c++11 -o 3d_stuff.o -c 3d_stuff.cpp
math_n_co.o : math_n_co.cpp
	g++ -std=c++11 -o math_n_co.o -c math_n_co.cpp
clean :
	rm -rf *.o
