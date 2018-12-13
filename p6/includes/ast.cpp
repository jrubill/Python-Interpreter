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
    //TableManager::getInstance().insertFunc(ident, suite);
	TableManager::getInstance().insertFunc(ident, this);
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
    if (params) {
		std::vector<Node*> args = static_cast<ArgsNode*>(params)->getArgs();
		const FuncNode *func = static_cast<const FuncNode *>(tm.getFunc(ident));
		std::vector<Node*> parameters = static_cast<ArgsNode*>(func->getParams())->getArgs();
		if (args.size() != parameters.size()) {
			std::cout << "incorrect param number\n";
			std::exception up = std::exception();
			throw up;	
		}
		//tm.pushScope();
		std::vector<const Literal*> literals;
		literals.reserve(args.size());
		for (unsigned int i = 0; i < args.size(); i++)
			literals.push_back(args[i]->eval());
		tm.pushScope();
		for (unsigned int i = 0; i < args.size(); i++)
			tm.insertSymb(static_cast<IdentNode*>(parameters[i])->getIdent(), literals[i]);
	}
	else tm.pushScope();
	tm.getSuite(ident)->eval();
	const Literal *result = tm.getEntry("__RETURN__");
    tm.popScope();
    return result;
}

const Literal *ReturnNode::eval() const {
    TableManager::getInstance().insertSymb("__RETURN__", val->eval());
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

const Literal *GreaterEqualNode::eval() const {
	return nullptr;
}
const Literal *LessEqualNode::eval() const {
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
bool LessEqualNode::getStatus() {
	const Literal *lhs = left->eval();
    const Literal *rhs = right->eval();
	return ((*lhs) <= (*rhs));
}
bool GreaterEqualNode::getStatus() {
	const Literal *lhs = left->eval();
    const Literal *rhs = right->eval();
	return ((*lhs) >= (*rhs));
}

const Literal *IfNode::eval() const {

	bool status = static_cast<CompNode*>(test)->getStatus();
	if (status) {
		ifSuite->eval();	
	}
	else {
		if (elseSuite) return elseSuite->eval();	
	}	
	return nullptr;
}

const Literal *ArgsNode::eval() const {
   // place into symbol table . . . ? 
    
   return nullptr;
}

const std::vector<Node*>& ArgsNode::getArgs() const {
	return args;
}



