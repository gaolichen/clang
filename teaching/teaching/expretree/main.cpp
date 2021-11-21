// expretree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "types.h"
#include "expretree.h"
#include "polynomial.h"
#include "expreparser.h"

#pragma region Test code

void testString() {
    String s1 = "aaaa";
    String s2 = s1 + "bbbb";
    std::cout << s2 << std::endl;

    if (s1 == "aaaa") {
        std::cout << "yes" << std::endl;
    }

    if (s1 != "aaaa") {
        std::cout << "no" << std::endl;
    }

    if (s1 < s2) {
        std::cout << "yes" << std::endl;
    }

    s1 += "ccc";
    std::cout << s1 << std::endl;
}

void testPolynomial() {
    Polynomial p1("ab");
    Polynomial p2("10");
    Polynomial* p3 = p1.multiply(&p2);
    Polynomial* p4 = p2.add(&p2);
    Polynomial* p5 = p4->subtract(p3);

    Vector<String> vs1 = p3->toStrings();
    Vector<String> vs2 = p4->toStrings();
    Vector<String> vs3 = p5->toStrings();
    std::cout << vs1 << std::endl;
    std::cout << vs2 << std::endl;
    std::cout << vs3 << std::endl;

    delete p3;
    delete p4;
    delete p5;
}

void testParser() {
    char expression[] = "abc + (12 * (d + 4) - 3)";
    ExpressionParser parser;
    Vector<String> postfix = parser.toPostfix(expression);
    std::cout << postfix << std::endl;
}

void testVector() {
    Vector<int> a{ 1,2,4 };
    std::cout << a << std::endl;
}

void runTests() {
    testString();
    testParser();
    testPolynomial();
    testVector();
}

#pragma endregion

#pragma region Examples

Vector<String> eval(const char* expression, const Vector<String>& vars, const Vector<int>& vals) {
    ExpressionParser parser;
    ExpressionNode* tree = parser.toExpressionTree(expression);
    //std::cout << tree->toString() << std::endl;
    VariableMap vm = VariableMap(vars, vals);
    Polynomial* poly = tree->eval(&vm);
    Vector<String> res = poly->toStrings();

    delete tree;
    //delete vm;
    delete poly;

    return res;
}

void runExample(const char* expression, const Vector<String>& vars, const Vector<int>& vals) {
    std::cout << std::endl << "============" << std::endl;
    std::cout << "expression = " << expression << std::endl;
    std::cout << "evalvars = " << vars << std::endl;
    std::cout << "evalints = " << vals << std::endl;

    std::cout << "output = " << eval(expression, vars, vals) << std::endl;
}

void example1() {
    Vector<String> vars{ "e"};
    Vector<int> vals{1};
    char expression[] = "e + 8 - a + 5";

    runExample(expression, vars, vals);
}

void example2() {
    Vector<String> vars{"e", "temperature"};
    Vector<int> vals{1, 12};
    char expression[] = "e - 8 + temperature - pressure";

    runExample(expression, vars, vals);
}

void example3() {
    Vector<String> vars{};
    Vector<int> vals{};
    char expression[] = "(e + 8)*(e - 8)";

    runExample(expression, vars, vals);
}

void example4() {
    Vector<String> vars{};
    Vector<int> vals{};
    char expression[] = "(e + 8)*(e - 8)*(x+2)*(y-3)*(pressure-4)";

    runExample(expression, vars, vals);
}

#pragma endregion

int main() {
    //runTests();

    example1();
    example2();
    example3();
    example4();
}
