CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11 -pedantic

.PHONY: all
all: osh

osh: main.o parser.o executeShellCommand.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -o $@ $^

main.o: main.cpp parser.hpp command.hpp executeShellCommand.hpp
parser.o: parser.cpp parser.hpp
executeShellCommand.o: executeShellCommand.cpp command.hpp parser.hpp executeShellCommand.hpp

.PHONY: clean
clean:
	rm -rf osh *.o

testall: test1 test2 test3 test4 test5 test6 test7 test8 test9

test1:
	./osh -t < testscripts/1.singleCommand.txt &> tmp
	diff tmp testscripts/ea1.txt

test2:
	./osh -t < testscripts/2.simpleRedir.txt &> tmp
	diff tmp testscripts/ea2.txt

test3:
	./osh -t < testscripts/3.moreRedir.txt &> tmp
	diff tmp testscripts/ea3.txt

test4:
	./osh -t < testscripts/4.logicalConditional.txt &> tmp
	diff tmp testscripts/ea4.txt

test5:
	./osh -t < testscripts/5.malformed.txt &> tmp
	diff tmp testscripts/ea5.txt

test6:
	./osh -t < testscripts/6.singlePipe.txt &> tmp
	diff tmp testscripts/ea6.txt

test7:
	./osh -t < testscripts/7.moreLogical.txt &> tmp
	diff tmp testscripts/ea7.txt

test8:
	./osh -t < testscripts/8.morePipes.txt &> tmp
	diff tmp testscripts/ea8.txt

test9:
	./osh -t < testscripts/9.simplePipeAndLogical.txt &> tmp
	diff tmp testscripts/ea9.txt
