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

// 输入 n 输出n的平方
void problem1() {
    int n;
    scanf("%d", &n);
    long long m = n * (long long) n;
    printf("%lld\n", m);
    // printf("%lld\n", n * (long)n); // wrong
}

// 输入两行字符串，输入每行字符串的长度
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

// 输入两个分数 分数之间有个运算符(+-*/) 计算结果
// 输入 2/5+1/2
// 输出 0.9
// 输入 3/5+1/4
// 输出 0.85
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
        //res += 1.0 / (i * i); // 整数除法 1/2 == 0
        //res += 1 / (double)(i * i); // 整数溢出 i*i 有可能溢出
        res += 1.0 / i / i; // 最好
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

// 输入一行英文
// 输出单词的平均长度
void problem6() {
    char ch; // 用来记录当前的字符
    char ch2  = ' '; // 用来记录前面一个字符
    int length = 0; // 记录所有单词的长度和
    int count = 0; // 记录单词的个数

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
            // 如果前面一个字符是空格，而且当前的字符是字母，那么单词数加一
            if (ch2 == ' ') {
                count++;
            }
        }
        ch2 = ch;
        //hello                   , world.
    }

    printf("%f\n", length / (double)count);
}

// 输入整数n < 100 
// 再输入n个整数
// 输出这n个整数的倒序

// 定义一个宏 (macro)
// define 想当于把所有N替换为100
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
    // 0 9 交换
    // 1 8
    // 2 7
    // 3 6
    // 4 5 // 最后一个交换
    // i=5: 5 4 // 不需要

    // 在数组内调整顺序
    // a[i] 数组里的数
    // i 数的位置 
    // 5 3 6 9 10 9 8
    for (i = 0; i + i < n; i++) {
        // 交换 a[i] 和 a[n-1-i]
        tmp = a[i];
        a[i] = a[n - 1 - i];
        a[n - i - 1] = tmp;
    }

    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/* 输入整数n < 52

    输出n张随机不重复的扑克牌
    用字母表示
    红桃 = t 黑桃 = h 方块 = f 梅花 = m
    4t 红桃4
    ah 黑桃A
    jm 梅花J*/

void problem8() {
    int n, k, l;
    // 用t表示10
    char number[13] = {'2', '3', '4', '5', '6', '7', '8', '9', 't', 'j', 'q', 'k', 'a'};
    char color[4] = { 't', 'h', 'f', 'm' };
    // 二维数组，记录哪些牌已经产生过
    // 如果产生过 相应位置的mark[k][l] == 1
    int mark[13][4] = { 0 };
    // tt = 红桃10

    scanf("%d", &n);

   // 设置随机种子
    srand(time(NULL));

    while (n > 0) {
        // 产生随机的一张牌
        // 随机产生数字
        k = rand() % 13; // 随机的0到12的数字
        l = rand() % 4; // 随机的0到3的数字

        // 如果不是重复的牌
        if (mark[k][l] == 0) {
            printf("%c%c ", number[k], color[l]);
            n--;
            mark[k][l] = 1;
        }
    }
}

// 输入n 
// 在 5 * 5 地图上，产生n步随机行走的路线 第一步用A表示  第二步用B ....
// 空的用 . 表示
// 输出例子
// AB...
// HCD..
// GFE..
// .....
// .....
void problem9() {
    int n, i, j, direction;
    int tx, ty, x = 0, y = 0; // 当前位置
    char ch = 'A', map[5][5];
    // dx, dy定义四种方向
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};

    // 初始化map
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
        // 检查是不是死胡同
        for (i = 0; i < 4; i++) {
            tx = x + dx[i];
            ty = y + dy[i];
            // 发现一个可以走的步， 不是死胡同
            if (tx >= 0 && tx < 5 && ty >= 0 && ty < 5 && map[tx][ty] == '.') {
                break;
            }
        }
        // 如果i=4 死胡同
        if (i == 4) {
            break;
        }

        // 产生一步随机路线
        direction = rand() % 4; // 随机的方向，0到3
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

    // 输出地图
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
