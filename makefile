# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean compile link
clean: 
	rm -f bin/*.o
compile:
	g++ -g -Wall -Weffc++ -std=c++11 -c -Include -o bin/test.o src/test.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Include -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
link:
	g++ -o bin/SelectionPolicy bin/test.o
run:
	./test