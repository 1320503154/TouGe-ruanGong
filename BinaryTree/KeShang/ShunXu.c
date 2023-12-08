#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// In math.h,其中floor()函数为向下（左）取整，ceil()函数为向上（右）取整
struct seqTree
{
    int size;
    char *arr;
};
typedef struct seqTree *Tree;
/*辅助功能：逐个输出顺序表的元素，元素之间以空格为界*/
void printTree(struct seqTree *T)
{
    for (int i = 0; i < T->size; i++)
        printf("%c ", T->arr[i]);
}
int isNULL(Tree T)
{
    if (T == NULL || T->size == 0 || T->arr[0] == ' ')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
/*第一关*/
struct seqTree *createSeqTree()
{
    char arr[255];
    gets(arr);
    int len = strlen(arr);

    struct seqTree *tree = (struct seqTree *)malloc(sizeof(struct seqTree));
    tree->size = len;
    tree->arr = (char *)malloc(sizeof(char) * (len + 1));
    for (int i = 0; i <= len; i++)
        tree->arr[i] = arr[i];
    return tree;
}
/*第二关，返回二叉树的根结点的值，若二叉树为空，则返回#*/
char root(struct seqTree *T)
{
    if (isNULL(T))
    {
        return '#';
    }
    return T->arr[0];
}

/*第二关，求二叉树T中指定结点ch的双亲结点，返回值是双亲结点的下标，若双亲不存在，则返回-1*/
int parent(struct seqTree *T, char ch)
{
    for (int i = 0; i < T->size; i++)
    {
        if (ch == T->arr[i]) // 找到节点
        {
            int parentIndex = (i - 1) >> 1;
            if (T->arr[parentIndex] == ' ') // 父节点为空格,返回-1;
                return -1;
            return parentIndex;
        }
    }
    return -1;
}

/*第二关，求二叉树T中指定结点ch的左孩子的下标，若左孩子不存在，则返回-1*/
int leftChild(struct seqTree *T, char ch)
{
    for (int i = 0; i < T->size; i++) // 遍历查找
    {
        if (ch == T->arr[i]) // 找到了
        {
            int leftChildIndex = i * 2 + 1;                                // 左孩子为2i + 1.
            if (leftChildIndex > T->size || T->arr[leftChildIndex] == ' ') // 如果左孩子超出size,或者左孩子为空格
                return -1;
            return leftChildIndex;
        }
    }
    return -1;
}

/*第二关，求二叉树T中指定结点ch的右孩子的下标，若左孩子不存在，则返回-1*/
int rightChild(struct seqTree *T, char ch)
{
    for (int i = 0; i < T->size; i++)
    {
        if (ch == T->arr[i])
        {
            int rightChildIndex = i * 2 + 2;
            if (rightChildIndex > T->size || T->arr[rightChildIndex] == ' ')
            {
                return -1;
            }
            return rightChildIndex;
        }
    }
}

/*第三关：层序遍历二叉树，输出遍历得到的结点，结点之间不需要空格*/
void levelOrder(struct seqTree *T)
{
    // 顺序存储的二叉树的层序遍历就是直接输出数组的原本的值.
    for (int i = 0; i < T->size; i++)
    {
        if (T->arr[i] != ' ')
        {
            printf("%c", T->arr[i]);
        }
    }
}

/*第四关：先序遍历二叉树，输出遍历得到的结点，结点之间不需要空格*/
void preOrder(struct seqTree *T, char node)
{
    int leftChildIndex = leftChild(T, node);
    int rightChildIndex = rightChild(T, node);
    if (node != '#') // 根节点为空,则返回#,此处检测
        printf("%c", node);
    if (leftChildIndex != -1) // 左孩子不为空,则遍历左子树
        preOrder(T, leftChildIndex);
    if (rightChildIndex != -1)
        preOrder(T, rightChildIndex); // 右孩子不为空,则遍历右子树
}

int main(void)
{
    struct seqTree *T = createSeqTree();
    // printTree(T);            // 测评第一关时，把本行代码放开
    // printf("%c\n", root(T)); //  测评第二关时，把该代码块放开
    // printf("%d\n", leftChild(T, 'A'));
    // printf("%d\n", rightChild(T, 'A'));
    // printf("%d\n", parent(T, 'A'));

    levelOrder(T); // 测评第三关时，把本行代码放开
    // preOrder(T,T->arr[0]);  // 测评第四关时，把本行代码放开
}
