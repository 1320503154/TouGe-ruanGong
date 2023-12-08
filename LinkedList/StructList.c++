#include <iostream>
using namespace std;
// 第一关代码

struct node
{ // 此处填写代码，定义链表结点类型，包含一个存放整型数据的 成员，和一个指向下一个结点的成员
    int data;
    struct node *next;
};

struct node *mycreateList()
{ // 此处填写代码，创建一个只有一个头结点的空链表，头节点的数据域赋值为0，并将表头结点的地址返回
    struct node *head;
    head = (struct node *)malloc(sizeof(struct node));
    // 为使得删除第i个结点和查找第i个结点的操作更方便实现，我们将头结点的数据域用于存放当前链表中的结点数。
    head->data = 0;
    head->next = NULL;
    return head;
}

// 第二关代码

void myinsertHead(struct node *head, int insData)
{
    /*在此处完成任务，实现在head为表头 在链表的头插数据元素insData的功能*/
    // begin
    struct node *insNode = (struct node *)malloc(sizeof(struct node));
    insNode->data = insData;
    insNode->next = head->next; // 新结点指向头结点的下一个结点
    head->next = insNode;       // 头结点指向新结点
    head->data++;               // 链表长度加一
    // end
}

void myinsertTail(struct node *head, int insData)
{
    /*在此处完成任务，在head为表头的单链表表尾插入数据元素insData*/
    // begin
    struct node *insNode = (struct node *)malloc(sizeof(struct node));
    insNode->data = insData;
    insNode->next = NULL;
    struct node *pointer = head;  // 指针指向头结点
    while (pointer->next != NULL) // 找到最后一个结点
    {
        pointer = pointer->next; // 指针指向下一个结点
    }
    pointer->next = insNode; // 最后一个结点指向新结点
    head->data++;
    // end
}

void myprintList(struct node *head)
{
    /*在此处完成任务，输出L为表头链表中的数据，每输出一个数据换一行*/
    // begin
    struct node *pointer = head->next;
    while (pointer != NULL)
    {
        printf("%d\n", pointer->data);
        pointer = pointer->next;
    }

    // end
}

// 第三关代码
int myfindPos(struct node *head, int position)
{
    // 请在此处填入代码，实现在链表中查找第position个结点的功能
    // begin
    if (position <= 0 || position > head->data)
    {
        return -1; // 查找失败，返回-1
    }
    struct node *temp = head->next;
    for (int i = 1; i < position; i++)
    {
        temp = temp->next;
    }
    return temp->data;
    // end
}

int myfindKey(struct node *head, int key)
{
    // 请在此处填入代码，实现在链表中查找与key值相同的第一个结点的功能
    // begin
    struct node *temp = head->next;
    while (temp != NULL)
    {
        if (temp->data == key)
        {
            return 1; // 找到数据，返回1
        }
        temp = temp->next;
    }
    return 0; // 未找到数据，返回0
    // end
}

// 第四关代码
int mydeletePos(struct node *L, int pos)
{
    // 请在此处填入代码，实现在链表中删除第pos个结点的功能
    // begin

    // end
}

int mydeleteKey(struct node *L, int key)
{
    // 请在此处填入代码，实现在链表中删除与key值相同的第一个结点的功能
    // begin

    // end
}

// 第五关代码
void reverseList_link(struct node *L)
{
    // 请在此处填入代码，实现链表逆置功能
    // begin

    // end
}
