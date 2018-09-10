# Makefile

CXX = g++
LEX = flex
LEXFLAGS = -Wno-unused
CXXFLAGS = -g -Wall -std=c++11

OBJS = main.o lex.yy.o

TARGET = main

# For every .cpp/.h file, make it
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

lex.yy.c: scan.l
	$(LEX) scan.l


all: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(TARGET)
	rm -f lex.yy.c

run:
	./$(TARGET)
