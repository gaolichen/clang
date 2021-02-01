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

// 输入一个月几天 1号是星期几，输入这个月的日历格式
void problem10() {
	int day, daysOfMonth, i;
	// 输入一个月有几天 和 1号是星期几
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

// 输出小于等于n的所有质数
void problem11() {
	int n, i, j;
	scanf("%d", &n);

	for (i = 2; i <= n; i++) {
		// 判断i是否是质数
		for (j = 2; j * j <= i; j++) {
			if (i % j == 0) {
				break;
			}
		}

		if (j * j > i) {
			// i是质数
			printf("%d ", i);
		}
		else {
			// i 不是质数
		}
	}
	printf("\n");
}

// 输入n 计算自然对数的底数e=1 + 1/1! + 1/2! + 1/3! + ... + 1/n!
// n! 表示n的阶乘

// 1/3! 是 1/2! 的 1/3 

void problem12() {
	int n, i;
	double res = 1.0, inc = 1.0;
	scanf("%d", &n);
	for (i = 1; i <= n; i++) {
		inc /= i;
		res += inc;
	}

	// 第一步 i=1
	// inc /= i:  inc /=1; inc = 1.0
	// res += 1.0; res = 2.0;
	// 第二b步 i = 2
	// inc /= i: inc /= 2; => inc = 1/2 = 1/2;
	// res += inc: res += 0.5; => res = 2.5;
	// 第三步
	// inc/=i: inc/=3; ==> inc = 1/2/3 =1/6
	// res += inc: res = 2.5 + 1/6 = 2.61666667

	printf("%0.15lf\n", res);
}

// 输入n， 输入n的奇数位和偶数位的数
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