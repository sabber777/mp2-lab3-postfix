
#include "postfix.h"
#include "stack.h"
#include <iostream>
#include <cctype>  
#include <cstdlib> 
using namespace std;

string TPostfix::ToPostfix()
{
	char result[MaxSize];
	int result_pos = 0;
	TStack<char> stack_op(MaxSize);
	for (unsigned int i = 0; i < infix.length(); i++)
	{

		if ((infix[i] != '(') && (infix[i] != ')') && (infix[i] != '+') && (infix[i] != '-') && (infix[i] != '*') && (infix[i] != '/'))
		{
			result[result_pos] = infix[i];
			result_pos++;
			result[result_pos] = '\0';
		}
	
		if (infix[i] == '(') stack_op.Push(infix[i]);
		                                          
		if (infix[i] == ')')
		{
			while (stack_op.Top() != '(')
			{
				result[result_pos] = stack_op.Pop();
				result_pos++;
				result[result_pos] = '\0';
			}
			stack_op.Pop();
		}
		
		if ((infix[i] == '+') || (infix[i] == '-') || (infix[i] == '*') || (infix[i] == '/'))
		{
			
			if (stack_op.IsEmpty() || stack_op.Top() == '(') stack_op.Push(infix[i]);
			
			else if (Priority(infix[i]) > Priority(stack_op.Top())) stack_op.Push(infix[i]);
			
			else
			{
				while (!stack_op.IsEmpty() && Priority(infix[i]) <= Priority(stack_op.Top()))
				{
					result[result_pos] = stack_op.Pop();
					result_pos++;
					result[result_pos] = '\0';
				}
				stack_op.Push(infix[i]);
			
			}
		}

	}
	
	while (stack_op.IsEmpty() == 0)
	{
		result[result_pos] = stack_op.Pop();
		result_pos++;
		result[result_pos] = '\0';
	}
	
	postfix = result;
	return postfix;
}

double TPostfix::Calculate()
{
	
	char a[MaxSize];
	double b[MaxSize];
	int flag;
	double k;

	TStack<double> stack(MaxSize);
	for (unsigned int i = 0; i < postfix.length(); i++)
	{
		
		if (postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/')
		{
			flag = 0;
			a[i] = postfix[i];
			for (int j = 0; j < i; j++)
				if (postfix[i] == a[j])
				{
					flag = 1;
					stack.Push(b[j]);
					break;
				}

			if (flag == 0)
			{
				char tmp[MaxSize];
				tmp[0] = postfix[i];
				tmp[1] = '\0';
				if ( isdigit(tmp[0]) ) b[i] = atoi(tmp); 
				else
				{
				cout << postfix[i] << "=";
				cin >> k;
				b[i] = k;
				}
				stack.Push(b[i]);
			}

		}
		else
			
		{
			if (postfix[i] == '+')
			{
				double tmp1 = stack.Pop();
				double tmp11 = stack.Pop();
				stack.Push(tmp11 + tmp1);
			}
			if (postfix[i] == '-')
			{
				double tmp1 = stack.Pop();
				double tmp11 = stack.Pop();
				stack.Push(tmp11 - tmp1);
			}
			if (postfix[i] == '/')
			{
				double tmp1 = stack.Pop();
				double tmp11 = stack.Pop();
				stack.Push(tmp11 / tmp1);
			}
			if (postfix[i] == '*')
			{
				double tmp1 = stack.Pop();
				double tmp11 = stack.Pop();
				stack.Push(tmp11 * tmp1);
			}
		}

	}

	return stack.Pop();;
}