# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean compile link
clean: 
	rm -f bin/*.o
compile:
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/test.o src/test.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Plan.o src/Plan.cpp
link:
	g++ -o bin/Plan bin/test.o
run:
	./test