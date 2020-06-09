#
# CS 11: Makefile C++ Lab 4
#

CXX      = g++
CXXFLAGS = -Wall -std=c++14
CONVERT_OBJS = units.o convert.o
TEST_OBJS    = units.o testbase.o hw3testunits.o

all : convert hw3testunits

convert : $(CONVERT_OBJS)
	$(CXX) $(CXXFLAGS) $(CONVERT_OBJS) -o convert

hw3testunits : $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o hw3testunits

test : hw3testunits
	./hw3testunits

clean :
	rm -rf convert hw3testunits docs *.o *~

doc : 
	doxygen

.PHONY : all clean test doc