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
    CallNode(const std::string &str) : Node(), ident(str) {}
    virtual ~CallNode() {}
    const std::string getIdent() const { return ident;  }
    virtual const Literal* eval() const;
private:
    std::string ident;
};


class FuncNode : public Node {
public:
	FuncNode(const std::string id, Node *statements) : ident(id), suite(statements) {}
    virtual ~FuncNode() {}	
    virtual const Literal *eval() const;
    FuncNode(const FuncNode&) = delete;
    FuncNode& operator=(const FuncNode&) = delete;

private:
    std::string ident;
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
