CXXFLAGS = -std=c++2a

redirect-cin: main.o
	g++ $(CXXFLAGS) main.o -o redirect-cin

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o redirect-cin
