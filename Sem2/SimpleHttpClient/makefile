CXX = g++
CXXFLAGS = -std=c++2a -pthread -Wall -Wextra
TARGETS = client

all: $(TARGETS)

client: client.o
	$(CXX) $(CXXFLAGS) -o client client.o

client.o: client.cpp
	$(CXX) $(CXXFLAGS) -c client.cpp -o client.o

clean:
	rm -f *.o $(TARGETS) httpforever.html
