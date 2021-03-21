// week1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>

int sumOfInteger(int n) {
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		ret += i;
	}

	return ret;
}

int sumOfIntegerRecursive(int n) {
	if (n == 1) { // boundary condition check
		return 1;
	}
	return n + sumOfIntegerRecursive(n - 1);
}

void problem1() {
	int n;
	scanf("%d", &n);
	printf("%d\n", sumOfIntegerRecursive(n));
}

// 12 8
// 8 12 % 8 == 4
// 4 8 % 4 ==0

int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}

int gcdNoRecursive(int a, int b) {
	int c;
	while (b) {
		c = a;
		a = b;
		b = c % b;
	}

	return a;
}

void problem2() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", gcd(a, b));
}

int hanoiStep;
// A == 0, B== 1, C== 2
void hanoiTower(int n, int A, int B, int C) {
	if (n == 1) {
		printf("step %d: move %d from %d to %d\n", ++hanoiStep, n, A, B);
	}
	else {
		hanoiTower(n - 1, A, C, B);
		printf("step %d: move %d from %d to %d\n", ++hanoiStep, n, A, B);
		hanoiTower(n - 1, C, B, A);
	}
}

void problem3() {
	int n;
	scanf("%d", &n);
	hanoiTower(n, 0, 1, 2);
}

int fibo(int n) {
	int a = 0, b = 1;
	int c;
	for (int i = 2; i <= n; i++) {
		c = b;
		b += a;
		a = c;
	}
	return b;
}

void problem4() {
	int n;
	scanf("%d", &n);
	printf("%d\n", fibo(n));
}

#define MAX_ROWS 16
//#define PRINT_QUEEN

int numberOfSolutions;

void putQueen(int* positions, int k, int n) {
	if (k == n) {
		// output
		numberOfSolutions++;
#ifdef PRINT_QUEEN
		printf("solution no. %d\n", numberOfSolutions);
		for (int i = 0; i < n; i++) {
			for (int j = 1; j <= n; j++) {
				if (positions[i] == j) {
					putchar('x');
				}
				else {
					putchar('.');
				}
			}
			putchar('\n');
		}
		putchar('\n');
#endif
		return;
	}

	for (int i = 1; i <= n; i++) {
		// check if we can put queen at position (k, i - 1)
		int ok = 1;
		for (int j = 0; j < k; j++) {
			if (i == positions[j] || positions[j] - j == i - k || positions[j] + j == i + k) {
			//if (i==positions[j]||(k-j)==(i-positions[j])||(j-k)==(i-positions[j])) {
				ok = 0;
				break;
			}
		}
		if (!ok) {
			continue;
		}
		positions[k] = i;
		putQueen(positions, k + 1, n);
	}
}

void problem5() {
	int n;
	int positions[MAX_ROWS] = { 0 };
	scanf("%d", &n);
	putQueen(positions, 0, n);
	printf("There are %d solutions.\n", numberOfSolutions);
}


#define MAX_PARTS 20

void partitionIntergerNoDup(int* parts, int len, int n) {
	if (n == 0) {
		// print;
		for (int i = 0; i < len; i++) {
			printf("%d ", parts[i]);
		}
		printf("\n");
		return;
	}

	int i;
	if (len == 0) {
		i = n - 1;
	}
	else {
		i = n < parts[len - 1] ? n : parts[len - 1] - 1;
	}
	if (i == 0) {
		return;
	}

	for (; i > 0; i--) {
		parts[len] = i;
		partitionIntergerNoDup(parts, len + 1, n - i);
	}
}

void partitionInterger(int* parts, int len, int n) {
	if (n == 0) {
		// print;
		for (int i = 0; i < len; i++) {
			printf("%d ", parts[i]);
		}
		printf("\n");
		return;
	}

	int i;
	if (len == 0) {
		i = n - 1;
	}
	else {
		i = n <= parts[len - 1] ? n : parts[len - 1];
	}

	for (; i > 0; i--) {
		parts[len] = i;
		partitionInterger(parts, len + 1, n - i);
	}
}

// n = sum_i {k_i * k}
// 7 = 3 + 3 + 1 == 0 * 6 + 0 * 5 + 0 * 4 + 2 * 3 + 0 *2 + 1 * 1
void partitionInteger2(int* times, int k, int n) {
	if (n == 0) {
		// print;
		for (int i = k - 1; i >= 1; i--) {
			for (int j = 0; j < times[i]; j++) {
				printf("%d ", i);
			}
		}
		printf("\n");
		return;
	}
	if (k > n) {
		return;
	}
	for (int i = 0; i * k <= n; i++) {
		times[k] = i;
		partitionInteger2(times, k + 1, n - i * k);
	}
}

void problem6() {
	int n, parts[MAX_PARTS] = { 0 };
	scanf("%d", &n);
//	partitionIntergerNoDup(parts, 0, n);
	partitionInteger2(parts, 1, n);
}


int main()
{
	problem6();
}