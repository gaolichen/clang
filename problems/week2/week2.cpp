// week2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>

void test() {
    printf("%d\n", sizeof(short));
    printf("%d\n", sizeof(int));
    printf("%d\n", sizeof(long));
    printf("%d\n", sizeof(long long));

    short i = 0x7fff;
    printf("%d\n", i);
    i++;
    printf("%d\n", i);
}

// 输入 n 输出n的平方
void problem1() {
    int n;
    scanf("%d", &n);
    long long m = n * (long long) n;
    printf("%lld\n", m);
    // printf("%lld\n", n * (long)n); // wrong
}

// 输入两行字符串，输入每行字符串的长度
void problem2() {
    int length1 = 0, length2 = 0;
    while (getchar() != '\n') {
        length1++;
    }

    while (getchar() != '\n') {
        length2++;
    }

    printf("%d %d\n", length1, length2);
}

// 输入两个分数 分数之间有个运算符(+-*/) 计算结果
// 输入 2/5+1/2
// 输出 0.9
// 输入 3/5+1/4
// 输出 0.85
void problem3() {
    int a, b, c, d;
    double n1, n2, result;
    char ch;
    scanf("%d/%d%c%d/%d", &a, &b, &ch, &c, &d);
    // a/b (ch=+-*/) c/d
    n1 = (double)a / b;
    n2 = c / (double)d;
    // 2/(double)5 = 0.4; 2/5 = 0
    // 5/3 = 1

    switch (ch) {
    case '+':
        result = n1 + n2;
        break;
    case '-':
        result = n1 - n2;
        break;
    case '*':
        result = n1 * n2;
        break;
    case'/':
        result = n1 / n2;
        break;
    }

    printf("%f\n", result);
}

int main()
{
    problem3();
}
