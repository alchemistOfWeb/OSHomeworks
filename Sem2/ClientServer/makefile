CXX = g++
CXXFLAGS = -std=c++2a -pthread -Wall -Wextra
TARGETS = client server

all: $(TARGETS)

client: client.o
	$(CXX) $(CXXFLAGS) -o client client.o

server: server.o
	$(CXX) $(CXXFLAGS) -o server server.o

client.o: client.cpp
	$(CXX) $(CXXFLAGS) -c client.cpp -o client.o

server.o: server.cpp
	$(CXX) $(CXXFLAGS) -c server.cpp -o server.o

clean:
	rm -f *.o $(TARGETS)

