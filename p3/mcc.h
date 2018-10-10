#ifndef __MCC_H__
#define __MCC_H__
#include <iostream>
#include <list>
#include <string>
#include <stack>
#include <algorithm>

class Elem {
public:
	Elem(char *n, int l, int col) : complexity(1), line_no(l), 
		col_no(col), name(new char[strlen(n)+1]) { strcpy(name, n); }
	~Elem() { delete [] name; }
	
	int getComplexity() const { return complexity; }
	virtual char getGrade();
	
	friend std::ostream& operator<<(std::ostream &os, const Elem *e);

protected:
	int complexity, line_no, col_no;
	char *name;
};

class Func : public Elem {
public:
	Func(char *n, int l = 1, int col = 0, bool m = false) : Elem(n, l, col), method(m) {}
	void operator++() { complexity++; }
	bool isMethod() const { return (method) ? true : false; }
private:
	bool method;
};

class Class : public Elem {
public:
	Class(char *n, int l = 1, int col = 0) : Elem(n, l, col), functions() {}
	Func *append(char *name, int line_no, int col_no);
	void setComplexity();
private:
	std::list<Func *> functions;
};

class MCC {
public:
	static MCC *getInstance();
	~MCC();
	void addFunc(char*, int, int);
	void operator++() { curr_func++; }

	void startClass(char*, int, int);
	void endClass();
	void print();

private:
	// var
	std::list<Elem*> elem_list;
	Func *curr_func;
	Class *curr_class;
	bool inClass;

	// func
	MCC() : elem_list(), curr_func(nullptr), curr_class(nullptr), inClass(false) {}
	MCC(const MCC&) = delete;
};

#endif // __MCC_H__