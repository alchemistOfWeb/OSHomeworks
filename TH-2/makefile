CXX = g++
CXXFLAGS = -std=c++2a -pthread -fPIC
LIB_NAME = libparallelScheduler.so
DEMO_NAME = demo-application

all: library demo-application

library: parallelScheduler.o
	$(CXX) $(CXXFLAGS) -shared -o $(LIB_NAME) parallelScheduler.o

parallelScheduler.o: parallelScheduler.cpp parallelScheduler.h
	$(CXX) $(CXXFLAGS) -c parallelScheduler.cpp -o parallelScheduler.o

demo-application: library demo.o
	$(CXX) $(CXXFLAGS) -o $(DEMO_NAME) demo.o -L. -lparallelScheduler -Wl,-rpath=.

demo.o: demo.cpp parallelScheduler.h
	$(CXX) $(CXXFLAGS) -c demo.cpp -o demo.o

clean:
	rm -f *.o $(LIB_NAME) $(DEMO_NAME)

