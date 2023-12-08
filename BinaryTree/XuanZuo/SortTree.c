#include <stdio.h>
#include <stdlib.h>
// 数据结构定义
struct node
{
    int data;
    struct node *lchild, *rchild;
};

typedef struct node *pTree;
/*第一关*/

/*1.创建一个二叉树结点,值为element*/
pTree createTreeNode(int element)
{
    pTree treeNode = (pTree)malloc(sizeof(struct node));
    treeNode->data = element;
    treeNode->lchild = NULL;
    treeNode->rchild = NULL;
    return treeNode;
}

/*2.在二叉排序树中插入一个数据元素,若二叉树为空，则新建根节点*/
pTree insertData(int x, pTree T)
{
    if (T == NULL) // 边界条件处理
    {
        pTree newNode = createTreeNode(x);
        return newNode;
    }

    if (x < T->data)
    {
        T->lchild = insertData(x, T->lchild); // 插入到左侧节点
    }
    else if (x > T->data)
    {
        T->rchild = insertData(x, T->rchild); // 插入到右侧节点
    }

    return T;
}

/*3.先序遍历和中序遍历函数*/
void preOrder(pTree T)
{
    if (T == NULL)
    {
        return;
    }
    printf("%d ", T->data);
    preOrder(T->lchild);
    preOrder(T->rchild);
}
void inOrder(pTree T)
{
    if (T == NULL)
    {
        return;
    }
    inOrder(T->lchild);
    printf("%d ", T->data);
    inOrder(T->rchild);
}

/*第二关*/
//          8
//        /   \
//       4     12
//      / \    / \
//     2   6  10  14
//    / \  / \ 
//   1  3 5   7
/* 1.在二叉排序树T中查找最小值，返回该结点 */
pTree findMin(pTree T)
{
    if (T == NULL)
    {
        return NULL; // 树为空，返回空指针
    }

    while (T->lchild != NULL)
    {
        T = T->lchild;
    }

    return T;
}

/* 2.在二叉排序树T中查找最大值，返回该结点 */
pTree findMax(pTree T)
{
    if (T == NULL)
    {
        return NULL; // 树为空，返回空指针
    }

    while (T->rchild != NULL)
    {
        T = T->rchild;
    }

    return T;
}
/* 3.在二叉排序树T中查找指定数据元素，若未找到，则返回NULL */
pTree findData(pTree T, int element)
{
    if (T == NULL || T->data == element)
    {
        return T; // 若节点为空或找到了指定元素，直接返回
    }
    else if (element < T->data)
    {
        return findData(T->lchild, element); // 递归在左子树中查找
    }
    else
    {
        // element > T->data 的 case
        return findData(T->rchild, element); // 递归在右子树中查找
    }
}

/*第三关*/
//          8
//        /   \
//       4     12
//      / \    / \
//     2   6  10  14
//    / \  / \ 
//   1  3 5   7
/*在二叉排序树T中删除指定元素的结点,若删除成功则返回该结点，否则返回NULL*/
pTree deleteData(pTree T, int element)
{
    // 如果树为空，返回NULL。
    if (T == NULL)
    {
        return NULL;
    }
    // 如果要删除的元素小于当前节点的值，则继续在左子树中递归删除。
    if (element < T->data)
    {
        T->lchild = deleteData(T->lchild, element);
    }
    // 如果要删除的元素大于当前节点的值，则继续在右子树中递归删除。
    else if (element > T->data)
    {
        T->rchild = deleteData(T->rchild, element);
    }
    // 如果要删除的元素等于当前节点的值：
    else
    { // element == T->data
        // 如果当前节点是叶节点（没有子节点），直接删除，并将该节点置为NULL。
        if (T->lchild == NULL && T->rchild == NULL)
        {
            free(T);
            T = NULL;
        }
        // 如果当前节点只有一个子节点，则用该子节点替换当前节点。
        else if (T->lchild == NULL)
        {
            pTree temp = T;
            T = T->rchild;
            free(temp);
        }
        else if (T->rchild == NULL)
        {
            pTree temp = T;
            T = T->lchild;
            free(temp);
        }
        // 如果当前节点有两个子节点，则需要找到当前节点的后继节点（右子树中最小的节点）或前驱节点（左子树中最大的节点）来替换当前节点，然后递归删除替换节点。
        else
        {
            pTree temp = findMin(T->rchild);               // 找到右子树中最小的节点
            T->data = temp->data;                          // 要删除的节点的值替换为右子树中最小的节点的值
            T->rchild = deleteData(T->rchild, temp->data); // 递归删除右子树中最小的节点,就是之前找到的temp节点
        }
    }
}
