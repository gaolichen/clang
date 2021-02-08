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

#define MAX_R 100
#define MAX_C 100

void problem10() {
    int r, c, i, j, a;
    int sum_r[MAX_R] = { 0 }, sum_c[MAX_C] = { 0 };
/*  // �ö�ά����  
    int arr[MAX_R][MAX_C];
    scanf("%d %d", &r, &c);
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &arr[i][j]);
            sum_r[i] += arr[i][j];
            sum_c[j] += arr[i][j];
        }
    }*/

    // ����Ҫ��ά����
    scanf("%d %d", &r, &c);
    for (i = 0; i < r; i++) {
        for (j = 0; j < c; j++) {
            scanf("%d", &a);
            sum_r[i] += a;
            sum_c[j] += a;
        }
    }

    printf("ÿ�е����ֺ���: ");
    for (i = 0; i < r; i++) {
        printf("%d ", sum_r[i]);
    }
    printf("\n");

    printf("ÿ�е�ƽ������: ");
    for (i = 0; i < r; i++) {
        printf("%.2f ", (double)sum_r[i] / c);
    }
    printf("\n");

    printf("ÿ�е����ֺ���: ");
    for (i = 0; i < c; i++) {
        printf("%d ", sum_c[i]);
    }
    printf("\n");

    printf("ÿ�е�ƽ������: ");
    for (i = 0; i < c; i++) {
        printf("%.2f ", (double)sum_c[i] / c);
    }
    printf("\n");
}

void problem11() {
    char ch, input[100] = {0};
    int count[10] = { 0 }, n = 0, i;
    // count[0,...,9]
    // count[0] �洢 '0' ���ֵĴ���
    // count[1] �洢 '1' ���ֵĴ���
    // ...
    // count[9] �洢 '9' ���ֵĴ���

    while ((ch = getchar()) != '\n') {
        input[n++] = ch;
    }

    // n = ���ٸ��ַ�
    // ͳ�� �����ַ����ֵ�Ƶ��
    // input[i]: �ַ�'0'��'9'
    // input[i] - '0': ����0��9
    for (i = 0; i < n; i++) {
        count[input[i] - '0']++;
    }

    for (i = 0; i <= 9; i++) {
        if (count[i] != 0) {
            printf("%d %d\n", i, count[i]);
        }
    }
}

void problem12() {
    int n, m = 0, i;
    char input[100];
    scanf("%d", &n);

    // ����һ��
    getchar();
    while ((input[m] = getchar()) != '\n') {
        m++;
    }

/*    // m++: ��ʹ��m ��++
    // ++m: ��++ ��ʹ��m
    while ((input[m] = getchar()) != '\n') {
        m++;
    }

    while ((ch = getchar()) != '\n') {
        input[m++] = ch;
    }*/

    // ����
    for (i = 0; i < m; i++) {
        if ('a' <= input[i] && input[i] <= 'z') {
            input[i] += n; // �п������
            if (input[i] > 'z') {
//                input[i] -= 26;
                // if input[i] == 'c',
                //    input[i] = 'a' + ('c' - 'a') % 26 == 'a' + 2 % 26 == 'a' + 2 == 'c'
                // if input[i] == 'z' + 2
                //    input[i] = 'a' + ('z' + 2 - 'a') % 26 == 'a' + 28 % 26 == 'a' + 2 == 'c'
                input[i] = 'a' + (input[i] - 'a') % 26;
            }
        }

        if ('A' <= input[i] && input[i] <= 'Z') {
            input[i] = 'A' + (input[i] - 'A' + n) % 26; // û���������
            /*input[i] = input[i] + n % 26;
            if (input[i] > 'Z') {
                input[i] -= 26;
            }*/
        }
    }

    for (i = 0; i < m; i++) {
        printf("%c", input[i]);
    }
    printf("\n");
}

int main()
{
    problem12();
}
