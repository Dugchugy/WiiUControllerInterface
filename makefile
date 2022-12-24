all : main

main: main.o Controller.o
	g++ -o main main.o Controller.o -I/usr/include/libevdev-1.0 -levdev -lstdc++fs

main.o: main.cpp Controller.hpp
	g++ -g -c main.cpp

Controller.o: Controller.cpp Controller.hpp
	g++ -g -c Controller.cpp