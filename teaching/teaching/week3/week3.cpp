// week3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma warning (disable : 4996)

#include <stdio.h>
#include <chrono>

#define BEGIN_TIMER { \
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

#define END_TIMER \
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); \
	int _miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); \
	printf("It takes %d ms.\n", _miliseconds); \
}

#define E_DIGITS 50000+10

void add(int* res, int* a, int len) {
	int v = 0;
	for (int i = len - 1; i >= 0; i--) {
		res[i] += a[i] + v;
		if (res[i] >= 10) {
			res[i] -= 10;
			v = 1;
		}
		else {
			v = 0;
		}
	}
}

void divide(int* res, int* a, int k, int len) {
	int v = 0;
	for (int i = 0; i < len; i++) {
		v = 10 * v + a[i];
		res[i] = v / k;
		v = v % k;
	}
}

void computeE(int n) {
	int res[E_DIGITS] = {5}; // {5, 0, 0, 0, ....} // this is for results.
	int a[E_DIGITS] = {5}; // this stores 1/n!, initial value = 1/2!
	int extraDigits = 5;

	// compute E
	for (int i = 3; ; i++) {
		int b[E_DIGITS];
		// b = a / i;
		divide(b, a, i, n + extraDigits);
		
		// if b is zero, stop;
		int nonzero = 0;
		for (int j = 0; j < n + extraDigits; j++) {
			if (b[j]) {
				nonzero = 1;
				break;
			}
		}
		if (!nonzero) {
			break;
		}

		// res += b;
		add(res, b, n + extraDigits);

		// a = b
		for (int j = 0; j < n + extraDigits; j++) {
			a[j] = b[j];
		}
	}

	// print results
	printf("2.");
	for (int i = 0; i < n; i++) {
		printf("%d", res[i]);
	}
	printf("\n");
}

void problem1() {
	int n;
	scanf("%d", &n);
	// begin timer
	BEGIN_TIMER;

	computeE(n);
	// end timer and print how long it takes.
	END_TIMER;
}

void problem2() {
	char ch = 100;
	printf("%c\n", ch);
}

struct TreeNode {
	int value;

	TreeNode* left = NULL;
	TreeNode* right = NULL;
	TreeNode(int value) { // constructor
		this->value = value;
	}

	void print() {
		printf("%d", value);
	}
};

void dfs(TreeNode* root) { // depth first search 深度优先
	root->print();
	printf(" ");
	if (root->left) {
		dfs(root->left);
	}
	if (root->right) {
		dfs(root->right);
	}
}

void bfs(TreeNode* root) { // broad first search 广度优先
	// queue
	TreeNode* queue[10] = {0};
	int open = 0, close = 0;
	queue[open++] = root;
	while (close < open) {
		TreeNode* node = queue[close++];
		node->print();
		printf(" ");
		if (node->left) {
			queue[open++] = node->left;
		}
		if (node->right) {
			queue[open++] = node->right;
		}
	}
}

void problem3() {
	int i = 2;
	TreeNode* root = new TreeNode(2);
	root->left = new TreeNode(3);
	root->right = new TreeNode(4);
	root->left->left = new TreeNode(5);
	root->left->right = new TreeNode(6);
	root->right->right = new TreeNode(7);
	printf("dfs:\n");
	dfs(root);

	printf("\nbfs:\n");
	bfs(root);
}

int main()
{
	problem1();
	return 0;
}
