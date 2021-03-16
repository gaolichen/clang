// week7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>

#define MAX_URL 80
void add_domain(char* url);

void problem1() {
	char url[MAX_URL + 1];
	scanf("%s", url);
	add_domain(url);
	printf("%s\n", url);
}

// ����fp2�����ݵ�fp1
#define MAX_LEN 200


void printFile(FILE* fp2) {
	char line[MAX_LEN];
	while (!feof(fp2)) { // �ж��Ƿ�����ļ�ĩβ
		fgets(line, MAX_LEN, fp2); // ��ȡһ��
		printf("%s\n", line);
	}
}

void problem3() {
	char file1[] = "C:\\project\\test1.txt";
	FILE* fp1 = fopen(file1, "r");
	printFile(fp1);
	fseek(fp1, 0, SEEK_SET);
	printFile(fp1);
	fclose(fp1);
}

void copyText(FILE* fp1, FILE* fp2) {
	char line[MAX_LEN];
	while (!feof(fp2)) { // �ж��Ƿ�����ļ�ĩβ
		fgets(line, MAX_LEN, fp2); // ��ȡһ��
		fputs(line, fp1); // дһ��
	}
}

void problem2() {
	char file1[] = "C:\\project\\test1.txt";
	char file2[] = "C:\\project\\test2.txt";
	char file3[] = "C:\\project\\test3.txt";

	FILE* fp1 = fopen(file1, "r");
	FILE* fp2 = fopen(file2, "r");
	FILE* fp3 = fopen(file3, "w");
	copyText(fp3, fp1);
	copyText(fp3, fp2);

	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

// ð�ݣ�ֻ�������ڵ���
void bubbleSort(int * a, int len) {
	int i, j, tmp;
	for (i = 0; i < len; i++) { // ִ����һ�Σ��������Ƶ����ұ�
		for (j = 0; j < len - i - 1; j++) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}

void problem4() {
	int n, a[MAX_LEN], i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	bubbleSort(a, n);

	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

// ѡ������
void selectionSort(int* a, int len) {
	int i, j, k, tmp;
	for (i = 0; i < len; i++) { // Ѱ�ҵ�iС����
		k = i;
		for (j = i + 1; j < len; j++) {
			if (a[j] < a[k]) {
				k = j;
			}
		}
		tmp = a[k];
		a[k] = a[i];
		a[i] = tmp;
	}
}

void problem5() {
	int n, a[MAX_LEN], i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}

	selectionSort(a, n);

	for (i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}


int main()
{
	problem5();
	return 0;
}

void add_domain(char* url) {
	char head[] = "http://www.";
	// sina.com.cn
	// ........sina.com.cn
	//            q       p
	char* p = url + strlen(url) + strlen(head);
	char* q = url + strlen(url);
	while (q >= url) {
		*p-- = *q--;
	}
	q = head + strlen(head) - 1;
	while (p >= url) {
		*p-- = *q--;
	}
}

