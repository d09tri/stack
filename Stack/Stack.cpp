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

void main()
{
	Stack stack;
	char str[100];
	printf("Input brackets here: ");
	scanf("%s", &str);
	int n = strlen(str);

	if (areBracketsBalanced(stack, str, n))
		printf("Balanced\n");
	else
		printf("Unbalanced\n");

	system("pause");
}