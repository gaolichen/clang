#include "polynomial.h"
#include <algorithm>

void Monomial::_normalize() {
	// if this coefficient is zero clear
	if (this->_coef == 0) {
		this->_vars.clear();
	}
	else {
		std::sort(this->_vars.begin(), this->_vars.end());
	}
}

Polynomial* Polynomial::multiply(const Polynomial* other) const {
	Polynomial* ret = new Polynomial();
	for (int i = 0; i < _terms.size(); i++) {
		for (int j = 0; j < other->_terms.size(); j++) {
			ret->_terms.push_back(_terms[i].multiply(other->_terms[j]));
		}
	}

	ret->_normalize();

	return ret;
}

Polynomial* Polynomial::add(const Polynomial* other) const {
	Polynomial* ret = new Polynomial();
	for (int i = 0; i < _terms.size(); i++) {
		ret->_terms.push_back(_terms[i]);
	}

	for (int i = 0; i < other->_terms.size(); i++) {
		ret->_terms.push_back(other->_terms[i]);
	}

	ret->_normalize();

	return ret;
}

Polynomial* Polynomial::subtract(const Polynomial* other) const {
	Polynomial* ret = new Polynomial();
	for (int i = 0; i < _terms.size(); i++) {
		ret->_terms.push_back(_terms[i]);
	}

	for (int i = 0; i < other->_terms.size(); i++) {
		ret->_terms.push_back(other->_terms[i]);
		ret->_terms.back().negative();
	}

	ret->_normalize();

	return ret;
}

void Polynomial::_normalize() {
	// sort
	std::sort(_terms.begin(), _terms.end());

	// combine the same terms
	int k = 0;
	for (int i = 0; i < _terms.size(); i++) {
		if (_terms[k].sameTerm(_terms[i])) {
			if (k != i) {
				_terms[k].add(_terms[i]);
			}
		}
		else {
			if (_terms[k].coef() != 0) {
				k++;
			}

			if (k != i) {
				_terms[k] = _terms[i];
			}
		}
	}

	for (int i = _terms.size() - 1; i > k; i--) {
		_terms.pop_back();
	}

	if (_terms.back().coef() == 0) {
		_terms.pop_back();
	}
}
