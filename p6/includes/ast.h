#pragma once

//  Declarations for a calculator that builds an AST
//  and a graphical representation of the AST.
//  by Brian Malloy

#include <iostream>
#include <string>
#include <map>
#include "literal.h"
#include "tableManager.h"
extern void yyerror(const char*);
extern void yyerror(const char*, const char);

class IdentNode : public Node {
public:
  IdentNode(const std::string id) : Node(), ident(id) { } 
  virtual ~IdentNode() {}
  const std::string getIdent() const { return ident; }
  virtual const Literal* eval() const;
private:
  std::string ident;
};

class BinaryNode : public Node {
public:
  BinaryNode(Node* l, Node* r) : Node(), left(l), right(r) {}
  virtual const Literal* eval() const = 0;
  Node* getLeft()  const { return left; }
  Node* getRight() const { return right; }
  BinaryNode(const BinaryNode&) = delete;
  BinaryNode& operator=(const BinaryNode&) = delete;
protected:
  Node *left;
  Node *right;
};

class UnaryNode : public Node {
public:
	UnaryNode(Node *_val) : val(_val) {}
    virtual ~UnaryNode() {}	
    virtual const Literal *eval() const;
    UnaryNode(const UnaryNode&) = delete;
    UnaryNode& operator=(const UnaryNode&) = delete;

private:
	Node *val;
};

class AsgBinaryNode : public BinaryNode {
public:
  AsgBinaryNode(Node* left, Node* right);
  virtual const Literal* eval() const;
};

class AddBinaryNode : public BinaryNode {
public:
  AddBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class SubBinaryNode : public BinaryNode {
public:
  SubBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class MulBinaryNode : public BinaryNode {
public:
  MulBinaryNode(Node* left, Node* right) : BinaryNode(left, right) {}
  virtual const Literal* eval() const;
};

class DivBinaryNode : public BinaryNode {
public:
  DivBinaryNode(Node* left, Node* right) : BinaryNode(left, right) { }
  virtual const Literal* eval() const;
};

class ModBinaryNode : public BinaryNode {
public:
	ModBinaryNode(Node *left, Node *right) : BinaryNode(left, right) {}
	virtual const Literal *eval() const;
};

class IntDivBinaryNode : public BinaryNode {
public:
	IntDivBinaryNode(Node *left, Node *right) : BinaryNode(left, right) {}
	virtual const Literal *eval() const;
};

class PowBinaryNode : public BinaryNode {
public:
	PowBinaryNode(Node *left, Node *right) : BinaryNode(left, right) {}
	virtual const Literal *eval() const;
};

class SubscriptNode : public BinaryNode {
public:
  SubscriptNode(Node *left, Node *right) : BinaryNode(left, right) {}   
  virtual const Literal* eval() const;
};


class CallNode : public Node {
public:
    CallNode(const std::string &str, Node *_params) : Node(), ident(str), params(_params) {}
    virtual ~CallNode() { delete params; }
    const std::string getIdent() const { return ident;  }
    CallNode(const CallNode&) = delete;
    CallNode& operator=(const CallNode&) = delete;
	virtual const Literal* eval() const;
private:
    std::string ident;
	Node *params;
};


class FuncNode : public Node {
public:
	FuncNode(const std::string id, Node *_params, Node *statements) : ident(id), params(_params), suite(statements) {}
    virtual ~FuncNode() {}	
    virtual const Literal *eval() const;
    FuncNode(const FuncNode&) = delete;
    FuncNode& operator=(const FuncNode&) = delete;
	Node *getParams() const { return params; }
	Node *getSuite() const { return suite; }
private:
    std::string ident;
    Node *params;
    Node *suite;
};

class SuiteNode : public Node {
public:
	SuiteNode(std::vector<Node*> _stmts) : statements(_stmts) {}
    virtual ~SuiteNode() {}	
    virtual const Literal *eval() const;
    SuiteNode(const SuiteNode&) = delete;
    SuiteNode& operator=(const SuiteNode&) = delete;

private:
    std::vector<Node*> statements;
};

class ReturnNode : public Node {
public:
    ReturnNode(const Node *l) : val(l) {}
    virtual ~ReturnNode() { delete val; }
    virtual const Literal *eval() const;
    ReturnNode(const ReturnNode&) = delete;
    ReturnNode& operator=(const ReturnNode&) = delete;
private:
    const Node *val;
};

class PrintNode : public Node {
public: 
    PrintNode(Node *n) : val(n) {}
    virtual ~PrintNode() { delete val; }
    virtual const Literal *eval() const;
    PrintNode(const PrintNode&) = delete;
    PrintNode& operator=(const PrintNode&) = delete;
private:
    Node *val;
};
class CompNode : public BinaryNode {
public:
    CompNode(Node *left, Node *right) : BinaryNode(left, right) {}
    virtual const Literal* eval() const;
    virtual bool getStatus();
};
class EqualNode : public CompNode {
public:
  EqualNode(Node *left, Node *right) : CompNode(left, right) {}   
  virtual const Literal* eval() const;
  virtual bool getStatus();
private:
};
class LessNode: public CompNode {
public:
  LessNode(Node *left, Node *right) : CompNode(left, right) {}   
  virtual const Literal* eval() const;
  virtual bool getStatus();
};
class LessEqualNode : public CompNode {
public:
  LessEqualNode(Node *left, Node *right) : CompNode(left, right) {}
  virtual const Literal* eval() const;
  virtual bool getStatus();
};

class GreaterNode : public CompNode {
public:
  GreaterNode(Node *left, Node *right) : CompNode(left, right) {}   
  virtual const Literal* eval() const;
  virtual bool getStatus();
};

class GreaterEqualNode : public CompNode {
public:
  GreaterEqualNode(Node *left, Node *right) : CompNode(left, right) {}
  virtual const Literal* eval() const;
  virtual bool getStatus();
};

class NotEqualNode : public CompNode {
public:
  NotEqualNode(Node *left, Node *right) : CompNode(left, right) {}   
  virtual const Literal* eval() const;
  virtual bool getStatus();
};



class IfNode : public Node {
public: 
    IfNode(Node *_test, Node *_ifSuite, Node *_elseSuite) : test(_test), ifSuite(_ifSuite), elseSuite(_elseSuite) {}
    virtual ~IfNode() { delete test; }
    virtual const Literal *eval() const;
    IfNode(const IfNode&) = delete;
    IfNode& operator=(const IfNode&) = delete;
private:
    Node *test, *ifSuite, *elseSuite;
};

class ArgsNode : public Node {
public:
	ArgsNode(std::vector<Node*> _args) : args(_args) {}
    virtual ~ArgsNode() {}	
    virtual const Literal *eval() const;
    ArgsNode(const ArgsNode&) = delete;
    SuiteNode& operator=(const ArgsNode&) = delete;
	const std::vector<Node*>& getArgs() const;

private:
    std::vector<Node*> args;
};

