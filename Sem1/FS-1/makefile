CXXFLAGS = -std=c++3a

all: read-file

read-file: main.o
	g++ $(CXXFLAGS) main.o -o read-file

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o read-file
