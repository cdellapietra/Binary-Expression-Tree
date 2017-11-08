# Project 4 Makefile
# Corey Della Pietra COP 4530

proj4.x : proj4_driver.cpp
	g++ -std=c++11 -Wall -pedantic -c bet.cpp
	g++ -std=c++11 -Wall -pedantic -c proj4_driver.cpp
	g++ -std=c++11 -Wall -pedantic -o proj4.x bet.o proj4_driver.o

clean :
	rm -f *.o *.x core.*
