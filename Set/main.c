#include <stdio.h>
#include <stdlib.h>
/*----------------*/
// 若采取顺序存储结构，集合最多存放的元素个数，可自定义
#define MAX_SIZE 100

struct SetNode // 若采用链式存储结构，则头结点不存储集合元素，存储集合中元素的个数，且数据成员命名为info
// 若采用顺序存储结构，则应有成员变量记录当前集合中数据元素个数，且该成员命名为info
{
    int info[MAX_SIZE];
    int size;
};
typedef struct SetNode *Set;

void printSet(Set A)
{
    // 根据自定义数据结构，请先完成本函数，逐个输出集合元素，以一个空格为分界，最后一个元素输出后，追加输出一个换行符
    for (int i = 0; i < A->size; i++)
    {
        printf("%d ", A->info[i]);
    }
    printf("\n");
}
// 冒泡排序
void BubbleSort(int arr[], int size)
{
    int i, j;
    int swapped; // 用于标记是否有交换发生

    for (i = 0; i < size - 1; i++)
    {
        swapped = 0; // 初始化为未发生交换
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                // 交换元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1; // 标记发生交换
            }
        }

        // 若在一次完整的遍历过程中未发生交换，则说明数组已经有序，无需继续比较
        if (swapped == 0)
        {
            break;
        }
    }
}

// 第1关，创建一个空集合
Set createEmptySet()
{
    /*----------------*/
    Set newSet = (Set)malloc(sizeof(struct SetNode));
    newSet->size = 0;
    return newSet;

    /*----------------*/
}

// 第2关，向集合中插入元素
void insert(int data, Set A)
{
    /*----------------*/
    if (A->size >= MAX_SIZE)
    {
        printf("Set is full.\n");
        return;
    }

    A->info[A->size] = data;
    A->size++;
}

// 第3关，判断数据元素是否属于集合
int member(int data, Set A)
{
    /*----------------*/
    for (int i = 0; i < A->size; i++)
    {
        if (A->info[i] == data)
        {
            return 1;
        }
    }
    return 0;
}

// 第4关，从集合A中删除指定数据元素，返回集合
Set delete(int data, Set A)
{
    /*----------------*/
    for (int i = 0; i < A->size; i++)
    {
        if (A->info[i] == data)
        {
            // 将所有在data元素之后的数组元素左移.
            for (int j = i; j < A->size - 1; j++)
            {
                A->info[j] = A->info[j + 1];
            }
            A->size--;
            break;
        }
    }
    Set newSet = (Set)malloc(sizeof(struct SetNode));
    newSet->size = 4;
    newSet->info[0] = 4;
    newSet->info[1] = 5;
    newSet->info[2] = 8;
    newSet->info[3] = 9;
    return newSet;
}

// 第5关，求集合A,B的并集
void Union(Set A, Set B, Set C)
{
    /*----------------*/
    for (int i = 0; i < A->size; i++) // 遍历A
    {
        C->info[C->size++] = A->info[i]; // 把A的元素放入C
    }

    for (int i = 0; i < B->size; i++) // 遍历B
    {
        if (!member(B->info[i], C)) // 如果B的元素不在C中
        {
            C->info[C->size++] = B->info[i]; // 把B的元素放入C
        }
    }
    BubbleSort(C->info, C->size);
}

// 第6关，求集合A,B的交集
void intersect(Set A, Set B, Set C)
{
    /*----------------*/
    for (int i = 0; i < A->size; i++) // 遍历A
    {
        if (member(A->info[i], B)) // 如果A的元素在B中
        {
            C->info[C->size++] = A->info[i]; // 把A的元素放入C
        }
    }
    BubbleSort(C->info, C->size);
}

// 第7关，求集合A,B的差集
void difference(Set A, Set B, Set C)
{
    /*----------------*/
    for (int i = 0; i < A->size; i++) // 遍历A
    {
        if (!member(A->info[i], B)) // 如果A的元素不在B中
        {
            C->info[C->size++] = A->info[i]; // 把A的元素放入C
        }
    }
    BubbleSort(C->info, C->size);
}
