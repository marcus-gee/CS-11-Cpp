#
# CS 11: Makefile C++ Lab 6
#

CXX      = g++
CXXFLAGS = -Wall -Werror -std=c++14
TEST_OBJS = matrix.o testbase.o test-matrix.o

all : test-matrix

test-matrix : $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o test-matrix

test : test-matrix
	./test-matrix

clean :
	rm -rf test-matrix *.o *~

.PHONY : all clean test