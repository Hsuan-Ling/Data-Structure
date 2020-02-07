#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
using namespace std;

template <class T>
class Stack
{
private:
	int index = -1;
	T stack[100];

public:

	bool isEmpty()
	{
		if (index == -1) return true;
		return false;
	}

	T& top()
	{
		if (!isEmpty()) return stack[index];
	}

	void push(T value)
	{
		index++;
		stack[index] = value;
	}

	void pop()
	{
		stack[index].~T();
		index--;
	}
};

int isp( char c )
{
	switch (c)
	{
	case '*':
	case '/':
	case '%':
		return 1;

	case '+':
	case '-':
		return 2;

	case '#':
	case '(':
		return 3;

	default:
		return -1;
	}
}

int icp(char c)
{
	switch (c)
	{
	case '(':
		return 0;

	case '*':
	case '/':
	case '%':
		return 1;

	case '+':
	case '-':
		return 2;

	case '#':

		return 3;

	default:
		return -1;
	}
}

string postfix(string infix)
{
	Stack<char> stack;
	string output;

	infix += '#';
	stack.push('#');

	for (int i = 0; i < infix.size(); i++)
	{
		if (isalnum(infix[i])) output += infix[i];
		else if (infix[i] == '#') {}
		else if (infix[i] == ')')
		{
			while (stack.top() != '(')
			{
				output += stack.top();
				stack.pop();

			}
			stack.pop();
		}
		else
		{
			while (isp(stack.top()) <= icp(infix[i]))
			{
				output += stack.top();
				stack.pop();
			}
			stack.push(infix[i]);
		}
	}

	while (!stack.isEmpty() && stack.top() != '#')
	{
		output += stack.top();
		stack.pop();
	}

	return output;
}

string prefix(string infix)
{
	reverse(infix.begin(), infix.end());

	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(') infix[i] = ')';
		else if (infix[i] == ')') infix[i] = '(';
	}

	Stack<char> stack;
	string output;

	infix += '#';
	stack.push('#');

	for (int i = 0; i < infix.size(); i++)
	{
		if (isalnum(infix[i])) output += infix[i];
		else if (infix[i] == '#') {}
		else if (infix[i] == ')')
		{
			while (stack.top() != '(')
			{
				output += stack.top();
				stack.pop();

			}
			stack.pop();
		}
		else
		{
			while (isp(stack.top()) < icp(infix[i]))
			{
				output += stack.top();
				stack.pop();
			}
			stack.push(infix[i]);
		}
	}

	while (!stack.isEmpty() && stack.top() != '#')
	{
		output += stack.top();
		stack.pop();
	}

	reverse(output.begin(), output.end());
	return output;
}

int main()
{
	string input;
	while (getline(cin, input))
	{
		cout << "Postfix: " << postfix(input) << endl;
		cout << "Pretfix: " << prefix(input) << endl << endl;
	}
}