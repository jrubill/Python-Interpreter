#ifndef SYMBOLTABLE__H
#define SYMBOLTABLE__H

#include <iostream>
#include <string>
#include <map>
#include <algorithm>

class Literal;

class SymbolTable {
public:
  SymbolTable() : table() {}
  bool found(const std::string &name) const;
  void insert(const std::string &name, const Literal *val);
  void setValue(const std::string& name, const Literal* val);
  const Literal* getValue(const std::string& name) const;

private:
  std::map<std::string, const Literal*> table;
};

#endif
