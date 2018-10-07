#ifndef __MCC_H__
#define __MCC_H__
#include <iostream>
#include <list>
#include <map>
#include <string.h>

class Elem {
public:
	Elem(std::string n, int l, int col) : complexity(1), line_no(l), 
		col_no(col), name(n) {}
	~Elem() {}

	// overloaded this to use std::map
	virtual bool operator<(Elem *rhs) { return (*(int *)(this)) < (*(int *)(rhs)); }
	virtual int getComplexity() = 0;
	virtual int getGrade();
	void operator++() { complexity++; }

protected:
	int complexity, line_no, col_no;
	std::string name;
};

class Func : public Elem {
public:
	Func(std::string n, int l = 1, int col = 0) : Elem(n, l, col) {}
	int getComplexity() { return complexity; }
};

class Class : public Elem {
public:
	Class(char *n, int l = 1, int col = 0) : Elem(n, l, col) {}
private:

};

class MCC {
public:
	static MCC *getInstance();
	~MCC();
	void add() { complex++; }
	void addFunc(std::string name, int line, int col);
	void addMethod(std::string name, int line, int col);
	void addClass(std::string name, int line, int col);
	int getComplex() { return complex; }
	void print() { }
private:
	std::map<std::string, Elem *> elem_map;
	std::list<Elem*> elem_list;
	int complex;
	static MCC *instance;

	void addToList(Elem *);
	MCC() : complex(0) {};
	MCC(const MCC&) = delete;
	void print(Func *f) { }
};

#endif // __MCC_H__