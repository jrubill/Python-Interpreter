#include "mcc.h"

int Elem::getGrade() {
    if (complexity < 6 ) return 'A';
    else if (complexity < 11) return 'B';
    else if (complexity < 21) return 'C';
    else if (complexity < 31) return 'D';
    else if (complexity < 41) return 'E';
    else return 'F';
}