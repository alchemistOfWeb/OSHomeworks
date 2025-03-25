CXXFLAGS = -std=c++2a

signal-echo: main.o
	g++ $(CXXFLAGS) main.o -o signal-echo -pthread

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o signal-echo
