CXXFLAGS = -std=c++2a

do-command: main.o
	g++ $(CXXFLAGS) main.o -o do-command

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o do-command
