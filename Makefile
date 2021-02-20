CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic

.PHONY: all
all: osh

osh: main.o parser.o executeShellCommand.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp parser.hpp command.hpp 
parser.o: parser.cpp parser.hpp
executeShellCommand.o: parser.cpp parser.hpp executeShellCommand.cpp

.PHONY: clean
clean:
	rm -rf osh *.o
