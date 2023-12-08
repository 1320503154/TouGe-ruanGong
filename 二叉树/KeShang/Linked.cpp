// #include <iostream>
// using namespace std;

// typedef char DataType;

// // 二叉树数据结构
// struct node
// {
//     DataType info;                // 存放结点数据
//     struct node *lchild, *rchild; // 指向左右孩子的指针
// };

// typedef struct node *BiTree; // 本质还是一个节点

// /*创建二叉树
//   函数名：createBiTree
//   参数：无
//   返回值：二叉树根结点指针
//   */
// BiTree createBiTree(void)
// {
//     // 请在此处填写代码， 完成二叉树和创建，返回值是二叉树的根结点指针
//     /********** Begin **********/
//     char ch;
//     BiTree T = NULL;
//     cin >> ch;
//     if (ch == '#') // 终止条件
//         return T;
//     else
//     {
//         T = new struct node;
//         T->info = ch;
//         T->lchild = createBiTree();
//         T->rchild = createBiTree();
//     }
//     /********** End *********/
// }

// void visit(BiTree T) // 输出结点T的数据
// {
//     cout << T->info;
// }

// void inOrder(BiTree root)
// {
//     if (root == NULL)
//         return;
//     inOrder(root->lchild);
//     visit(root);
//     inOrder(root->rchild);
// }

// int main(void)
// {
//     BiTree root = createBiTree();
//     inOrder(root);
// }
// #include <iostream>
// using namespace std;

// typedef char DataType;

// // 二叉树数据结构
// struct node
// {
//     DataType info;                // 存放结点数据
//     struct node *lchild, *rchild; // 指向左右孩子的指针
// };

// typedef struct node *BiTree;

// /*创建二叉树
//   函数名：createBiTree
//   参数：无
//   返回值：二叉树根结点指针
//   */
// BiTree createBiTree(void)
// {
//     char ch;
//     BiTree root;
//     cin >> ch;
//     if (ch == '#')
//         root = NULL;
//     else
//     {
//         root = new struct node;
//         root->info = ch;
//         root->lchild = createBiTree();
//         root->rchild = createBiTree();
//     }
//     return root;
// }

// void visit(BiTree T)
// {
//     cout << T->info;
// }

// int countLeaf(BiTree root)
// {
//     // 请在此处填写代码， 计算二叉树中树叶的个数
//     /********** Begin **********/
//     // 递归解决,写逻辑即可,树叶的左孩子和右孩子都是空

//     int count = 0;

//     if (root == NULL)
//     {
//         return 0;
//     }
//     else if ((root->lchild == NULL) && (root->rchild == NULL))
//     {
//         // 找到叶子节点,count++
//         count++;
//         return count;
//     }
//     else
//     { // 非叶子节点
//         count = countLeaf(root->lchild) + countLeaf(root->rchild);
//         return count;
//     }

//     /********** End **********/
// }

// int main(void)
// {
//     BiTree root = createBiTree();
//     cout << countLeaf(root);
// }
#include <stdio.h>
int main()
{
    short si = -4321; // short is 2 bytes => 16bits :1110 1111 0001 1111.
    // unsigned is ignore the 1, 1 have value,rather than represent sign.
    unsigned short usi = si;
    printf("%u", usi);
}