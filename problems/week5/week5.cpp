// week5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>

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

// ��ָ���������Ԫ�صĺ�
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

// ����һ�����֣������������Ԫ�أ���ָ��д��
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


#define STR_LEN 20

int read_line(char str[], int len);

void problem5() {
	char input[STR_LEN + 1];
	read_line(input, STR_LEN);
	printf("%s", input);
}

// ����һ���ַ������浽str������ַ����ĳ���
int read_line(char str[], int len) {
	char ch;
	int i = 0;
	while ((ch = getchar()) != '\n' && i < len) {
		str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}

// ͳ���ַ�����ĸ��ո���
int count_spaces(char* str);

void problem6() {
	char str[STR_LEN + 1];
	read_line(str, STR_LEN);
	printf("there are %d spaces.\n", count_spaces(str));
}

int count_spaces(char* str) {
	int count = 0;
	while (*str) {
		if (*str++ == ' ') {
			count++;
		}
	}
	return count;
}

char* my_strcat(char* str1, char* str2);

void problem7() {
	char str1[STR_LEN + 1], str2[STR_LEN + 1];
	scanf("%s%s", str1, str2);
	printf("%s\n", my_strcat(str1, str2));
}

char* my_strcat(char* str1, char* str2) {
/*	char* p = str1;
	// if str1="abc"; *p = 'a';
	// �ҵ�str1��'\0'��λ��
	while (*p) p++;*/
//	char* p = str1 + strlen(str1);
	// *p = '\0';
	strcpy(str1 + strlen(str1), str2);
	return str1;
}

int main()
{
	problem7();
}
