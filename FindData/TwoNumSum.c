// #include <stdio.h>
// void compute(int data[], int n, int target)
// { // 在此处填写代码，在data数组中查找是否存在两个元素之和为target，并按要求输出
//     /*-----------begin---------------*/
//     // 力扣第一题两数之和,使用哈希表即可
//     int found = 0;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++) // j = 1
//         {
//             if (data[i] + data[j] == target)
//             {
//                 found = 1;
//                 printf("%d %d\n", i, j);
//                 return;
//             }
//         }
//     }
//     if (found == 0)
//     {
//         printf("-1 -1\n");
//     }
//     /*-----------end---------------*/
// }

// int main(void)
// {
//     int a[] = {-3, 2, 5, 9, 15, 32};
//     int x;
//     scanf("%d", &x);
//     compute(a, 6, x);
// }

// 复杂版本如下
#include <stdio.h>
#include <stdlib.h>

struct HashNode
{
    int key;   // 存储的是nums[i],数组元素
    int value; // 存储的是i,数组下标
    struct HashNode *next;
};

struct HashTable
{
    struct HashNode **buckets; // 这里的两个*号是指针的指针，也就是说buckets是一个指针数组,每个元素都是一个指针
    int size;
};

struct HashTable *createHashTable(int size)
{
    struct HashTable *hashTable = (struct HashTable *)malloc(sizeof(struct HashTable));
    hashTable->size = size;
    hashTable->buckets = (struct HashNode **)calloc(size, sizeof(struct HashNode *));
    return hashTable;
}

struct HashNode *createHashNode(int key, int value)
{
    struct HashNode *newNode = (struct HashNode *)malloc(sizeof(struct HashNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void insertNode(struct HashTable *hashTable, int key, int value)
{
    int index = abs(key) % hashTable->size;                // 除留余数法,绝对值处理key
    struct HashNode *newNode = createHashNode(key, value); // 创建新节点
    if (hashTable->buckets[index] == NULL)                 // 如果该位置为空,直接插入
    {
        hashTable->buckets[index] = newNode; // 将新节点插入到该位置
    }
    else // 如果该位置不为空,则将新节点插入到链表的最后
    {
        struct HashNode *node = hashTable->buckets[index]; // 获取该位置的头节点
        while (node->next != NULL)                         // 遍历链表,找到最后一个节点
        {
            node = node->next; // 移动到下一个节点
        }
        node->next = newNode; // 将新节点插入到链表的最后
    }
}

struct HashNode *searchNode(struct HashTable *hashTable, int key)
{
    int index = abs(key) % hashTable->size;            // 除留余数法,绝对值处理key
    struct HashNode *node = hashTable->buckets[index]; // 获取该位置的头节点
    while (node != NULL)                               // 遍历链表
    {
        if (node->key == key) // 如果找到了,返回该节点
        {
            return node; // 返回该节点
        }
        node = node->next; // 移动到下一个节点
    }
    return NULL; // 如果没有找到,返回NULL
}

void freeHashTable(struct HashTable *hashTable)
{
    if (hashTable == NULL)
    {
        return;
    }
    for (int i = 0; i < hashTable->size; i++)
    {
        struct HashNode *node = hashTable->buckets[i];
        while (node != NULL)
        {
            struct HashNode *temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(hashTable->buckets);
    free(hashTable);
}

int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    struct HashTable *hashTable = createHashTable(numsSize); // 创建哈希表
    for (int i = 0; i < numsSize; i++)                       // 遍历数组
    {
        struct HashNode *node = searchNode(hashTable, target - nums[i]); // 在哈希表中查找是否存在target - nums[i]
        if (node != NULL)
        {
            int *result = (int *)malloc(2 * sizeof(int));
            result[0] = node->value;
            result[1] = i;
            *returnSize = 2;
            freeHashTable(hashTable);
            return result;
        }
        insertNode(hashTable, nums[i], i);
    }
    freeHashTable(hashTable);
    *returnSize = 0;
    return NULL;
}

int main(void)
{
    int nums[] = {-3, 2, 5, 9, 15, 32};
    int target = 0;
    scanf("%d", &target);
    int returnSize;
    int *result = twoSum(nums, sizeof(nums) / sizeof(nums[0]), target, &returnSize);
    if (*result == NULL)
    {
        printf("-1,-1");
    }
    else
    {
        printf("%d,%d", result[0], result[1]);
        free(result);
    }

    return 0;
}