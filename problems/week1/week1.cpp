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

// ����һ���¼��� 1�������ڼ�����������µ�������ʽ
void problem10() {
	int day, daysOfMonth, i;
	// ����һ�����м��� �� 1�������ڼ�
	scanf("%d %d", &daysOfMonth, &day);
	
	for (i = 0; i < day; i++) {
		printf("   ");
	}

	for (i = 1; i <= daysOfMonth; i++) {
		if (day % 7 == 6) {
			printf("%2d\n", i);
		}
		else {
			printf("%2d ", i);
		}
		day++;
	}
}

// ���С�ڵ���n����������
void problem11() {
	int n, i, j;
	scanf("%d", &n);

	for (i = 2; i <= n; i++) {
		// �ж�i�Ƿ�������
		for (j = 2; j * j <= i; j++) {
			if (i % j == 0) {
				break;
			}
		}

		if (j * j > i) {
			// i������
			printf("%d ", i);
		}
		else {
			// i ��������
		}
	}
	printf("\n");
}

// ����n ������Ȼ�����ĵ���e=1 + 1/1! + 1/2! + 1/3! + ... + 1/n!
// n! ��ʾn�Ľ׳�

// 1/3! �� 1/2! �� 1/3 

void problem12() {
	int n, i;
	double res = 1.0, inc = 1.0;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		inc /= i;
		res += inc;
	}

	// ��һ�� i=1
	// inc /= i:  inc /=1; inc = 1.0
	// res += 1.0; res = 2.0;
	// �ڶ�b�� i = 2
	// inc /= i: inc /= 2; => inc = 1/2 = 1/2;
	// res += inc: res += 0.5; => res = 2.5;
	// ������
	// inc/=i: inc/=3; ==> inc = 1/2/3 =1/6
	// res += inc: res = 2.5 + 1/6 = 2.61666667

	printf("%0.15lf\n", res);
}

// ����n�� ����n������λ��ż��λ����
void problem13() {
	int n, even, odd, ten;
	scanf("%d", &n);
	for (ten = 1, even = odd = 0; n > 0; n /=10, ten *= 10) {
		odd += (n % 10) * ten;
		n /= 10;
		even += (n % 10) * ten;
//		ten *= 10;
//		n /= 10;
	}

	printf("%d %d\n", odd, even);
}

int main() {
	problem13();
	return 0;
}