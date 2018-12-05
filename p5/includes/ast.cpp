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
    TableManager::getInstance().insertFunc(ident, suite);
    return nullptr;
}

const Literal *SuiteNode::eval() const {
    for (const Node *n : statements) {
        if (n != nullptr) n->eval();
        // check for a return statement
        if (TableManager::getInstance().checkName("__RETURN__"))
            break;
    }
    return nullptr;
}

const Literal* CallNode::eval() const {
    TableManager& tm = TableManager::getInstance();
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
    (val->eval())->print(); 
    return nullptr;
}

const Literal *CompNode::eval() const {
	return nullptr;
}
const Literal *EqualNode::eval() const {
	return nullptr;
}

const Literal *LessNode::eval() const {
	return nullptr;
}

const Literal *GreaterNode::eval() const {
	return nullptr;
}

const Literal *NotEqualNode::eval() const {
	return nullptr;
}

bool CompNode::getStatus() {
    return false;
}
bool EqualNode::getStatus() {
	const Literal *lhs = left->eval();
    const Literal *rhs = right->eval();
	return ((*lhs) == (*rhs));
}
bool LessNode::getStatus() {
	const Literal *lhs = left->eval();
    const Literal *rhs = right->eval();
	return ((*lhs) < (*rhs));
}
bool GreaterNode::getStatus() {
	const Literal *lhs = left->eval();
    const Literal *rhs = right->eval();
	return ((*lhs) > (*rhs));
}
bool NotEqualNode::getStatus() {
	const Literal *lhs = left->eval();
    const Literal *rhs = right->eval();
	return !((*lhs) == (*rhs));
}

const Literal *IfNode::eval() const {
	TableManager &tm = TableManager::getInstance();

	bool status = static_cast<CompNode*>(test)->getStatus();
	if (status) {
		ifSuite->eval();	
	}
	else {
		if (elseSuite) return elseSuite->eval();	
	}	
	return nullptr;
}
