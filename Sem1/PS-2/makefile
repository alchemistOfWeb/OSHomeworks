CXXFLAGS = -std=c++2a

interactive-shell: main.o
	g++ $(CXXFLAGS) main.o -o interactive-shell

main.o: main.cpp
	g++ $(CXXFLAGS) main.cpp -c

clean:
	rm -f *.o interactive-shell
