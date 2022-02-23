Main: HuffmanAlgorithm.o Main.o
	g++ -std=c++1y HuffmanAlgorithm.o Main.o -o Main

HuffmanAlgorithm.o: HuffmanAlgorithm.cpp HuffmanAlgorithm.h
	g++ -std=c++1y -c HuffmanAlgorithm.cpp

Main.o: Main.cpp
	g++ -std=c++1y -c  Main.cpp
