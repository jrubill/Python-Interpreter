#ifndef __MCC_H__
#define __MCC_H__
#include <iostream>
#include <list>
#include <map>
#include <string.h>

class Elem {
public:
	Elem(char *n, int l, int col) : complexity(1), line_no(l), 
		col_no(col), name(new char[strlen(n)+1]) { strcpy(name, n); }
	~Elem() { delete [] name; }

	// overloaded this to use std::map
	virtual bool operator<(Elem *rhs) { return (*(int *)(this)) < (*(int *)(rhs)); }
	virtual int getComplexity() = 0;
	virtual int getGrade();
	void operator++() { complexity++; }

protected:
	int complexity, line_no, col_no;
	char *name;
};

class Func : public Elem {
public:
	Func(char *n, int l = 1, int col = 0) : Elem(n, l, col) {}
};

class Class : public Elem {
public:
	Class(char *n, int l = 1, int col = 0) : Elem(n, l, col) {}
};

class MCC {
public:
	static MCC *getInstance();
	~MCC();
	void add() { complex++; }
	int getComplex() { return complex; }
	// recursive to print list in order. I'm lazy :)
	void print() { }
private:
	std::map<std::string, Elem *> elem_map;
	std::list<Elem*> elem_list;
	int complex;
	static MCC *instance;
	MCC() : complex(0) {};
	MCC(const MCC&) = delete;
	void print(Func *f) { }
};

#endif // __MCC_H__