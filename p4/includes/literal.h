#include "node.h"
#include "poolOfNodes.h"
#include <cmath>
class Literal : public Node {
public:
  virtual ~Literal() {}

  virtual const Literal* operator+(const Literal& rhs) const =0;
  virtual const Literal* opPlus(float) const =0;
  virtual const Literal* opPlus(int) const =0;
  virtual const Literal* opPlus(std::string) const =0;

  virtual const Literal* operator*(const Literal& rhs) const =0;
  virtual const Literal* opMult(float) const =0;
  virtual const Literal* opMult(int) const =0;
  virtual const Literal* opMult(std::string) const =0;


  virtual const Literal* operator-(const Literal& rhs) const =0;
  virtual const Literal* opSubt(float) const =0;
  virtual const Literal* opSubt(int) const =0;

  virtual const Literal* operator/(const Literal& rhs) const =0;
  virtual const Literal* opDiv(float) const =0;
  virtual const Literal* opDiv(int) const =0;

  virtual const Literal* operator%(const Literal& rhs) const = 0;
  virtual const Literal* opMod(float) const = 0;
  virtual const Literal* opMod(int) const = 0;
  
  virtual const Literal* IntDiv(const Literal& rhs) const = 0;
  virtual const Literal* opIntDiv(float) const = 0;
  virtual const Literal* opIntDiv(int) const = 0;
  
  virtual const Literal* Power(const Literal &rhs) const = 0;
  virtual const Literal* opPow(float) const = 0;
  virtual const Literal* opPow(int) const = 0;

  virtual const Literal* operator[](const Literal &rhs) const = 0;
  virtual const Literal* subscript(std::string) const = 0;

  virtual const Literal* flip() const = 0;

  virtual const Literal* eval() const = 0;
  virtual void print() const { 
    std::cout << "No Way" << std::endl; 
  }
};

class IntLiteral;
class StringLiteral : public Literal {
public:
    StringLiteral(char *str) : val(str) {} 
    StringLiteral(std::string str) : val(str) {}    
  virtual const Literal* operator+(const Literal& rhs) const {
        return rhs.opPlus(val); 
  }
  virtual const Literal* opPlus(float) const {
 		throw std::string("Cannot add Floats and Strings!"); 
  } 
  virtual const Literal* opPlus(int) const {
 		throw std::string("Cannot add Integers and Strings!"); 
  } 
  virtual const Literal* opPlus(std::string str) const {
      const Literal *node = new StringLiteral(str + val);
      PoolOfNodes::getInstance().add(node);
      return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const {
      return rhs.opMult(val);
  } 
  virtual const Literal* opMult(float) const {
 		throw std::string("Cannot multiply string and float!"); 
  } 
  virtual const Literal* opMult(int lhs) const {
      std::string temp = val;
      for (int i = 0; i < lhs - 1; i++)
        temp += val;
      const Literal *node = new StringLiteral(temp);
      PoolOfNodes::getInstance().add(node); 
      return node; 
  } 
  virtual const Literal* opMult(std::string) const {
 		throw std::string("Cannot multiply String and String!"); 
  }

  virtual const Literal* operator-(const Literal&) const {
 		throw std::string("Cannot subtract with a string!"); 
  } 
  virtual const Literal* opSubt(float) const {
 		throw std::string("Cannot subtract with a string!"); 
  } 
  virtual const Literal* opSubt(int) const {
 		throw std::string("Cannot subtract with a string!"); 
  } 

  virtual const Literal* operator/(const Literal&) const {
 		throw std::string("Cannot divide with a String!"); 
  } 
  virtual const Literal* opDiv(float) const {
 		throw std::string("Cannot divide with a String!"); 
  } 
  virtual const Literal* opDiv(int) const {
 		throw std::string("Cannot divide with String!"); 
  } 

  virtual const Literal* operator%(const Literal&) const {
 		throw std::string("Cannot perform modulus on String!"); 
  } 
  virtual const Literal* opMod(float) const {
 		throw std::string("Cannot perform modulus on String!"); 
  } 
  virtual const Literal* opMod(int) const {
 		throw std::string("Cannot perform modulus on String!"); 
  } 
  
  virtual const Literal* IntDiv(const Literal&) const {
 		throw std::string("Cannot perform Integer Division on String!"); 
  } 
  virtual const Literal* opIntDiv(float) const {
 		throw std::string("Cannot perform Integer Division on String!"); 
  }
  virtual const Literal* opIntDiv(int) const {
 		throw std::string("Cannot perform Integer Division on String!"); 
  } 
  
  virtual const Literal* Power(const Literal&) const {
 		throw std::string("Cannot take power of String!"); 
  } 
  virtual const Literal* opPow(float) const {
 		throw std::string("Cannot take power of String!"); 
  } 
  virtual const Literal* opPow(int) const {
 		throw std::string("Cannot take power of String!"); 
  }

  virtual const Literal* flip() const {
 		throw std::string("Cannot flip a string!"); 
  } 

  virtual const Literal* eval() const {
    return this;
  } 

  virtual const Literal* operator[](const Literal &rhs) const {

        return rhs.subscript(val); 
      
      //else throw std::string("Invalid subscript operation!");
  } 
  virtual const Literal* subscript(std::string) const {
      throw std::string("Invalid subscript operation!");
  }

  virtual void print() const {
    std::cout << "STRING: " << val << std::endl;
  }  
private:
    std::string val;
};

class FloatLiteral: public Literal {
public:
  FloatLiteral(float _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node; 
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(std::string) const {
 		throw std::string("Cannot perform addition with Float and String!"); 
  }
  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<float>(lhs) * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(std::string) const {
 		throw std::string("Cannot perform multiplication with Float and String!"); 
  }

  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(float lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* operator%(const Literal& rhs) const {
  	return rhs.opMod(val);
  } 
  virtual const Literal* opMod(float lhs) const {
 	const Literal *node = new FloatLiteral(static_cast<int>(lhs) % static_cast<int>(val));
	PoolOfNodes::getInstance().add(node);
  	return node;
  }

  virtual const Literal* opMod(int lhs) const {
 	const Literal *node = new FloatLiteral(lhs % static_cast<int>(val));
	PoolOfNodes::getInstance().add(node);
  	return node;
  } 
 virtual const Literal* IntDiv(const Literal &rhs) const {
	return rhs.opIntDiv(val);
}

virtual const Literal* opIntDiv(int lhs) const {
	const Literal *node = new FloatLiteral(lhs / static_cast<int>(val));
	PoolOfNodes::getInstance().add(node);
	return node;
}
virtual const Literal* opIntDiv(float lhs) const {
	const Literal *node = new FloatLiteral(static_cast<int>(lhs) / static_cast<int>(val));
	PoolOfNodes::getInstance().add(node);
	return node;
}

virtual const Literal* Power(const Literal &rhs) const {
	return rhs.opPow(val);
}

virtual const Literal* opPow(int lhs) const {
	const Literal *node = new FloatLiteral(std::pow(lhs, val));
	PoolOfNodes::getInstance().add(node);
	return node;
}
virtual const Literal* opPow(float lhs) const {
	const Literal *node = new FloatLiteral(std::pow(lhs, val));
	PoolOfNodes::getInstance().add(node);
	return node;
}

virtual const Literal* operator[](const Literal&) const {
    throw std::string("Invalid operation!");
}

virtual const Literal* subscript(std::string) const {
    throw std::string("Invalid operation!");
}


virtual const Literal* flip() const { 
	const Literal *node = new FloatLiteral(val * -1);
	PoolOfNodes::getInstance().add(node);
	return node;
}

  virtual const Literal* eval() const { return this; }
  virtual void print() const { 
    std::cout << "FLOAT: " << val << std::endl; 
  }
private:
  float val;
};

class IntLiteral: public Literal {
public:
 IntLiteral(int _val): val(_val) {}

  virtual const Literal* operator+(const Literal& rhs) const  {
    return rhs.opPlus(val);
  }
  virtual const Literal* opPlus(float lhs) const  {
    const Literal* node = new FloatLiteral(static_cast<float>(val) + lhs);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(int lhs) const  {
    const Literal* node = new IntLiteral(lhs + val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opPlus(std::string) const {
 		throw std::string("Cannot perform addition with Integer and String!"); 
  }
  virtual const Literal* operator-(const Literal& rhs) const  {
    return rhs.opSubt(val);
  }
  virtual const Literal* opSubt(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opSubt(int lhs) const  {
    const Literal* node = new IntLiteral(lhs - val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator*(const Literal& rhs) const  {
    return rhs.opMult(val);
  }
  virtual const Literal* opMult(float lhs) const  {
    const Literal* node = new FloatLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(int lhs) const  {
    const Literal* node = new IntLiteral(lhs * val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opMult(std::string lhs) const {
      std::string temp = lhs;
      for (int i = 0; i < val - 1; i++)
          temp += lhs;
      const Literal* node = new StringLiteral(temp);
      PoolOfNodes::getInstance().add(node);
      return node;
  }
  virtual const Literal* operator/(const Literal& rhs) const  {
    return rhs.opDiv(val);
  }
  virtual const Literal* opDiv(float lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new FloatLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }
  virtual const Literal* opDiv(int lhs) const  {
    if ( val == 0 ) throw std::string("Zero Division Error");
    const Literal* node = new IntLiteral(lhs / val);
    PoolOfNodes::getInstance().add(node);
    return node;
  }

  virtual const Literal* operator%(const Literal& rhs) const {
  	return rhs.opMod(val);
  } 
  virtual const Literal* opMod(float lhs) const {
 	const Literal *node = new FloatLiteral(static_cast<int>(lhs) % static_cast<int>(val));
	PoolOfNodes::getInstance().add(node);
 	return node; 
  } 
  virtual const Literal* opMod(int lhs) const {
 	const Literal *node = new IntLiteral(lhs % val);
	PoolOfNodes::getInstance().add(node);
 	return node;
 }
 
 virtual const Literal* IntDiv(const Literal& rhs) const {
	return rhs.opIntDiv(val);	
 }

virtual const Literal* opIntDiv(int lhs) const {
	const Literal *node = new FloatLiteral(lhs / static_cast<int>(val));
	PoolOfNodes::getInstance().add(node);
	return node;
}
virtual const Literal* opIntDiv(float lhs) const {
	const Literal *node = new FloatLiteral(static_cast<int>(lhs) / static_cast<int>(val));
	PoolOfNodes::getInstance().add(node);
	return node;
}

virtual const Literal* Power(const Literal &rhs) const {
	return rhs.opPow(val);
}

virtual const Literal* opPow(int lhs) const {
	const Literal *node = new FloatLiteral(std::pow(lhs, val));
	PoolOfNodes::getInstance().add(node);
	return node;
}
virtual const Literal* opPow(float lhs) const {
	const Literal *node = new FloatLiteral(std::pow(lhs, val));
	PoolOfNodes::getInstance().add(node);
	return node;
}
virtual const Literal* flip() const { 
	const Literal *node = new IntLiteral(val * -1);
	PoolOfNodes::getInstance().add(node);
	return node;
}

virtual const Literal* operator[](const Literal&) const {
    throw std::string("not valid operation");
}
virtual const Literal* subscript(std::string str) const {
    const Literal *node = new StringLiteral(str[val] + "");
    PoolOfNodes::getInstance().add(node);
    return node;
}
  virtual const Literal* eval() const { return this; }
  virtual void print() const { 
    std::cout << "INT: " << val << std::endl; 
  }
private:
  int val;
};
