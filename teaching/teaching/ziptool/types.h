#pragma once
#include <iostream>
#define USE_STD_STRING
#define USE_STD_VECTOR

#ifdef USE_STD_STRING
#include <string>
using String = std::string;
#else
#include "simplestring.h"
using String = SimpleString;
#endif

#ifdef USE_STD_VECTOR
#include<vector>
template<typename T>
using Vector = std::vector<T>;
#else
#include "simplevector.h"
template<typename T>
using Vector = SimpleVector<T>;
#endif

template <typename T>
std::ostream& operator<< (std::ostream& out, const Vector<T>& v) {
    out << '[';
    if (!v.empty()) {
        std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", "));
        out << "\b\b";
    }
    out << ']';
    return out;
}

#define BUFFER_SIZE 100

#define CHAR_TO_INT(ch) ((ch) & 0xff)
#define INT_TO_CHAR1(x) (x)
#define INT_TO_CHAR2(x) ((x) >> 8)
#define TWO_CHAR_TO_INT(ch1, ch2) (CHAR_TO_INT(ch1) | (CHAR_TO_INT(ch2) << 8))