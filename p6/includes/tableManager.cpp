#include "tableManager.h"

TableManager& TableManager::getInstance() {
    static TableManager instance;
    return instance;
}

const Node *TableManager::getSuite(const std::string &name) {
    int scope = currentScope;
    while (scope >= 0) {
        if (functions[scope].found(name))
            return functions[scope].getEntry(name);
        --scope;
    }
    return nullptr;
}

const Literal *TableManager::getEntry(const std::string &name) {
    int scope = currentScope;
    while (scope >= 0) {
        if (tables[scope].found(name)) return tables[scope].getValue(name);
        --scope;
    }
    return nullptr;
}

bool TableManager::checkName(const std::string &name) const {
    int scope = currentScope;
    while (scope >= 0) {
        if (tables[scope].found(name)) return true;
        --scope;
    }
    return false;
}

bool TableManager::checkFunc(const std::string &name) const {
    int scope = currentScope;
    while (scope >= 0) {
        if (functions[scope].found(name)) return true;
        -- scope;
    }
    return false;
}

void TableManager::insertSymb(const std::string &name, const Literal *l) {
    tables[currentScope].insert(name, l);
}

void TableManager::insertFunc(const std::string &name, const Node *n) {
    functions[currentScope].insert(name, n);
}

void TableManager::updateSymb(const std::string &name, const Literal *l) {
	int scope = currentScope;
	while (scope >= 0) {
		if (tables[scope].found(name)) {
			tables[scope].setValue(name, l);
			return;
		}
		--scope;
	}
	throw std::string(name + " not defined");	
}

void TableManager::pushScope() {
    tables.push_back(SymbolTable());
    functions.push_back(FuncTable());
    ++currentScope;
}

void TableManager::popScope() {
    tables.pop_back();
    functions.pop_back();
    --currentScope;
}
