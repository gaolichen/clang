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
	static int i = 0; // ��̬�ֲ�����
	i++;
	printf("%d\n", i);
}

// ���� ��/��/��(mm/dd/yyyy) ��ʽ�����ڣ���� ��-��-��(yyyy-mm-dd) ��ʽ������
void problem1() {
	int year, month, day;
	scanf("%d/%d/%d", &month, &day, &year);
	printf("%d-%02d-%02d", year, month, day);
}

// ����һ��������һ���еĵڼ��졣
int dayOfYear(int year, int month, int day) {
	int days1[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int days2[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int i, res = 0;
	// ���������
	if (year % 400 == 0 || (year % 100) && (year % 4 == 0)) {
		for (i = 0; i < month - 1; i++) {
			res += days2[i];
		}
		return res + day;
	}
	else {
		// ��������
		for (i = 0; i < month - 1; i++) {
			res += days1[i];
		}
		return res + day;
	}
}

// �����������ڲ��
void problem4() {
	int year, month1, day1, month2, day2;
	scanf("%d %d %d %d %d", &year, &month1, &day1, &month2, &day2);
	printf("%d\n", dayOfYear(year, month1, day1) - dayOfYear(year, month2, day2));
}

// �����������˰������һ�������������������룬�����Ҫ������˰
void problem5() {
	int n;
	double res = 0.0;
	scanf("%d", &n);
	if (n > 1000000) {
		// ���볬��100��ģ��������ֽ�50%
		res += (n - 1000000) / 2.0;
		n = 1000000;
	}

	// ���볬��50��ģ�50��100��Ĳ��ֽ�30%
	if (n > 500000) {
		res += (n - 500000) * 0.3;
		n = 500000;
	}

	// ���볬��20��ģ�20��50��Ĳ��ֽ�20%
	if (n > 200000) {
		res += (n - 200000) * 0.2;
		n = 200000;
	}

	// ���볬��10��ģ�10��20��Ĳ���10%
	if (n > 100000) {
		res += (n - 100000) * 0.1;
		n = 100000;
	}

	// ���볬��5��ģ�5��10��Ĳ��ֽ���5%
	if (n > 50000) {
		res += (n - 50000) * 0.05;
		n = 50000;
	}

	printf("%f\n", res);
}

void problem7() {
	int n, i, j;
	int mat[20][20] = {0};
	int dx[4] = {0, 1, 0, -1}; // �ĸ�����
	int dy[4] = {1, 0, -1, 0};
	int cx = 0, cy = 0; // ��ǰ��λ��
	int nx, ny;
	int m = 1; // ��ǰ�ŵ�����
	int dir = 0; // ��ǰ��ǰ������ 
	scanf("%d", &n);
	mat[cx][cy] = m;
	while (m < n * n) {
		// ������һ�� 
		nx = cx + dx[dir];
		ny = cy + dy[dir];

		// �����������Ѿ���ռ��, ת��
		if (nx < 0 || nx >= n || ny < 0 || ny >= n || mat[nx][ny]) {
			dir = (dir + 1) % 4;
		} else {
			// ������Է��� 
			mat[nx][ny] = ++m;
			cx = nx;
			cy = ny;
		}
	}

	// ���
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
