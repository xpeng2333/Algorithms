
all:sortNum_main

sortNum_main:sortNum_main.o sortNum.o
	g++  -O4 sortNum_main.o sortNum.o -o sortNum_main --std=c++11

sortNum.o:sortNum.cpp
	g++ -c -O4 sortNum.cpp --std=c++11
sortNum_main.o:sortNum_main.cpp
	g++ -c -O4 sortNum_main.cpp --std=c++11

clean:
	rm sortNum_main sortNum.o sortNum_main.o