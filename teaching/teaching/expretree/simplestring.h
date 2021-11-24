#pragma once
#pragma warning (disable : 4996)
#include <iostream>
#include <cstring>

class SimpleString {
public:
	SimpleString() {}

	SimpleString(int len, char ch) : _len(len) {
		_str = new char[len + 1];
		for (int i = 0; i < len; i++) {
			_str[i] = ch;
		}

		_str[_len] = 0;
	}

	SimpleString(const char* str) {
		_len = strlen(str);
		this->_str = _clonestr(str, _len);
	}

	SimpleString(const char* str, int len) : _len(len) {
		this->_str = _clonestr(str, _len);
	}

	SimpleString(const SimpleString& other) {
		_len = other._len;
		if (_str) {
			delete[] _str;
		}
		_str = _clonestr(other._str, _len);
	}

	SimpleString& operator = (const SimpleString& other) {
		_len = other._len;
		if (_str) {
			delete[] _str;
		}
		_str = _clonestr(other._str, _len);
		return *this;
	}

	SimpleString operator + (const SimpleString& other) const {
		SimpleString ret(*this);
		ret += other;
		return ret;
	}

	SimpleString& operator += (const SimpleString& other) {
		char* new_str = new char[this->_len + other._len + 1];
		strncpy(new_str, this->_str, this->_len);
		strncpy(new_str + this->_len, other._str, other._len);

		this->_len += other._len;
		new_str[this->_len] = 0;

		delete[] this->_str;
		this->_str = new_str;

		return *this;
	}

	bool operator < (const SimpleString& other) const {
		return strcmp(this->_str, other._str) < 0;
	}

	bool operator == (const SimpleString& other) const {
		if (this->_len != other._len) {
			return false;
		}

		return strcmp(this->_str, other._str) == 0;
	}

	bool operator != (const SimpleString& other) const {
		return !(*this == other);
	}

	friend std::ostream& operator << (std::ostream& out, const SimpleString& s) {
		if (s.c_str()) {
			out << s.c_str();
		}
		return out;
	}

	int length() const {
		return _len;
	}

	const char* c_str() const {
		return _str;
	}

	~SimpleString() {
		if (_str != nullptr) {
			delete[] _str;
			_str = nullptr;
		}
	}

private:
	char* _str = nullptr;
	int _len = 0;

	static char* _clonestr(const char* str, int len) {
		char* ret = new char[len + 1];
		strncpy(ret, str, len);
		ret[len] = 0;

		return ret;
	}
};