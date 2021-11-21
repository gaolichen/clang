#pragma once
#include "types.h"
#include "polynomial.h"

class VariableMap {
private:
	Vector<String> _vars;
	Vector<int> _vals;
public:
	VariableMap(const Vector<String>& vars, const Vector<int>& vals) : _vars(vars), _vals(vals) {
	}

	bool getValue(const String& var, int* ret) const {
		for (int i = 0; i < _vars.size(); i++) {
			if (_vars[i] == var) {
				*ret = _vals[i];
				return true;
			}
		}
		return false;
	}
};

class ExpressionNode {
public:	
	virtual ~ExpressionNode() {}
	virtual Polynomial* eval(const VariableMap* variableMap) const = 0;
	virtual String toString() const = 0;
};

class LeafNode : public ExpressionNode {
private:
	String _expression;
public:
	LeafNode(const String& expression): _expression(expression) {
	}

	virtual Polynomial* eval(const VariableMap* variableMap) const {
		int val;
		if (variableMap->getValue(_expression, &val)) {
			char buf[20];
			return new Polynomial(itoa(val, buf, 10));
		}
		return new Polynomial(_expression);
	}

	virtual String toString() const {
		return _expression;
	}
};

class BinaryNode : public ExpressionNode {
protected:
	ExpressionNode* _left = nullptr;
	ExpressionNode* _right = nullptr;
	String _op;

public:
	BinaryNode(const String& op, ExpressionNode* left, ExpressionNode* right) : _op(op), _left(left), _right(right) {
	}

	virtual ~BinaryNode() {
		if (_left) {
			delete _left;
			_left = nullptr;
		}

		if (_right) {
			delete _right;
			_right = nullptr;
		}
	}

	virtual Polynomial* eval(const VariableMap* variableMap) const {
		Polynomial* p1 = this->_left->eval(variableMap);
		Polynomial* p2 = this->_right->eval(variableMap);

		Polynomial* res = nullptr;
		if (_op == "+") {
			res = p1->add(p2);
		}
		else if (_op == "-") {
			res = p1->subtract(p2);
		}
		else if (_op == "*") {
			res = p1->multiply(p2);
		}

		delete p1;
		delete p2;

		return res;
	}

	virtual String toString() const {
		String s = "(";
		s += _left->toString() + this->_op + _right->toString();
		return s + ")";
	}
};
