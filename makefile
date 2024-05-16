all : main

main: main.o Device.o Controller.o
	g++ -o main main.o Device.o Controller.o -I/usr/include/libevdev-1.11.0 -lstdc++fs

main.o: main.cpp Controller.hpp Device.hpp
	g++ -g -c main.cpp

Device.o: Device.cpp Device.hpp
	g++ -g -c Device.cpp

Controller.o: Controller.cpp Controller.hpp Device.hpp
	g++ -g -c Controller.cpp
