// week4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <math.h>

void test() {
	int a[10] = {};
	int b[4][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int i, j;
	printf("a=\n");
	for (i = 0; i < 10; i++) {
		printf("%d ", a[i]);
	}
	printf("\nb=\n");

	for (i = 0; i < 4; i++) {
		for (j = 0; j < 3; j++) {
			printf("%d ", b[i][j]);
		}
		printf("\n");
	}
}

void testStatic(void) {
	static int i = 0; // 静态局部变量
	i++;
	printf("%d\n", i);
}

// 输入 月/日/年(mm/dd/yyyy) 格式的日期，输出 年-月-日(yyyy-mm-dd) 格式的日期
void problem1() {
	int year, month, day;
	scanf("%d/%d/%d", &month, &day, &year);
	printf("%d-%02d-%02d", year, month, day);
}

// 计算一个日期是一年中的第几天。
int dayOfYear(int year, int month, int day) {
	int days1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int i, res = 0;
	// 如果是闰年
	if (year % 400 == 0 || (year % 100) && (year % 4 == 0)) {
		for (i = 0; i < month - 1; i++) {
			res += days2[i];
		}
		return res + day;
	}
	else {
		// 不是闰年
		for (i = 0; i < month - 1; i++) {
			res += days1[i];
		}
		return res + day;
	}
}

// 计算两个日期差几天
void problem4() {
	int year, month1, day1, month2, day2;
	scanf("%d %d %d %d %d", &year, &month1, &day1, &month2, &day2);
	printf("%d\n", dayOfYear(year, month1, day1) - dayOfYear(year, month2, day2));
}

// 计算个人所得税：输入一个正整数，代表年收入，输出需要交多少税
void problem5() {
	int n;
	double res = 0.0;
	scanf("%d", &n);
	if (n > 1000000) {
		// 收入超过100万的，超出部分交50%
		res += (n - 1000000) / 2.0;
		n = 1000000;
	}

	// 收入超过50万的，50万到100万的部分交30%
	if (n > 500000) {
		res += (n - 500000) * 0.3;
		n = 500000;
	}

	// 收入超过20万的，20万到50万的部分交20%
	if (n > 200000) {
		res += (n - 200000) * 0.2;
		n = 200000;
	}

	// 收入超过10万的，10万到20万的部分10%
	if (n > 100000) {
		res += (n - 100000) * 0.1;
		n = 100000;
	}

	// 收入超过5万的，5万到10万的部分缴纳5%
	if (n > 50000) {
		res += (n - 50000) * 0.05;
		n = 50000;
	}

	printf("%f\n", res);
}

void problem7() {
	int n, i, j;
	int mat[20][20] = {0};
	int dx[4] = {0, 1, 0, -1}; // 四个方向
	int dy[4] = {1, 0, -1, 0};
	int cx = 0, cy = 0; // 当前的位置
	int nx, ny;
	int m = 1; // 当前放的数字
	int dir = 0; // 当前的前进方向 
	scanf("%d", &n);
	mat[cx][cy] = m;
	while (m < n * n) {
		// 试着走一步 
		nx = cx + dx[dir];
		ny = cy + dy[dir];

		// 如果出界或者已经被占了, 转弯
		if (nx < 0 || nx >= n || ny < 0 || ny >= n || mat[nx][ny]) {
			dir = (dir + 1) % 4;
		} else {
			// 否则可以放置 
			mat[nx][ny] = ++m;
			cx = nx;
			cy = ny;
		}
	}

	// 输出
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%3d ", mat[i][j]);
		}
		printf("\n");
	}
}

// compute 1 + 2 + ... + n;
// (1 + 2 + ... + (n-1)) + n
int total(int n) {
	// 边界判断
	if (n <= 0) {
		return 0;
	}

	return n + total(n - 1);
}

// if n = 3
// return 3 + total(2);
//            : 2 + total(1);
//                  1 + total(0);
//                       0;

void problem8() {
	int n;
	scanf("%d", &n);
	printf("%d\n", total(n));
}

// 求最大公约数
int gcd(int a, int b) {
	if (b == 0) {
		return a;
	}
	else {
		return gcd(b, a % b);
	}
}

// 5 0 -> 5
// 0 5 -> gcd(5, 0) -> 5
// 6 3 -> gcd(3, 6%3) == gcd(3, 0) -> 3
// 8 12 -> gcd(12, 8%12) == gcd(12, 8) -> gcd(8, 12%8)==gcd(8, 4) -> gcd(4, 8%4) == gcd(4, 0) -> 4  
// 辗转相除法

void problem9() {
	int a, b;
	scanf("%d %d", &a, &b);
	printf("%d\n", gcd(a, b));
}

int size; // 当前栈里的元素个数
char stack[80]; // 栈

void push(char ch) { // 元素放到栈里
	stack[size] = ch;
	size++;
}

char pop() { // 把栈里的元素取出来， 返回栈里最后一个放进去的元素
	size--;
	return stack[size];
}

int isEmpty() { // 判断栈是否空
	return size == 0;
}

// 判断输入括号是否匹配
void problem10() {
	char ch, ch2;
	// 输入一行
	int match = 1;
	while ((ch = getchar()) != '\n') {
		if (ch == '(' || ch == '{') {
			push(ch); // 存起来
		}
		else if (ch == ')' || ch == '}') {
			// 如果栈是空，不匹配，停止
			if (isEmpty()) {
				// 不匹配
				match = 0;
				break;
			}

			// 取出栈里最后一个放进去的元素
			ch2 = pop();
			if (ch == ')' && ch2 != '(' || ch == '}' && ch2 != '{') {
				// 不匹配
				match = 0;
				break;
			}
		}
	}
	// 输出
	if (match) { // 非0的数都是真
		printf("yes\n");
	}
	else {
		printf("no\n");
	}
}

void testSqrt() {
	double i = 1.0;
	float j = 2.0;
	int k = sqrt(j);
	printf("%f", sqrt(8));
}


int main()
{
	problem10();
}
