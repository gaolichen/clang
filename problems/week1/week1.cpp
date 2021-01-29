// week1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>

// problem 1: input a year, print yes if it is a leap year, print no otherwise.
void problem1() {
	int year;
	scanf("%d", &year);
	if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
		printf("yes\n");
	}
	else {
		printf("no\n");
	}
}

// ������λ�����������
void problem2() {
	int n;
	scanf("%d", &n);
	int a, b, c;
	a = n / 100;
	b = (n - a * 100) / 10;
	c = n % 10;
	printf("%d%d%d", c, b, a);
}

// �����·ݵİ��������֣���������·�
void problem3() {
	int n;
	scanf("%d", &n);
	switch (n) {
	case 0:
		printf("��\n");
		break;
	case 1:
		printf("һ\n");
		break;
	case 2:
		printf("��\n");
		break;
	case 3:
		printf("��\n");
		break;
	case 4:
		printf("��\n");
		break;
	case 5:
		printf("��\n");
		break;
	case 6:
		printf("��\n");
		break;
	case 7:
		printf("��\n");
		break;
	case 8:
		printf("��\n");
		break;
	case 9:
		printf("��\n");
		break;
	}
}

// ����С��1000������������������8���Ʊ�ʾ
void problem4() {
	int n, a, b, c, d;

	scanf("%d", &n);
	a = n % 8;
	n /= 8;
	b = n % 8;
	n /= 8;
	c = n % 8;
	n /= 8;
	d = n % 8;
	printf("%d", d * 1000 + c * 100 + b * 10 + a);
}

// ���뾮�ĸ߶�h�ף�����ÿ����5��Ȼ�����2�ף�������ܼ�����������
void problem5() {
	int h;
	scanf("%d", &h);
//	(h - 5 + 3 - 1) / 3 + 1;
//	(h - 3)/3 + 1
	if (h <= 5) {
		printf("1\n");
	}
	else {
		printf("%d\n", h / 3);
	}
}

// ����һ������n���ж��Ƿ�������
// if n % a == 0, 
// then b = n / a 
// a, b ͬʱ����n ���� a * b == n,
// a, b����һ��С�ڸ���n
void problem6() {
	int n, i;
	scanf("%d", &n);
	for (i = 2; i < n && i * i <= n; i++) {
		if (n % i == 0) {
			break;
		}
	}
//	for (i = 2; i < n && n % i != 0; i++);

	if (i * i > n) {
		printf("yes\n");
	}
	else {
		printf("no\n");
	}
}

// ��������n�����n��λ���ֵĵ���
// ����n = 12345�����54321
void problem7() {
	int n;
	scanf("%d", &n);
	while (n > 0) {
		printf("%d", n % 10); // n�ĸ�λ����
		n /= 10;
	}
	printf("\n");
}

// ���n��8����
void problem8() {
	int n, m = 0, ten = 1;
	scanf("%d", &n);
	while (n > 0) {
		m += (n % 8) * ten;
		ten *= 10; // ��һ��
		n /= 8;
	}

	printf("%d", m);
}

// �������������������Լ��
void problem9() {
	int a, b, tmp;
	scanf("%d %d", &a, &b);
	if (a == 0 || b == 0) {
		printf("one of them is zero.\n");
		return;
	}
	while (a % b != 0) {
		tmp = a;
		a = b;
		b = tmp % b;
	}

	printf("%d\n", b);
}

int main() {
	problem9();
	return 0;
}