
all:sortStr_main

sortStr_main:sortStr_main.o sortStr.o
	g++  -O4 sortStr_main.o sortStr.o -o sortStr_main --std=c++11

sortStr.o:sortStr.cpp
	g++ -c -O4 sortStr.cpp --std=c++11
sortStr_main.o:sortStr_main.cpp
	g++ -c -O4 sortStr_main.cpp --std=c++11

clean:
	rm sortStr_main sortStr.o sortStr_main.o