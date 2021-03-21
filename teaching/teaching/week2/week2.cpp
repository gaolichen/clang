// week2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning (disable : 4996)

#include <stdio.h>

struct ExpressionNode {
	int value = 0;
	char op = 0;

	ExpressionNode* next;

	void print() {
		if (op) {
			printf("%c", op);
		}
		else {
			printf("%d", value);
		}
	}

	int priority() {
		switch (op)
		{
		case '+':
		case '-':
			return 10;
		case '*':
		case '/':
			return 20;
		default:
			return 0;
		}
	}
};

ExpressionNode* createValueNode(int value) {
	ExpressionNode* newNode = new ExpressionNode();
	newNode->value = value;
	return newNode;
}

ExpressionNode* createOpNode(char ch) {
	ExpressionNode* newNode = new ExpressionNode();
	newNode->op = ch;
	return newNode;
}

#pragma region Link List

// a Link list
// (head = node1) -> node2 -> node3
struct ExpressionList {
	ExpressionNode* head = NULL;

	/// <summary>
	/// Add the new vaue as head
	/// </summary>
	/// <param name="value"></param>
	void addNode(int value) {
		ExpressionNode* newNode = createValueNode(value);
		newNode->next = head;
		head = newNode;
	}

	void addOperator(char ch) {
		ExpressionNode* newNode = createOpNode(ch);
		newNode->next = head;
		head = newNode;
	}

	void reverse() {
		ExpressionNode* curr = head, * prev = NULL;
		//  prev  --  curr ---  curr->next
		while (curr) {
			ExpressionNode* tmp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = tmp;
		}
		head = prev;
	}

	ExpressionNode* find(int value) {
		// TODO
		return NULL;
	}

	ExpressionNode* remove(int value) {
		ExpressionNode* curr = head;
		ExpressionNode* prev = NULL;
		while (curr) {
			if (curr->value == value) {
				if (prev) {
					prev->next = curr->next;
				}
				else {
					head = curr->next;
				}
				return curr;
			}
			prev = curr;
			curr = curr->next;
		}

		return NULL;
	}

	void print() {
		ExpressionNode* p = head;
		while (p) {
			p->print();
			printf(" ");
			p = p->next;
		}
		printf("\n");
	}
};

void testLinkList() {
	int n;
	ExpressionList list;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int value;
		scanf("%d", &value);
		list.addNode(value);
	}
	
	list.print();
	printf("after reverse:\n");
	list.reverse();
	list.print();
}

#pragma endregion

#pragma region Stack

#define STACK_SIZE 80
struct ExpressionStack {
	ExpressionNode* nodes[STACK_SIZE];
	int size = 0;

	/// <summary>
	/// add node as the top of the stack
	/// </summary>
	/// <param name="node"></param>
	void push(int value) {
		ExpressionNode* node = createValueNode(value);
		nodes[size++] = node;
	}

	void pushOp(char ch) {
		ExpressionNode* node = createOpNode(ch);
		nodes[size++] = node;
	}

	ExpressionNode* pop() {
		return nodes[--size];
	}

	ExpressionNode* top() {
		return nodes[size - 1];
	}

	int isEmpty() {
		return size == 0;
	}
};

#pragma endregion

#pragma region evaluate expression

int compute(int n1, int n2, char op) {
	switch (op) {
	case '+':
		return n1 + n2;
	case '-':
		return n1 - n2;
	case '*':
		return n1 * n2;
	case '/':
		return n1 / n2;
	default:
		return 0;
	}
}

int evaluate(ExpressionList* list) {
	ExpressionStack stack;
	ExpressionNode* p = list->head;
	while (p) {
		if (p->op) {
			int n1 = stack.pop()->value;
			int n2 = stack.pop()->value;
			stack.push(compute(n2, n1, p->op));
		}
		else {
			stack.push(p->value);
		}
		p = p->next;
	}
	return stack.pop()->value;
}

void toPostfix(ExpressionList* inFix, ExpressionList* postFix) {
	ExpressionNode* p = inFix->head;
	ExpressionStack opStack;
	while (p) {
		if (p->op) {
			int priority = p->priority();
			while (!opStack.isEmpty() && opStack.top()->priority() >= priority) {
				postFix->addOperator(opStack.pop()->op);
			}
			opStack.pushOp(p->op);
		}
		else {
			postFix->addNode(p->value);
		}
		p = p->next;
	}
	while (!opStack.isEmpty()) {
		postFix->addOperator(opStack.pop()->op);
	}
}

void testExpression() {
	char ch;
	int num = -1;
	ExpressionList list;
	// 123+345 
	while ((ch = getchar()) != '\n') {
		if (ch >= '0' && ch <= '9') {
			if (num == -1) {
				num = ch - '0';
			}
			else {
				num = 10 * num + ch - '0';
			}
		}
		else {
			if (num != -1) {
				list.addNode(num);
				num = -1;
			}
			if (ch != ' ')
				list.addOperator(ch);
		}
	}
	if (num != -1) {
		list.addNode(num);
	}
	list.reverse();
//	list.print();
	ExpressionList postFix;
	toPostfix(&list, &postFix);
	postFix.reverse();
//	postFix.print();
	printf("%d\n", evaluate(&postFix));
}

#pragma endregion

int main()
{
	testExpression();
}
