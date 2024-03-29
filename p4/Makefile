CCC = g++
LEX = flex
YACC = bison
CFLAGS = -g -std=c++11 -W -Wall -Weffc++ -Wextra -pedantic -O0
LEXFLAGS = -Wno-unused -Wno-sign-compare -Wno-deprecated-register

OBJS = parse.tab.o lex.yy.o ast.o symbolTable.o poolOfNodes.o main.o
TARGET = prog


all: $(OBJS)
	$(CCC) $(CFLAGS) -o $(TARGET) $(OBJS)

parse.tab.c: includes/parse.y
	$(YACC) -d includes/parse.y

parse.tab.o: parse.tab.c
	$(CCC) $(CFLAGS) -c parse.tab.c

lex.yy.c: includes/scan.l parse.tab.o
	$(LEX) includes/scan.l

lex.yy.o: lex.yy.c
	$(CCC) $(CFLAGS) $(LEXFLAGS) -c lex.yy.c

ast.o: includes/ast.cpp includes/ast.h includes/literal.h
	$(CCC) $(CFLAGS) -c includes/ast.cpp

symbolTable.o: includes/symbolTable.cpp includes/symbolTable.h
	$(CCC) $(CFLAGS) -c includes/symbolTable.cpp

poolOfNodes.o: includes/poolOfNodes.cpp includes/poolOfNodes.h \
  includes/node.h
	$(CCC) $(CFLAGS) -c includes/poolOfNodes.cpp

main.o: main.cpp
	$(CCC) $(CFLAGS) -c main.cpp

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o parse.tab.c lex.yy.c
	rm -f parse.tab.h
