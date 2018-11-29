#ifndef __TABLEMANAGER_H__
#define __TABLEMANAGER_H__

#include "symbolTable.h"
#include "funcTable.h"
#include "node.h"
#include <vector>

class TableManager {
public:
    static TableManager& getInstance();
    const Literal *getEntry(const std::string& name);
    const Node *getSuite(const std::string& name);

    void insertSymb(const std::string &name, const Literal *l);
    void insertFunc(const std::string &name, const Node *n);

    bool checkName(const std::string &name) const;
    bool checkFunc(const std::string &name) const;


    void updateSymb(const std::string &name, const Literal *l);
    void pushScope();
    void popScope();
    void display() const;

private:
    int currentScope;
    // todo: change these to lists
    std::vector<SymbolTable> tables;
    std::vector<FuncTable> functions;
    TableManager() : currentScope(0), tables(), functions() {
        tables.push_back(SymbolTable());
        functions.push_back(FuncTable());
    }

};

#endif // __TABLEMANAGER_H__
