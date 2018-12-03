#include <iostream>
#include <typeinfo>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include "ast.h"


const Literal* IdentNode::eval() const { 
  const Literal* val = TableManager::getInstance().getEntry(ident);
  return val;
}


AsgBinaryNode::AsgBinaryNode(Node* left, Node* right) : 
  BinaryNode(left, right) { 
  const Literal* res = right->eval();
  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().insertSymb(n, res);
}


const Literal* AsgBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* res = right->eval();

  const std::string n = static_cast<IdentNode*>(left)->getIdent();
  TableManager::getInstance().updateSymb(n, res);
  return res;
}

const Literal* UnaryNode::eval() const {
	const Literal *res = val->eval()->flip();
	return res;
}

const Literal* AddBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return (*x+*y);
}

const Literal* SubBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)-(*y));
}

const Literal* MulBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)*(*y));
}

const Literal* DivBinaryNode::eval() const { 
  if (!left || !right) {
    throw std::string("error");
  }
  const Literal* x = left->eval();
  const Literal* y = right->eval();
  return ((*x)/(*y));
}

const Literal *ModBinaryNode::eval() const {
	if (!left || !right) throw std::string("error");
	const Literal *x = left->eval();
	const Literal *y = right->eval();
	return ((*x) % (*y));
}

const Literal *IntDivBinaryNode::eval() const {
	if (!left || !right) throw std::string("error");
	const Literal *x = left->eval();
	const Literal *y = right->eval();
	return ((*x).IntDiv(*y));
}

const Literal *PowBinaryNode::eval() const {
	const Literal *x = left->eval();
	const Literal *y = right->eval();
	return ((*x).Power(*y));
}

const Literal *SubscriptNode::eval() const {
    const Literal *x = left->eval(); 
    const Literal *y = right->eval(); 
    return (*x)[*y];

}

const Literal *FuncNode::eval() const {
    suite->eval(); 
    return nullptr;
}

const Literal *SuiteNode::eval() const {
    for (const Node *n : statements) {
        n->eval();
        // check for a return statement
        if (TableManager::getInstance().checkName("__RETURN__"))
            break;
    }
    return nullptr;
}

const Literal* CallNode::eval() const {
    TableManager& tm = TableManager::getInstance();
    std::cout << "got hit!\n";
    if (!tm.checkFunc(ident)) {
        std::cout << "function " << ident << " not found" << std::endl;
        std::exception up = std::exception();
        throw up;
    }
    tm.pushScope();
    tm.getSuite(ident)->eval();
    const Literal *result = tm.getEntry("__RETURN__");
    tm.popScope();
    return result;
}

const Literal *ReturnNode::eval() const {
    return val->eval();
}

const Literal* PrintNode::eval() const {
    val->eval()->print();
    return nullptr;
}
