CXX = g++
CXXFLAGS = -std=c++2a -pthread -Wall -Wextra
TARGET = philosophers

all: $(TARGET)

$(TARGET): philosophers.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) philosophers.o -lrt

philosophers.o: philosophers.cpp
	$(CXX) $(CXXFLAGS) -c philosophers.cpp -o philosophers.o

clean: 
	rm -f *.o $(TARGET)
