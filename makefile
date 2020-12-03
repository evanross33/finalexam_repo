count: main.o
	g++ main.o -o count

main.o: main.cc
	g++ -c main.cc

doc:
	doxygen -g doxygenconfig
	doxygen doxygenconfig

check: Source1.cpp
	cppcheck --enable=all --check-config Source1.cpp
	g++ Source1.cpp -o a.out
	valgrind -v ./a.out

all: count doc
