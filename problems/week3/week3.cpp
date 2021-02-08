// week3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>

double average(double x, double y) {
	// .... 
	// ....
	return (x + y) / 2;
}

void print_frog(int n) {
	printf("%d只青蛙%d只眼\n", n, 2 * n);
}

void print_something(void) {
	printf("hello world\n");
}

void test() {
	double x = 1.0, y = 2.0;
	printf("average: %f\n", average(x, y));
	printf("average: %f\n", average(1.4, 4.6));
	print_frog(10);
	print_something();
}

// 打印小于n的所有质数

// 返回p是否是质数
int is_prime(int p) {
	int i;
	for (i = 2; i * i <= p; i++) {
		if (p % i == 0) {
			return 0;
		}
	}

	return 1;
}

void problem1() {
	int n, i;
	scanf("%d", &n);

	for (i = 2; i < n; i++) {
		if (is_prime(i)) {
			printf("%d\t", i);
		}
	}
	printf("\n");
}

int sum(int a[], int len) { // 正确
	int i, res = 0;
	for (i = 0; i < len; i++) {
		res += a[i];
	}

	return res;
}

#define LEN 10

int sum(int a[][LEN], int len) {
	int i, j;
	int res = 0;
	for (i = 0; i < len; i++) {
		for (j = 0; j < LEN; j++) {
			res += a[i][j];
		}
	}

	return res;
}

// n! = 1 * 2 * 3 * ... * n
// n! = n * (n-1)!
// 递归函数
int fraction(int n) {
	printf("fraction(%d)\n", n);
	// 边界判断
	if (n <= 1) {
		return 1;
	}
	else {
		return n * fraction(n - 1);
	}
}

// 申明函数
int sum(int x, int y);

int main()
{
	int a[10];
	int b[20][10];
	printf("%d\n", fraction(5));
	printf("%d\n", sum(b, 20));

	printf("%d\n", sum(a, 10));
	printf("%d\n", sum(3, 4));
//	problem1();
}

// 定义函数 实现函数
int sum(int x, int y) {
	return x + y;
}
