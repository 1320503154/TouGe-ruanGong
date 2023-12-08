#include <iostream>
#include <string>
using namespace std;
// Passionate about C++
typedef char DataType;

// 队列数据元素结构
typedef struct node
{
    DataType info;
    struct node *next;
    node(DataType x) : info(x), next(NULL) {} // c++的魅力,相较于c而言
} QueueData;

typedef struct queueRecord
{
    QueueData *front, *rear;
    queueRecord() : front(NULL), rear(NULL) {}
} LINKQUEUE;

typedef struct queueRecord *PLinkQueue;

PLinkQueue createEmptyQueue_link()
{
    // 创建一个空队列，实质：生成一个LINKQUEUE类型的结点，并给front 和 rear 成员赋值
    // 请在此处填写代码，完成相应功能
    /*-------begin----------*/
    PLinkQueue queue = new LINKQUEUE();
    return queue;
    /*-------end----------*/
}

int isEmptyQueue_link(PLinkQueue queue)
{ // 判定队列是否为空，实质： 看队列的front指针是否为空，若为空，则队列为空

    // 请在此处填写代码，完成相应功能
    /*-------begin----------*/
    if (queue->front == NULL)
        return 1;
    else
        return 0;
    /*-------end----------*/
}

void enQueue_link(DataType x, PLinkQueue queue)
{
    // 将数据元素x插入队尾。实质：生成一个struct node类型的结点，并给相应成员赋值后插入队尾
    // 请在此处填写代码，完成相应功能
    /*-------begin----------*/
    QueueData *newNode = new QueueData(x);
    if (isEmptyQueue_link(queue))
    {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    /*-------end----------*/
}

void enQueue_link(QueueData *p, PLinkQueue Q)
{
    // 本函数的功能是将 struct node 类型的结点插入队尾，与enQueue_link(DataType x, PLinkQueue queue)的区别是，不需要生成结点

    // 请在此处填写代码，完成相应功能
    /*-------begin----------*/
    if (isEmptyQueue_link(Q))
    {
        Q->front = p;
        Q->rear = p;
    }
    else
    {
        Q->rear->next = p;
        Q->rear = p;
    }
    /*-------end----------*/
}
// 本关任务：实现队列基本操作，并使用队列基本操作解决密码加密和解密问题。

// 密码加密原理描述如下：
// 将明文（一个字符串）的每个字符按照字母表后移，每个字符的后移个数由秘钥值列表确定，如果明文比密钥值列表长，可以从头再使用这个密钥值列表。
// 如明文：student，秘钥：2345，
// 则加密方法是：s（向后移动2位）变成u，t（向后移动3位）变成w，u （向后移动4位）变成y，d（向后移动5位） 变成i，此时秘钥用完，所以从头开始用2进行移位加密，依此类推可以得到加密后的密文。而解密时，只需将密文根据秘钥反推就可以得到明文。
DataType deQueue_link(PLinkQueue Q)
{
    // 出队，实质： 取出Q队列的队首结点，返回该结点的数据元素，并将该结点使用enQueue_link(QueueData *p,PLinkQueue Q)插入队尾
    // 本函数为针对本实验特殊设计，可实现秘钥的循环使用
    // 使用队列先进先出原理，访问秘钥列表方法有多种，本实验要求： 使用循环队列相关操作。设计思路：利用出队操作，获得队首秘钥，用完该秘钥后将秘钥重新插入队尾，可实现秘钥的循环使用。
    // 请在此处填写代码，完成相应功能
    /*-------begin----------*/
    QueueData *p = Q->front;
    DataType x = p->info;
    Q->front = p->next;   // 出队,修改队首指针
    if (Q->front == NULL) // 如果队列为空
        Q->rear = NULL;   // 队尾指针置空
    enQueue_link(p, Q);   // 将出队的结点插入队尾
    return x;
    /*-------end----------*/
}

void decrypt(string src, string key, string &dest)
{
    /*  参数： src 放的是源文 ； key 放的是秘钥 ； dest 放加密后的密文
       加密函数： 步骤提示
       1. 初始化一个空队列Q
       2. 将key数组的元素逐个插入队列Q
       3. 逐个访问src数组的源文，并加密， 使用deQueue_link(Q)函数可得到队首秘钥，并使秘钥循环使用
    */
    PLinkQueue queue = createEmptyQueue_link();

    string dest(src.length(), ' '); // 初始化 dest 为与 src 相同长度的空字符串

    for (char keyChar : key) // 使用循环逐个访问字符串内的单个字符
    {
        enQueue_link(keyChar, queue);
    }
    int i = 0;
    for (char charactor : src)
    {
        DataType keyChar = deQueue_link(queue);
        dest[i] = charactor + keyChar - '0';
        i++;
    }
    dest += '\0'; // 末尾加上结束符
}

int main(void)
{
    string src, key, dest;

    cin >> src;

    cin >> key;
    decrypt(src, key, dest);
    cout << dest;
}
