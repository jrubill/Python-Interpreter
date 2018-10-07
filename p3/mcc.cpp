#include "mcc.h"

int Elem::getGrade() {
    if (complexity < 6 ) return 'A';
    else if (complexity < 11) return 'B';
    else if (complexity < 21) return 'C';
    else if (complexity < 31) return 'D';
    else if (complexity < 41) return 'E';
    else return 'F';
}

void MCC::addFunc(std::string name, int line, int col) {
    Func *e = new Func(name, line, col);
    elem_list.push_back(e);
}

MCC* MCC::getInstance() {
    if (!instance) instance = new MCC();
    return instance;
}

void addToList(Elem *e) {

}

MCC* MCC::instance = nullptr;