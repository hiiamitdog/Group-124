FLAGS = -pedantic-errors -std=c++11
printCard.o: printCard.cpp printCard.h
	g++ $(FLAGS) -c printCard.cpp
printMenu.o: printMenu.cpp printMenu.h
	g++ $(FLAGS) -c printMenu.cpp
poker.o: poker.cpp printCard.h printMenu.h
	g++ $(FLAGS) -c poker.cpp
p: printCard.o printMenu.o poker.o
	g++ $(FLAGS) printCard.o printMenu.o poker.o -o p