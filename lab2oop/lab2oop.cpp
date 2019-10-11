#include <iostream>
#include <stack>
#include "Stack.h"

std::string infix_to_postfix(std::string infix);
double evaluate_postfix(std::string postfix);

int main()
{
	/* Stack<int> stk1;
	for (int i = 0; i < 5; i++)
		std::cin >> stk1;

	std::cout << stk1[3];

	Stack<int> stk2 = stk1;
	std::cout << stk1;
	std::cout << stk2;

	Stack<int> stk3;
	for (int i = 0; i < 5; i++)
		stk3.push(i * 777);

	std::cout << stk3;

	stk3 = stk2;
	std::cout << stk2;
	std::cout << stk3; */

	while (true)
	{
		std::string infix;
		std::cout << "Input expression: ";
		std::cin >> infix;
		if (infix == "stop")
			break;

		std::string postfix = infix_to_postfix(infix);
		std::cout << "Postfix form: " << postfix << std::endl;

		double result = evaluate_postfix(postfix);
		std::cout << "Result: " << result << std::endl << std::endl;
	}
	
	return 0;
}

//Function to return precedence of operators.
int prec(char c)
{
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}

// Function to convert infix expression to postfix.
std::string infix_to_postfix(std::string infix)
{
	Stack<char> stk;
	stk.push('#');
	std::string postfix;

	for (int i = 0; infix[i]; i++)
	{
		// If the scanned character is an operand, add it to the postfix string.
		if (isdigit(infix[i]))
			postfix += infix[i];

		// If the scanned character is an '(', push it to the stack.
		else if (infix[i] == '(')
			stk.push('(');

		// If the scanned character is an ‘)’, 
		// pop the stack and write to postfix string until an ‘(‘ is reched. 
		else if (infix[i] == ')')
		{
			while (stk.top() != '#' && stk.top() != '(')
				 postfix += stk.pop();
			if (stk.top() == '(')
				stk.pop();
		}

		// The scanned character is an operator.
		else 
		{
			while (stk.top() != '#' && prec(infix[i]) <= prec(stk.top()))
				postfix += stk.pop();
			stk.push(infix[i]);
		}
	}

	//Pop all the remaining elements from the stack.
	while (stk.top() != '#')
		postfix += stk.pop();

	return postfix;
}

double evaluate_postfix(std::string postfix)
{
	Stack<double> stk;

	for (int i = 0; postfix[i]; i++)
	{
		// If the scanned character is an operand,  
		// push it to the stack.  
		if (isdigit(postfix[i]))
			stk.push(postfix[i] - 48.0);

		// If the scanned character is an operator, pop two
		// elements from the stack and apply the operator.
		else
		{
			double val1 = stk.pop();
			double val2 = stk.pop();

			switch (postfix[i])
			{
			case '+': stk.push(val2 + val1); break;
			case '-': stk.push(val2 - val1); break;
			case '*': stk.push(val2 * val1); break;
			case '/': stk.push(val2 / val1); break;
			case '^': stk.push(pow(val2, val1)); break;
			}
		}
	}
	return stk.pop();
}
