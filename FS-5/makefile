CXXFLAGS = -std=c++2a

manual-append: main.o
	g++ $(CXXFLAGS) main.o -o manual-append

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o manual-append
