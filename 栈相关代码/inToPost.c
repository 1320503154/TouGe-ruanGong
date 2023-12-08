#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

typedef char elType;

struct stack
{
    elType *arr;
    int size;
    int top;
};

typedef struct stack *Stack;

Stack create_stack()
{
    Stack myStack = (Stack)malloc(sizeof(struct stack));
    if (myStack != NULL)
    {
        myStack->arr = (elType *)malloc(sizeof(elType) * 300);
        myStack->size = 0;
        myStack->top = 0;
        return myStack;
    }
    else
    {
        printf("无法创建栈\n");
        return NULL;
    }
}

int isEmpty(Stack myStack)
{
    if (myStack == NULL)
    {
        return 1;
    }
    if (myStack->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void push(Stack myStack, elType data)
{
    myStack->arr[myStack->top] = data;
    myStack->top++;
    myStack->size++;
}

elType pop(Stack myStack)
{
    if (isEmpty(myStack))
    {
        printf("栈为空，无法执行 pop 操作\n");
        return -1;
    }
    elType data = myStack->arr[myStack->top];
    myStack->top--;
    myStack->size--;
    return data;
}

elType top(Stack myStack)
{
    return myStack->arr[myStack->top - 1];
}

int getPriority(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

bool isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Stack inToPost(char *expression)
{
    Stack postfixStack = create_stack();
    Stack operatorStack = create_stack();
    int i = 0;
    while (expression[i] != '\0')
    {
        if (isdigit(expression[i]))
        {
            int operand = 0;
            while (isdigit(expression[i]))
            {
                operand = operand * 10 + (expression[i] - '0');
                i++;
            }
            push(postfixStack, operand + '0');
        }
        else if (isOperator(expression[i]))
        {
            if (isEmpty(operatorStack) || getPriority(expression[i]) > getPriority(top(operatorStack)))
            {
                push(operatorStack, expression[i]);
            }
            else
            {
                while (!isEmpty(operatorStack) && getPriority(expression[i]) <= getPriority(top(operatorStack)))
                {
                    elType operator= pop(operatorStack);
                    push(postfixStack, operator);
                }
                push(operatorStack, expression[i]);
            }
            i++;
        }
        else if (expression[i] == '(')
        {
            push(operatorStack, expression[i]);
            i++;
        }
        else if (expression[i] == ')')
        {
            while (!isEmpty(operatorStack) && top(operatorStack) != '(')
            {
                elType operator= pop(operatorStack);
                push(postfixStack, operator);
            }

            if (!isEmpty(operatorStack) && top(operatorStack) == '(')
            {
                pop(operatorStack);
            }
            i++;
        }
    }
    while (!isEmpty(operatorStack))
    {
        elType operator= pop(operatorStack);
        push(postfixStack, operator);
    }

    return postfixStack;
}

void print(Stack s)
{
    printf("输出栈元素: ");
    for (int i = 0; i < s->size; i++)
    {
        printf("%c ", s->arr[i]);
    }
    printf("\n");
}

int main(void)
{
    char express[80];
    printf("请输入表达式：\n");
    gets(express);
    Stack s = inToPost(express);
    print(s);
    return 0;
}