# Please implement your Makefile rules and targets below.
# Customize this file to define how to build your project.
all: clean compile link run

clean: 
	rm -f bin/*.o bin/test

bin:
	mkdir -p bin

compile:
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/SelectionPolicy.o src/SelectionPolicy.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Facility.o src/Facility.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/plan.o src/plan.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/test.o src/test.cpp

link:
	g++ -o bin/test bin/SelectionPolicy.o bin/Facility.o bin/Settlement.o bin/plan.o bin/test.o

run:
	./bin/test
