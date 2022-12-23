all : main

main: main.o Controller.o
	g++ -o main main.o Controller.o

main.o: main.cpp Controller.hpp
	g++ -g -c main.cpp

Controller.o: Controller.cpp Controller.hpp
	g++ -g -c Controller.cpp