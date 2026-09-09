#include "RPN.hpp"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <sstream>
#include <stack>
#include <list>
#include <cstdlib>

RPN::RPN() {}

RPN::RPN(const RPN& src) {
	*this = src;
}

RPN& RPN::operator=(const RPN& rhs) {
	(void)rhs;
	return *this;
}

RPN::~RPN() {}

static bool isOp(char op) {
	return (op == '+' || op == '-' || op == '/' || op == '*');
}

void RPN::evaluate(const std::string& expression) {
    std::stack<int, std::list<int> > stack;
	std::stringstream ss(expression);
	std::string token;

	while (ss >> token) {
		if (token.length() == 1 && ::isdigit(token[0])) {
			stack.push((token[0] - '0'));
		} else if (token.length() == 1 && isOp(token[0])) {
			if (stack.size() < 2) {
				std::cerr << "Error" << std::endl;
				return ;
			}
			int b = stack.top();
			stack.pop();
			int a = stack.top();
			stack.pop();
			int result = 0;
			switch (token[0]) {
				case '+':
					result = a + b;
					break ;
				case '-':
					result = a - b;
					break ;
				case '*':
					result = a * b;
					break ;
				case '/':
					if (b == 0) {
						std::cerr << "Division by zero" << std::endl;
						return ;
					}
					result = a / b;
					break ;
			}
			stack.push(result);
		} else {
			std::cerr << "Error" << std::endl;
			return ;
		}
	}

	if (stack.size() == 1) {
		std::cout << stack.top() << std::endl;
	} else {
		std::cerr << "Error" << std::endl;
	}
}