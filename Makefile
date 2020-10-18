all : prog
prog : main.o screen_display.o 3d_stuff.o math_n_co.o
	g++ -o tiny_renderer main.o screen_display.o 3d_stuff.o math_n_co.o
main.o : main.cpp
	g++ -o main.o -c main.cpp
screen_display.co : screen_display.cpp
	g++ -o screen_display.o -c screen_display.cpp
3d_stuff.o : 
	g++ -o 3d_stuff.o -c 3d_stuff.cpp
math_n_co.o : 
	g++ -o math_n_co.o -c math_n_co.cpp
clean :
	rm -rf *.o