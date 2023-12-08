#include <stdio.h>

#define SIZE 10 // 定义哈希表的大小为10

// 哈希表数据结构
typedef struct
{
    int key;
    int value;
} HashTable;

// 哈希表数组
HashTable hashTable[SIZE];

// 初始化哈希表，将所有桶置为空
void initHashTable()
{
    for (int i = 0; i < SIZE; i++)
    {
        hashTable[i].key = -1;
        hashTable[i].value = 0;
    }
}

// 哈希函数，计算键的哈希值
int hashFunction(int key)
{
    return key % SIZE;
}

// 线性探测再散列法插入键值对
void insert(int key, int value)
{
    int index = hashFunction(key);

    // 如果计算出的哈希桶为空，直接插入键值对
    if (hashTable[index].key == -1)
    {
        hashTable[index].key = key;
        hashTable[index].value = value;
    }
    // 如果发生冲突，使用线性探测再散列法查找下一个空桶
    else
    {
        int nextIndex = (index + 1) % SIZE;

        // 从当前哈希桶开始，依次向后查找下一个空桶
        while (nextIndex != index && hashTable[nextIndex].key != -1)
        {
            nextIndex = (nextIndex + 1) % SIZE;
        }

        // 如果找到空桶，则插入键值对
        if (hashTable[nextIndex].key == -1)
        {
            hashTable[nextIndex].key = key;
            hashTable[nextIndex].value = value;
        }
    }
}

// 输出哈希表
void printHashTable()
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", hashTable[i].value);
    }
    printf("\n");
}

int main()
{
    initHashTable(); // 初始化哈希表

    // 插入键值对
    insert(10, 5);
    insert(20, 8);
    insert(30, 12);
    insert(18, 15);

    printHashTable(); // 输出哈希表

    return 0;
}