#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SNode
{
	char data;
	SNode *next;
};

struct Stack
{
	SNode *top;
};

void initStack(Stack &stack)
{
	stack.top = NULL;
}

bool isEmpty(Stack stack)
{
	return stack.top == NULL;
}

SNode *createSNode(char c)
{
	SNode *p = new SNode;
	if (p != NULL)
	{
		p->data = c;
		p->next = NULL;
	}
	return p;
}

void push(Stack &stack, char c)
{
	SNode *p = createSNode(c);
	if (p == NULL)
		return;
	if (isEmpty(stack))
		stack.top = p;
	else
	{
		p->next = stack.top;
		stack.top = p;
	}
}

char pop(Stack& stack, char& c)
{
	if (isEmpty(stack))
		return '/0';
	else
	{
		SNode* p = stack.top;
		stack.top = p->next;
		c = p->data;
		delete p;
		return c;
	}
}

bool areBracketsBalanced(Stack& stack, char str[], int n)
{
	initStack(stack);
	char c;
	for (int i = 0; i < n; i++)
	{
		if (str[i] == '(' || str[i] == '[' || str[i] == '{')
			push(stack, str[i]);
		else
		{
			if (!isEmpty(stack))
			{
				if (str[i] == ')')
				{
					if (stack.top->data != '(')
						return false;
				}
				if (str[i] == ']')
				{
					if (stack.top->data != '[')
						return false;
				}
				if (str[i] == '}')
				{
					if (stack.top->data != '{')
						return false;
				}
				pop(stack, c);
			}
			else
				return false;
		}
	}
}

int findPriority(char c)
{
	if (c == '+' || c == '-')
		return 1;
	if (c == '*' || c == '/')
		return 2;
	if (c == '^')
		return 3;
	return 0;
}

char sTemp[100];

void infixToPostfix(Stack &stack, char s[], int n)
{
	initStack(stack);
	int j = 0;
	char c;
	for (int i = 0; i < n; i++)
	{
		if (s[i] >= '0' && s[i] <= '9' || s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z')
		{
			sTemp[j] = s[i];
			j++;
		}
		else if (s[i] == '(')
			push(stack, s[i]);
		else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '^' || s[i] == '*')
		{
			if (isEmpty(stack))
				push(stack, s[i]);
			else if (findPriority(stack.top->data) >= findPriority(s[i]))
			{
				c = pop(stack, c);
				sTemp[j] = c;
				j++;
				push(stack, s[i]);
			}
			else
				push(stack, s[i]);
		}
		else if (s[i] == ')')
		{
			while (!isEmpty(stack) && stack.top->data != '(')
			{
				c = pop(stack, c);
				sTemp[j] = c;
				j++;
			}
		}
	}
	while (!isEmpty(stack))
	{
		c = pop(stack, c);
		if (c == '(' || c == ')')
			continue;
		else
		{
			sTemp[j] = c;
			j++;
		}
	}
}

void main()
{
	Stack stack;
	char str[100];
	printf("Input brackets/infix here: ");
	scanf("%s", &str);
	int n = strlen(str);

	infixToPostfix(stack, str, n);
	for (int i = 0; i < strlen(sTemp); i++)
	{
		printf("%c", sTemp[i]);
	}

	/*
	if (areBracketsBalanced(stack, str, n))
		printf("Balanced");
	else
		printf("Unbalanced");
	*/

	printf("\n");
	system("pause");
}