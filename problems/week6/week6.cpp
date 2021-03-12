// week6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define IS_LEAP(y) ((y) % 400 == 0 || (y) % 100 != 0 && (y) % 4 == 0)

void reverseArray(int* a, int len) {
	int *p = a, *q = a + len - 1, tmp;
	while (p < q) {
		tmp = *p;
		*p++ = *q;
		*q-- = tmp;
	}
}

void problem1() {
	int n, i, a[20];
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	reverseArray(a, n);
	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

// 例子：输入两个复数，输出他们的乘积
// (a + b i) * (c + d i) == (a*c - b*d) + (a * d+ b*c) i 

typedef int my_type;

typedef struct Complex {
	my_type real;
	my_type imag;
};

//#define DEBUG

Complex multiplyComplex(Complex* x, Complex* y) {
#ifdef DEBUG
	printf("%d %d", x->real, x->imag);
#endif
	Complex z;
	// 
	z.real = x->real * y->real - x->imag * y->imag;
	z.imag = x->real * y->imag + x->imag * y->real;
	return z;
}

void problem2() {
	Complex c1, c2, c3;
	scanf("%d %d %d %d", &c1.real, &c1.imag, &c2.real, &c2.imag);
	c3 = multiplyComplex(&c1, &c2);
	printf("%d+%di\n", c3.real, c3.imag);
}

int main()
{
/*	int year;
	scanf("%d", &year);
	if (IS_LEAP(year)) {
		printf("yes\n");
	}
	else {
		printf("no\n");
	}
	printf("%f\n", MAX(2.5, 3.6));*/
	problem2();
}
