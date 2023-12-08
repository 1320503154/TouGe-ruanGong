#include <stdio.h>
#include <stdlib.h>
typedef struct treeNode
{
    int l, r, weight, parent, top;
    int *element;
} node, *Node;

Node printTree(int n)
{
    Node t = (Node)malloc((2 * n + 1) * sizeof(node));
    int i = 0;
    for (i = 0; i < n; i++)
    {
        printf("input weight: ");
        scanf("%d", &t[i].weight);
        t[i].l = -1;
        t[i].r = -1;
        t[i].parent = -1;
        t[i].top = -1;
        t[i].element = (int *)malloc(n * sizeof(int));
    }

    while (i < 2 * n + 1)
    {
        t[i].weight = 0;
        t[i].l = -1;
        t[i].r = -1;
        t[i].parent = -1;
        t[i].top = -1;
        t[i].element = (int *)malloc(n * sizeof(int));
        i++;
    }

    return t;
}

int *findMin(Node tree)
{
    int i = 1;
    int *min = (int *)malloc(2 * sizeof(int));

    for (int i = 0;; i++)
    {
        if (tree[i].parent == -1)
        {
            min[0] = i;
            break;
            i++;
        }
        else if (!tree[i].weight)
            break;
    }

    int minweight = tree[min[0]].weight;
    int maxweight = tree[min[0]].weight;
    while (tree[i].weight)
    {
        if (tree[i].parent != -1)
        {
            i++;
            continue;
        }
        if (tree[i].weight <= minweight)
        {
            minweight = tree[i].weight;
            min[0] = i;
        }
        else if (tree[i].weight >= maxweight)
            maxweight = tree[i].weight;
        i++;
    }
    minweight = maxweight;
    i = 0;
    while (tree[i].weight)
    {
        if (tree[i].parent != -1)
        {
            i++;
            continue;
        }
        if (tree[i].weight <= minweight && i != min[0])
        {
            minweight = tree[i].weight;
            min[1] = i;
        }
        i++;
    }
    printf("%d%d\n", min[0], min[1]);
    return min;
}

void printHuffman(Node t, int m)
{
    if (m == -1)
        return;
    printf("%d\t", t[m].weight);
    printHuffman(t, t[m].l);
    printHuffman(t, t[m].r);
}

int main()
{
    int n = 0;
    printf("input n:");
    scanf("%d", &n);
    Node tree = printTree(n);
    int m = n;
    int *min = (int *)malloc(2 * sizeof(int));
    while (m != 2 * n - 1)
    {
        min = findMin(tree);
        tree[m].weight = tree[min[0]].weight + tree[min[1]].weight;
        tree[m].l = min[0];
        tree[m].r = min[1];
        tree[min[0]].parent = m;
        tree[min[1]].parent = m;
        m++;
    }

    printHuffman(tree, m - 1);

    int i = 0;
    while (tree[0].element[i])
    {
        printf("%d", tree[0].element[i]);
        i++;
    }
}