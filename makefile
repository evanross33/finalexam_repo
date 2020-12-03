count: main.o
	g++ main.o -o count

main.o: main.cc
	g++ -c main.cc

doc:
	doxygen -g doxygenconfig
	doxygen doxygenconfig

check: main.cc
	cppcheck --enable=all --check-config main.cc

all: count doc
