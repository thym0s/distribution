CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall -pedantic
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=distribution.cpp result.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: distribution

distribution: $(OBJS)
	$(CXX) -o distribution $(OBJS)

distribution.o: distribution.cpp distribution.h

result.o: result.cpp result.h

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) distribution
