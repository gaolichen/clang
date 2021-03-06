// week5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>

void intAndFraction(float f, int* n, float* d) {
	*n = (int)f;
	*d = f - *n;
}

// 返回一个数的 整数部分和小数部分
void problem1() {
	float f, d;
	int n;
	scanf("%f", &f);

	intAndFraction(f, &n, &d); // 传递地址
	printf("%d %f", n, d);
}

// 求一个数组中的最大值和最小值
#define LEN 20

void getMaxAndMin(int a[], int len, int *max, int *min) {
	int i;
	*max = a[0];
	*min = a[0];
	for (i = 1; i < len; i++) {
		if (a[i] > *max) {
			*max = a[i];
		}
		if (a[i] < *min) {
			*min = a[i];
		}
	}
}

void problem2() {
	int n, i, a[LEN];
	int max, min;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	getMaxAndMin(a, n, &max, &min);

	printf("%d %d\n", max, min);
}

// 用指针计算数组元素的和
void problem3() {
	int n, i, a[10], sum = 0, *p = &a[0];
	
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	while (p < &a[n]) {
		sum += *(p++);
	}

	printf("%d\n", sum);
}

// 数组一组数字，倒序输出数组元素（用指针写）
void problem4() {
	int n, i, a[10], *p;

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	p = a + n - 1;
	while (p >= a) {
		printf("%d ", *p--);
	}
	printf("\n");
}

int main()
{
	problem4();
}
