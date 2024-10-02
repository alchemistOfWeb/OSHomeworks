CXXFLAGS = -std=c++2a

read-file: main.o
	g++ $(CXXFLAGS) main.o -o simple-copy

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o simple-copy
