// week5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>

void intAndFraction(float f, int* n, float* d) {
	*n = (int)f;
	*d = f - *n;
}

// ����һ������ �������ֺ�С������
void problem1() {
	float f, d;
	int n;
	scanf("%f", &f);

	intAndFraction(f, &n, &d); // ���ݵ�ַ
	printf("%d %f", n, d);
}

// ��һ�������е����ֵ����Сֵ
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

void problem3() {
	;
}

int main()
{
	problem2();
}
