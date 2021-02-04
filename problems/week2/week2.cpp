// week2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void test() {
    printf("%d\n", sizeof(short));
    printf("%d\n", sizeof(int));
    printf("%d\n", sizeof(long));
    printf("%d\n", sizeof(long long));

    short i = 0x7fff;
    printf("%d\n", i);
    i++;
    printf("%d\n", i);
}

// ���� n ���n��ƽ��
void problem1() {
    int n;
    scanf("%d", &n);
    long long m = n * (long long) n;
    printf("%lld\n", m);
    // printf("%lld\n", n * (long)n); // wrong
}

// ���������ַ���������ÿ���ַ����ĳ���
void problem2() {
    int length1 = 0, length2 = 0;
    while (getchar() != '\n') {
        length1++;
    }

    while (getchar() != '\n') {
        length2++;
    }

    printf("%d %d\n", length1, length2);
}

// ������������ ����֮���и������(+-*/) ������
// ���� 2/5+1/2
// ��� 0.9
// ���� 3/5+1/4
// ��� 0.85
void problem3() {
    int a, b, c, d;
    double n1, n2, result;
    char ch;
    scanf("%d/%d%c%d/%d", &a, &b, &ch, &c, &d);
    // a/b (ch=+-*/) c/d
    n1 = (double)a / b;
    n2 = c / (double)d;
    // 2/(double)5 = 0.4; 2/5 = 0
    // 5/3 = 1

    switch (ch) {
    case '+':
        result = n1 + n2;
        break;
    case '-':
        result = n1 - n2;
        break;
    case '*':
        result = n1 * n2;
        break;
    case'/':
        result = n1 / n2;
        break;
    }

    printf("%f\n", result);
}

// 1 + 1/2^2 + 1/3^2 + ... + 1/n^2
void problem4() {
    int n, i;
    double res = 0.0;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        //res += 1.0 / (i * i); // �������� 1/2 == 0
        //res += 1 / (double)(i * i); // ������� i*i �п������
        res += 1.0 / i / i; // ���
    }

    printf("%f\n", res);
}

// 1^3 + 2^3 + ... + n^3
void problem5() {
    int n, i;
    long long res = 0;
    scanf("%d", &n);

    for (i = 1; i <= n; i++) {
        res += (long long)i * i * i;
    }

    printf("%lld\n", res);
}

// ����һ��Ӣ��
// ������ʵ�ƽ������
void problem6() {
    char ch; // ������¼��ǰ���ַ�
    char ch2  = ' '; // ������¼ǰ��һ���ַ�
    int length = 0; // ��¼���е��ʵĳ��Ⱥ�
    int count = 0; // ��¼���ʵĸ���

/*    while (1) {
        scanf("%c", &ch);
        if (ch == '\n') {
            break;
        }
        //
    }*/
    while ((ch = getchar()) != '\n') {
        if (ch >= 'a' && ch <= 'z' || ch >= 'A' && ch <= 'Z') {
            length++;
            // ���ǰ��һ���ַ��ǿո񣬶��ҵ�ǰ���ַ�����ĸ����ô��������һ
            if (ch2 == ' ') {
                count++;
            }
        }
        ch2 = ch;
        //hello                   , world.
    }

    printf("%f\n", length / (double)count);
}

// ��������n < 100 
// ������n������
// �����n�������ĵ���

// ����һ���� (macro)
// define �뵱�ڰ�����N�滻Ϊ100
#define NN 100

void problem7() {
    int n, i, tmp;
    int a[NN];

    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    // n = 10
    // 0 1 2 3 4 5 6 7 8 9
    // 0 9 ����
    // 1 8
    // 2 7
    // 3 6
    // 4 5 // ���һ������
    // i=5: 5 4 // ����Ҫ

    // �������ڵ���˳��
    // a[i] ���������
    // i ����λ�� 
    // 5 3 6 9 10 9 8
    for (i = 0; i + i < n; i++) {
        // ���� a[i] �� a[n-1-i]
        tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - i - 1] = tmp;
    }

    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/* ��������n < 52

    ���n��������ظ����˿���
    ����ĸ��ʾ
    ���� = t ���� = h ���� = f ÷�� = m
    4t ����4
    ah ����A
    jm ÷��J*/

void problem8() {
    int n, k, l;
    // ��t��ʾ10
    char number[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 't', 'j', 'q', 'k', 'a'};
    char color[4] = { 't', 'h', 'f', 'm' };
    // ��ά���飬��¼��Щ���Ѿ�������
    // ��������� ��Ӧλ�õ�mark[k][l] == 1
    int mark[13][4] = { 0 };
    // tt = ����10

    scanf("%d", &n);

   // �����������
    srand(time(NULL));

    while (n > 0) {
        // ���������һ����
        // �����������
        k = rand() % 13; // �����0��12������
        l = rand() % 4; // �����0��3������

        // ��������ظ�����
        if (mark[k][l] == 0) {
            printf("%c%c ", number[k], color[l]);
            n--;
            mark[k][l] = 1;
        }
    }
}

// ����n 
// �� 5 * 5 ��ͼ�ϣ�����n��������ߵ�·�� ��һ����A��ʾ  �ڶ�����B ....
// �յ��� . ��ʾ
// �������
// AB...
// HCD..
// GFE..
// .....
// .....
void problem9() {
    int n, i, j, direction;
    int tx, ty, x = 0, y = 0; // ��ǰλ��
    char ch = 'A', map[5][5];
    // dx, dy�������ַ���
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    // ��ʼ��map
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            map[i][j] = '.';
        }
    }

    scanf("%d", &n);
    map[x][y] = ch;
    n--;
    srand(time(NULL));
    while (n > 0) {
        // ����ǲ�������ͬ
        for (i = 0; i < 4; i++) {
            tx = x + dx[i];
            ty = y + dy[i];
            // ����һ�������ߵĲ��� ��������ͬ
            if (tx >= 0 && tx < 5 && ty >= 0 && ty < 5 && map[tx][ty] == '.') {
                break;
            }
        }
        // ���i=4 ����ͬ
        if (i == 4) {
            break;
        }

        // ����һ�����·��
        direction = rand() % 4; // ����ķ���0��3
        x += dx[direction];
        y += dy[direction];
        if (x >= 0 && x < 5 && y >= 0 && y < 5 && map[x][y] == '.') {
            map[x][y] = ++ch;
            n--;
        }
        else {
            x -= dx[direction];
            y -= dy[direction];
        }
    }

    // �����ͼ
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    problem9();
}
