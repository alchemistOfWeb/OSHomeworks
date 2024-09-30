CXXFLAGS = -std=c++2a

all: main

main: ComplexNumber.o sortComplex.o main.o
	g++ $(CXXFLAGS) main.o ComplexNumber.o sortComplex.o -o main

main.o: main.cpp ComplexNumber.h sortComplex.h
	g++ $(CXXFLAGS) main.cpp -c

ComplexNumber.o: ComplexNumber.cpp ComplexNumber.h
	g++ $(CXXFLAGS) ComplexNumber.cpp -c

sortComplex.o: sortComplex.cpp sortComplex.h
	g++ $(CXXFLAGS) sortComplex.cpp -c

clean:
	rm -f *.o main
