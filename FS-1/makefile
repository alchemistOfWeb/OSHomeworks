CXXFLAGS = -std=c++2a

main:  main.o
	g++ $(CXXFLAGS) main.o -o main

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o main
