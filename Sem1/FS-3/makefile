CXXFLAGS = -std=c++2a

hacker-rm: main.o
	g++ $(CXXFLAGS) main.o -o hacker-rm

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o hacker-rm
