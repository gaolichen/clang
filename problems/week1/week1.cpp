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

// 输入三位数，输出倒序
void problem2() {
	int n;
	scanf("%d", &n);
	int a, b, c;
	a = n / 100;
	b = (n - a * 100) / 10;
	c = n % 10;
	printf("%d%d%d", c, b, a);
}

// 输入月份的阿拉伯数字，输出中文月份
void problem3() {
	int n;
	scanf("%d", &n);
	switch (n) {
	case 0:
		printf("零\n");
		break;
	case 1:
		printf("一\n");
		break;
	case 2:
		printf("二\n");
		break;
	case 3:
		printf("三\n");
		break;
	case 4:
		printf("四\n");
		break;
	case 5:
		printf("五\n");
		break;
	case 6:
		printf("六\n");
		break;
	case 7:
		printf("七\n");
		break;
	case 8:
		printf("八\n");
		break;
	case 9:
		printf("九\n");
		break;
	}
}

// 输入小于1000的整数，输出这个数的8进制表示
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

// 输入井的高度h米，青蛙每次跳5米然后掉下2米，输出青蛙几次能跳出井
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

// 输入一个数字n，判断是否是质数
// if n % a == 0, 
// then b = n / a 
// a, b 同时整除n 而且 a * b == n,
// a, b至少一个小于根号n
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

// 输入整数n，输出n各位数字的倒序
// 比如n = 12345，输出54321
void problem7() {
	int n;
	scanf("%d", &n);
	while (n > 0) {
		printf("%d", n % 10); // n的个位数字
		n /= 10;
	}
	printf("\n");
}

// 输出n的8进制
void problem8() {
	int n, m = 0, ten = 1;
	scanf("%d", &n);
	while (n > 0) {
		m += (n % 8) * ten;
		ten *= 10; // 加一句
		n /= 8;
	}

	printf("%d", m);
}

// 输入两个整数，求最大公约数
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