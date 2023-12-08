#include <stdio.h>
#include <stdlib.h>
struct node
{ // 链表结点类型，包含一个存放整型数据的 data 成员，和一个指向下一个结点的next成员
    int data;
    struct node *next;
};

struct node *mycreateList()
{ // 函数功能：创建一个只有一个头结点的空链表，头节点的数据域赋值为0，并将表头结点的地址返回
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->data = 0;
    head->next = NULL;
    return head;
}

void myinsertHead(struct node *head, int insData)
{
    /*函数功能：实现在head为表头的链表中使用头插法，插入数据元素insData*/
    struct node *p;
    p = (struct node *)malloc(sizeof(struct node));
    p->data = insData;
    p->next = head->next;
    head->next = p;
}

void myinsertTail(struct node *head, int insData)
{
    /*在head为表头的单链表表尾插入数据元素insData*/
    struct node *p, *q;
    p = (struct node *)malloc(sizeof(struct node));
    p->data = insData;
    p->next = NULL;
    q = head;
    while (q->next != NULL)
        q = q->next;
    q->next = p;
}

void myprintList(struct node *L)
{
    /*输出head为表头的链表中的数据元素，每输出一个数据空一格*/
    struct node *p = L->next;
    while (p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
}
void genNumber(struct node *A, int num)
{ // 本函数用于接收输入的大数的各个位，返回大数链表表头，可使用上面已实现的链表插入函数
    /*------begin---------*/
    // 从控制台读取要插入链表的数字,然后num是插入多少个数字
    A->data = num;
    int data = 0;
    for (int i = 1; i <= num; i++)
    {
        scanf("%d", &data);
        // 头插法,保存低位在前
        myinsertHead(A, data);
    }
    /*------end---------*/
}

struct node *addNumber(struct node *A, struct node *B)
{
    // 此处实现函数求两数相加，并返回和值链表的表头；
    /*------begin---------*/
    struct node *newhead = mycreateList();
    // sum表示两个数相加的和，carry表示进位
    int sum = 0;
    // 跳过头结点
    A = A->next;
    B = B->next;
    // 当其中一个链表不为空时,一直进行
    while (A != NULL || B != NULL)
    {
        if (A != NULL && B != NULL)
        {
            // 因为采用头插法,所以低位在前,比如5->2->1,插入后为1->2->5
            sum = A->data + B->data;
            if (sum >= 10)
            {
                // 进位
                myinsertHead(newhead, sum % 10); // 保存低位,9+5=14,则保存4,进位1
                sum = sum / 10;
            }
            else // 如果sum没有溢出
            {
                myinsertHead(newhead, sum);
                sum = 0; // 重置sum,开始新的循环计算
            }
            A = A->next;
            B = B->next;
        }
        else
        { // 如果其中一个为空
            if (A == NULL)
            { // 一直移动B链表指针即可
                sum += B->data;
                if (sum >= 10)
                {
                    myinsertHead(newhead, sum % 10);
                    sum = sum / 10;
                }
                else
                {
                    myinsertHead(newhead, sum);
                    sum = 0;
                }
                B = B->next;
            }
            else
            {
                sum += A->data;
                if (sum >= 10)
                {
                    myinsertHead(newhead, sum % 10);
                    sum = sum / 10;
                }
                else
                {
                    myinsertHead(newhead, sum);
                    sum = 0;
                }
                A = A->next;
            }
        }
    }
    // 如果最后还有进位,则插入
    if (sum != 0)
    {
        myinsertHead(newhead, sum);
    }
    return newhead;
    /*------end---------*/
}

int main(void)
{
    struct node *A, *B, *C;
    int i, j;
    A = mycreateList();
    B = mycreateList();
    scanf("%d", &i);

    genNumber(A, i);

    scanf("%d", &j);

    genNumber(B, j);

    C = addNumber(A, B);
    myprintList(C);
    return 1;
}
