# Makefile for cpp

CXX = g++
LEX = flex
YACC = bison

LEXFLAGS = -Wno-unused -Wno-sign-compare
CXXFLAGS = -g -Wall -std=c++11

OBJS = main.o parse.tab.o lex.yy.o

TARGET = prog


all: $(OBJS)
	$(CXX) $(CXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp parse.y scan.l parse.tab.c lex.yy.c
	$(CXX) $(CXXFLAGS) -c main.cpp

parse.tab.c: parse.y
	$(YACC) -vtd parse.y

parse.tab.o: parse.tab.c
	$(CXX) $(CXXFLAGS) -c parse.tab.c

lex.yy.c: scan.l parse.tab.o
	$(LEX) scan.l

lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAGS) $(LEXFLAGS) -c lex.yy.c

clean:
	rm -f $(OBJS) parse.tab.c lex.yy.c parse.tab.h parse.output
	rm -f $(TARGET)

run:
	./$(TARGET)
