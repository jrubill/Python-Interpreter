#include "funcTable.h"

void FuncTable::insert(const std::string &name, const Node *n) {
    if (found(name))
        throw std::string("Redeclaration of function: " + name);
    else functions[name] = n;
}

bool FuncTable::found(const std::string &name) const {
    return (functions.find(name) != functions.end());
}

const Node *FuncTable::getEntry(const std::string &name) {
    if (!found(name)) throw std::string("function " + name + "doesn't exist!");
    else return functions[name];
}
