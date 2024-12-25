CXXFLAGS = -std=c++2a

array-summary: main.o
	g++ $(CXXFLAGS) main.o -o array-summary -pthread

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o array-summary
