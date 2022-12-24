all : main

main: main.o Device.o
	g++ -o main main.o Device.o -I/usr/include/libevdev-1.0 -levdev -lstdc++fs

main.o: main.cpp Device.hpp
	g++ -g -c main.cpp

Device.o: Device.cpp Device.hpp
	g++ -g -c Device.cpp