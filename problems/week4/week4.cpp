// week4.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>


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

int main()
{
	problem7();
}
