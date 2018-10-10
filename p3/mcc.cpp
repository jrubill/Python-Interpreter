#include "mcc.h"

/* Elem */
char Elem::getGrade() {
    if (complexity < 6 ) return 'A';
    else if (complexity < 11) return 'B';
    else if (complexity < 21) return 'C';
    else if (complexity < 31) return 'D';
    else if (complexity < 41) return 'E';
    else return 'F';
}


std::ostream& operator<<(std::ostream &os, const Elem *e) {
	os << "\t";
	if (dynamic_cast<const Class *>(e)) os << "C ";
	else {
		if ( (static_cast<const Func *>(e))->isMethod()) os << "M ";
		else os << "F ";
	}
		return os << e->line_no << ":" << e->col_no << " " << e->name << " - (" << e->getComplexity() << ")";
}

/* Class */
Func *Class::append(char *n, int line, int column) {
    char *new_name = new char[strlen(n) + strlen(name) + 2];
    strcpy(new_name, name);
    strcat(new_name, ".");
    strcat(new_name, n);
    Func *toAdd = new Func(new_name, line, column, true);
    functions.push_back(toAdd);
    return toAdd;
}

void Class::setComplexity() {
    functions.sort([](const Func *lhs, const Func *rhs) { 
        return lhs->getComplexity() > rhs->getComplexity(); 
    });
    complexity = functions.front()->getComplexity();
}

/* MCC */

MCC *MCC::getInstance() {
    static MCC *instance;
    if (!instance) instance = new MCC();
    return instance;
}

MCC::~MCC() {
    while (!elem_list.empty()) delete elem_list.front(), elem_list.pop_front();
}

void MCC::startClass(char *n, int line, int column) {
    Class *new_class = new Class(n, line, column);
    curr_class = new_class;
    elem_list.push_back(new_class);
}

void MCC::endClass() {
    curr_class->setComplexity();
    curr_class = nullptr;
}

void MCC::addFunc(char *n, int line, int column) {
    Func *toAdd;
    if (inClass) toAdd = curr_class->append(n, line, column);
    else toAdd = new Func(n, line, column);
    curr_func = toAdd;
    elem_list.push_back(toAdd);
}

void MCC::print() {
    elem_list.sort([](const Elem *lhs, const Elem *rhs) { 
        return lhs->getComplexity() > rhs->getComplexity(); 
    });
    for (const Elem *l : elem_list)
        std::cout << l << std::endl;
        std::cout << std::endl;
}