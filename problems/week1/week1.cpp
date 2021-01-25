// week1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning(disable : 4996)
#include <stdio.h>

// problem 1: input a year, print yes if it is a leap year, print no otherwise.
void isLeapYear() {
	int year;
	scanf("%d", &year);
	if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)) {
		printf("yes\n");
	}
	else {
		printf("no\n");
	}
}

int main() {
	isLeapYear();
}