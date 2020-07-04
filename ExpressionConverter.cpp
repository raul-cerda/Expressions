#include "ExpressionConverter.h"

// Write all your functions here

//checks if string is a number or "operand"
bool isOperand(string a)
{
	return (a != "+" && a != "-" && a != "*" && a != "/" && a != "(" && a != ")");
}

//first put string into vector with each element a number or operand
//then deal with each case, whether its a num, operator, or parenthese
string Infix2RPN(string a)
{
	stringstream s(a);
	vector<string> expression;
	string nextChar;
	while (getline(s, nextChar, ' '))
		expression.push_back(nextChar);

	stack<string> opStack;
	list<string> output;
	for (size_t i = 0; i < expression.size(); i++)
	{
		if (isOperand(expression[i]))
			output.push_back(expression[i]);
		else if (expression[i] == "(")
			opStack.push(expression[i]);
		else if (expression[i] == ")")
		{
			while (opStack.top() != "(")
			{
				output.push_back(opStack.top());
				opStack.pop();
			}
			opStack.pop();
		}
		else
		{   
			if (!opStack.empty())
			{
				if (expression[i] == "*" || expression[i] == "/")
				{
					while ((opStack.top() == "*" || opStack.top() == "/") && opStack.top() != "(")
					{
						output.push_back(opStack.top());
						opStack.pop();
					}
				}
				else
				{
					while (!opStack.empty() && opStack.top() != "(")
					{
						output.push_back(opStack.top());
						opStack.pop();
					}
				}
			}
			opStack.push(expression[i]);
		}
	}

	while (!opStack.empty())
	{
		output.push_back(opStack.top());
		opStack.pop();
	}

	string result = "";
	result.append(output.front());
	output.pop_front();
	while (!output.empty())
	{
		result.append(" ");
		result.append(output.front());
		output.pop_front();
	}
	return result;
}

//recursive inorder traversal thru tree, print part of expression each step
// isOperator used as an operator will always have 2 children
string ExpressionTree2Infix(ArithNode * head)
{
	string result = "";
	if (head->isOperator)
	{
		return "(" + ExpressionTree2Infix(head->left) + head->binaryOperator
			+ ExpressionTree2Infix(head->right) + ")";
	}
	return to_string(head->operand);
}

//convert the string to tree, then use recursive method to turn into infix
string RPN2Infix(string a)
{
	ArithNode * temp;
	temp = RPN2ExpressionTree(a);
	return ExpressionTree2Infix(temp); //this returs stoi out of bounds
}

//cycle from infix to rpn, then rpn to expression tree method
ArithNode * Infix2ExpressionTree(string a)
{
	string temp = Infix2RPN(a);
	return RPN2ExpressionTree(temp);
}

//use stack to enter each node of tree, with operator as head
ArithNode * RPN2ExpressionTree(string a)
{
	int forUse;
	ArithNode * fir;
	ArithNode * sec;
	stack<ArithNode*> nodes;
	stringstream s(a);
	vector<string> express;
	string temp;
	while (getline(s, temp, ' '))
		express.push_back(temp);
	for (size_t i = 0; i < express.size(); i++)
	{
		if (isOperand(express[i]))
		{
			forUse = stoi(express[i]);
			nodes.push(new ArithNode(forUse));
		}
		else 
		{
			fir = nodes.top();
			nodes.pop();
			sec = nodes.top();
			nodes.pop();
			nodes.push(new ArithNode(express[i][0]));
			nodes.top()->left = sec;
			nodes.top()->right = fir;
		}
	}
	ArithNode * tree = nodes.top();
	return tree;
}

//convert to rpn then evaluate
int EvaluateInfix(string a)
{
	string result = Infix2RPN(a);
	return EvaluateRPN(result);
}

//use stack to evaluate based on operator precedence
int EvaluateRPN(string a)
{
	stack<int> operandStack;
	stringstream s(a);
	vector<string> express;
	string temp;
	while (getline(s, temp, ' '))
		express.push_back(temp);

	for (size_t i = 0; i < express.size(); i++)
	{
		if (isOperand(express[i]))
			operandStack.push(stoi(express[i]));
		else
		{
			int sec = operandStack.top();
			operandStack.pop();
			int fir = operandStack.top();
			operandStack.pop();
			if (express[i] == "+")
				operandStack.push(fir+sec);
			if(express[i] == "-")
				operandStack.push(fir - sec);
			if (express[i] == "*")
				operandStack.push(fir * sec);
			if (express[i] == "/")
				operandStack.push(fir/sec);
		}
	}
	return operandStack.top();
}