#pragma once
#include <string>
#include <vector>
#include <stack>
#include <sstream>
#include <vector>
#include <iostream>
#include <list>

using namespace std;

class ArithNode
{
public:
	bool isOperator;
	char binaryOperator; // set only if isOperator = true
	int operand; // set only if isOperator = false
	ArithNode *left;
	ArithNode *right;

	ArithNode(char op) {
		left = NULL;
		right = NULL;
		binaryOperator = op;
		isOperator = true;
	}

	ArithNode(int n) {
		left = NULL;
		right = NULL;
		operand = n;
		isOperator = false;
	}

};


string Infix2RPN(string);
string RPN2Infix(string);
ArithNode *Infix2ExpressionTree(string);
ArithNode *RPN2ExpressionTree(string);
int EvaluateInfix(string);
int EvaluateRPN(string);

