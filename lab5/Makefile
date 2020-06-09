#
# CS 11: Makefile C++ Lab 5
#

CXX      = g++
CXXFLAGS = -Wall -Werror -std=c++14
TEST_OBJS = rational.o testbase.o test-rational.o

all : test-rational

test-rational : $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_OBJS) -o test-rational

test : test-rational
	./test-rational

clean :
	rm -rf test-rational *.o *~

.PHONY : all clean test