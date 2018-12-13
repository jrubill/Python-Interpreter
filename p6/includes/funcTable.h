#ifndef __FUNCTABLE_H__
#define __FUNCTABLE_H__

#include <map>
#include "node.h"

class FuncTable {
public:
    FuncTable() : functions() {}
    void insert(const std::string &name, const Node *n);
    bool found(const std::string &name) const;
    const Node *getEntry(const std::string &name);
private:
    std::map<const std::string, const Node*> functions;
};

#endif // __FUNCTABLE_H__
