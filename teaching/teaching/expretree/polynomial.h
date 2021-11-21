#pragma once
#pragma warning (disable : 4996)
#include <cstdlib>
#include "types.h"

class Monomial {
private:
	int _coef = 0;
	Vector<String> _vars;
	void _normalize();
public:
	Monomial() {}

	explicit Monomial(const String& var) {
		if (var.c_str()[0] >= '0' && var.c_str()[0] <= '9') {
			_coef = atoi(var.c_str());
			_vars = Vector<String>{};
		}
		else {
			_coef = 1;
			_vars = Vector<String>{ var };
		}
	}

	Monomial(const Monomial& other) {
		_vars = other._vars;
		_coef = other._coef;
	}

	int coef() const {
		return this->_coef;
	}

	Monomial multiply(const Monomial& other) const {
		Monomial res;
		for (int i = 0; i < this->_vars.size(); i++) {
			res._vars.push_back(this->_vars[i]);
		}
		for (int i = 0; i < other._vars.size(); i++) {
			res._vars.push_back(other._vars[i]);
		}

		res._coef = this->_coef * other._coef;
		res._normalize();

		return res;
	}

	bool sameTerm(const Monomial& other) const {
		if (this->_vars.size() != other._vars.size()) {
			return false;
		}

		for (int i = 0; i < this->_vars.size(); i++) {
			if (this->_vars[i] != other._vars[i]) {
				return false;
			}
		}

		return true;
	}

	void add(const Monomial& other) {
		this->_coef += other._coef;
	}

	void negative() {
		this->_coef = -this->_coef;
	}

	bool operator < (const Monomial& other) const {
		if (this->_vars.size() != other._vars.size()) {
			return other._vars.size() < this->_vars.size();
		}
		else {
			for (int i = 0; i < this->_vars.size(); i++) {
				if (_vars[i] != other._vars[i]) {
					return _vars[i] < other._vars[i];
				}
			}
			return false;
		}
	}

	String toString() const {
		char buf[20];
		String ret = itoa(this->_coef, buf, 10);

		for (int i = 0; i < this->_vars.size(); i++) {
			ret += "*";
			ret += this->_vars[i];
		}
		return ret;
	}
};

class Polynomial {
private:
	Vector<Monomial> _terms;
	void _normalize();
public:
	Polynomial() {}

	Polynomial(const String& variable) {
		_terms.push_back(Monomial(variable));
	}

	Vector<String> toStrings() const {
		Vector<String> ret;
		for (int i = 0; i < _terms.size(); i++) {
			ret.push_back(_terms[i].toString());
		}

		return ret;
	}

	Polynomial* multiply(const Polynomial* other) const;
	Polynomial* add(const Polynomial* other) const;
	Polynomial* subtract(const Polynomial* other) const;
};

