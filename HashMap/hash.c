#include <stdio.h>
#include <stdlib.h>

/*哈希结构*/
#define MAXNUM 10 // 哈希表最大长度
typedef struct hashTable
{
    int *element; // 存放键值的连续空间起始地址
    int maxNum;   // 哈希表长度
    int curNum;   // 当前哈希表已有数据元素
} ht;

struct node
{
    int data;
    struct node *next;
};
typedef struct node *Node;
typedef struct hashTable_link
{
    struct node *element;
    int maxNum; // 哈希表长度
} htl;          // 链地址法:把所有冲突的同义词都放在一个链表里

/*第一关*/
// 初始化一个哈希表，能满足线性探测在散列处理冲突法使用，初始化哈希表元素均为-1，表示该位置为空，可插入
struct hashTable *initHashTable_linear()
{
    ht *hashTable = (ht *)malloc(sizeof(ht));
    hashTable->element = (int *)malloc(sizeof(int) * MAXNUM);
    hashTable->maxNum = MAXNUM;
    hashTable->curNum = 0;
    for (int i = 0; i < MAXNUM; i++)
    {
        hashTable->element[i] = -1;
    }
    return hashTable;
}

// 初始化一个哈希表，能满足拉链法处理冲突法使用。初始化哈希表元素为0，用于计算该条链中数据个数，在插入时增加
struct hashTable_link *initHashTable_link()
{
    htl *hashTableLink = (htl *)malloc(sizeof(htl));
    hashTableLink->element = (struct node *)malloc(sizeof(struct node) * MAXNUM);
    hashTableLink->maxNum = MAXNUM;
    hashTableLink->element->data = 0;
    hashTableLink->element->next = NULL;
    return hashTableLink;
}

/*第二关*/
// 输出线性探测再散列法构建的哈希表,从下标为0的元素开始输出，每输出一个数据空一格
void printHashTable(struct hashTable *h)
{
    for (int i = 0; i < h->maxNum; i++)
    {
        printf("%d ", h->element[i]);
    }
}

/*第三关*/
// 哈希函数，h(key) = (key*3) %  7
int hashFun(int key)
{
    return (key * 3) % 7;
}

// 函数功能：计算key的哈希地址，若发生冲突，则使用线性探测再散列的方法查找合适的插入位置下标，并返回该下标
int findPos(struct hashTable *h, int key)
{
    int index = hashFun(key);
    if (h->element[index] == -1) // 如果哈希表中该位置为空，则直接返回下标
    {
        return index;
    }
    int nextIndex = (index + 1) % h->maxNum; // 取余最大元素个数，防止数组越界
    while (h->element[nextIndex] != -1)      // 当下一个位置不为空时，继续往后找
    {
        nextIndex = (nextIndex + 1) % h->maxNum;
    }
    return nextIndex; // 找到空位置，返回下标
}

// 插入键值函数,若哈希表空间已满，则返回-1，否则返回插入位置下标
int insertKey(struct hashTable *h, int key)
{
    if (h->curNum == h->maxNum)
    {
        return -1;
    }
    int index = findPos(h, key);
    h->element[index] = key; // 此处的key就是value:存在哈希表的data
    h->curNum++;
    return index;
}
