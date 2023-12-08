#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
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
        myStack->top = -1; // 初始化 top 为 -1
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
        return -1;
    }
    if (myStack->top == -1) // 栈为空时 top 等于 -1
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
    myStack->arr[++(myStack->top)] = data; // 增加 top 后再插入元素
    myStack->size++;
}

elType pop(Stack myStack)
{
    if (isEmpty(myStack))
    {
        printf("栈为空，无法执行 pop 操作\n");
        return -1;
    }
    elType data = myStack->arr[myStack->top--]; // 先在top位置插入元素,然后再top--
    myStack->size--;
    return data;
}

elType top(Stack myStack)
{
    if (isEmpty(myStack))
    {
        printf("栈为空，无法执行 top 操作\n");
        return -1;
    }
    return myStack->arr[myStack->top];
}

int getPriority(char op) // 得到运算符的优先级
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

bool isOperator(char c) // 是操作符吗?
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

Stack inToPost(char *expression)
{
    // 写出解释下列代码的注释
    Stack postfixStack = create_stack();  // 创建一个后缀栈
    Stack operatorStack = create_stack(); // 创建一个操作符栈
    int i = 0;
    while (expression[i] != '\0') // 遍历表达式
    {
        if (isdigit(expression[i])) // 如果是数字
        {
            int operand = 0;               // 操作数
            while (isdigit(expression[i])) // 如果是数字
            {
                operand = operand * 10 + (expression[i] - '0'); // 将字符转换为数字
                i++;                                            // 下一个字符
            }
            push(postfixStack, operand + '0'); // 将操作数压入后缀栈
        }
        else if (isOperator(expression[i])) // 如果是操作符
        {
            if (isEmpty(operatorStack) || getPriority(expression[i]) > getPriority(top(operatorStack))) // 如果操作符栈为空或者当前操作符的优先级大于操作符栈顶的优先级
            {
                push(operatorStack, expression[i]); // 将操作符压入操作符栈
            }
            else
            {
                while (!isEmpty(operatorStack) && getPriority(expression[i]) <= getPriority(top(operatorStack))) // 如果操作符栈不为空且当前操作符的优先级小于等于操作符栈顶的优先级
                {
                    elType operator= pop(operatorStack); // 将操作符栈顶的操作符弹出
                    push(postfixStack, operator);        // 将操作符压入后缀栈
                }
                push(operatorStack, expression[i]); // 将当前操作符压入操作符栈
            }
            i++; // 下一个字符
        }
        else if (expression[i] == '(') // 如果是左括号
        {
            push(operatorStack, expression[i]); // 将左括号压入操作符栈
            i++;
        }
        else if (expression[i] == ')') // 如果是右括号
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
        else
        {
            // Ignore other characters like spaces
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
    for (int i = 0; i < s->size; i++)
    {
        printf("%c ", s->arr[i]);
    }
    printf("\n");
}

int main()
{
    char expression[] = "3 + 2 * (5 - 1) / 2";
    Stack postfix = inToPost(expression);
    print(postfix);

    return 0;
}