count: main.o
	g++ main.o -o count

main.o: main.cc
	g++ -c main.cc

doc:
	doxygen -g doxygenconfig
	doxygen doxygenconfig

all: count doc
