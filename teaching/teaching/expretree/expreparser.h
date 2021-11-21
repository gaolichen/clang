#pragma once
#include "types.h"
#include "expretree.h"

class ExpressionParser {
public:
	ExpressionNode* toExpressionTree(const char * expression) {
		Vector<String> postfix = toPostfix(expression);
		//std::cout << "postfix=" << postfix << std::endl;
		return postfixToTree(postfix);
	}

	Vector<String> toPostfix(const char* expression) {
		int len = strlen(expression);

		int start = -1;
		Vector<String> ret;
		Vector<char> opStack;
		for (int i = 0; i <= len; i++) {
			if ((expression[i] >= '0' && expression[i] <= '9') ||
				(expression[i] >= 'a' && expression[i] <= 'z') ||
				(expression[i] >= 'A' && expression[i] <= 'Z')) {
				if (start < 0) {
					start = i;
				}
			}
			else {
				if (start >= 0) {
					ret.push_back(String(expression + start, i - start));
					start = -1;
				}

				if (expression[i] == '(') {
					opStack.push_back('(');
				}
				else if (expression[i] == ')') {
					while (!opStack.empty() && opStack.back() != '(') {
						ret.push_back(String(1, opStack.back()));
						opStack.pop_back();
					}

					opStack.pop_back();
				}
				else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*') {
					int priority = _getPriority(expression[i]);
					while (!opStack.empty() && _getPriority(opStack.back()) >= priority) {
						ret.push_back(String(1, opStack.back()));
						opStack.pop_back();
					}
					opStack.push_back(expression[i]);
				}
				else {
					// do nothing
				}
			}
		}

		while (!opStack.empty()) {
			ret.push_back(String(1, opStack.back()));
			opStack.pop_back();
		}

		return ret;
	}

	ExpressionNode* postfixToTree(const Vector<String>& postfix) {
		Vector<ExpressionNode*> stack;
		for (int i = 0; i < postfix.size(); i++) {
			if (postfix[i] == "+" || postfix[i] == "-" || postfix[i] == "*") {
				ExpressionNode* b = stack.back();
				stack.pop_back();
				ExpressionNode* a = stack.back();
				stack.pop_back();
				stack.push_back(new BinaryNode(postfix[i], a, b));
			}
			else {
				stack.push_back(new LeafNode(postfix[i]));
			}
		}

		ExpressionNode* ret = stack.back();
		return ret;
	}

private:
	int _getPriority(char op) {
		if (op == '+' || op == '-') {
			return 10;
		}
		else if (op == '*') {
			return 20;
		}

		return 0;
	}
};