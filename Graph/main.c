#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 100 // 定义队列的最大大小
#define N 6          // 顶点数
// 邻接矩阵数据结构
typedef struct
{
    int vcount;     // 顶点数
    int type;       // 0 无向图，1 有向图
    char vexs[N];   // 顶点信息
    int arcs[N][N]; // 关系矩阵
} GraphMatrix;

// 邻接表数据结构
struct EdgeNode // 边表中的结点
{
    int endvex;                // 相邻顶点在顶点表中下标
    int weight;                // 边的权
    struct EdgeNode *nextedge; // 链字段
};
typedef struct EdgeNode *EdgeList;

typedef struct
{
    char vertex;       // 记录顶点信息
    int degree;        // 用于记录顶点的入度，在拓扑排序时需使用
    EdgeList edgelist; // 指向边表的指针
} VexNode;
typedef struct
{
    VexNode vexs[N]; // N个顶点
    int type;        // 0 无向图，1 有向图
    int vcount;      // 顶点数
} GraphList;

/*第一关 完成图初始化
 */
void printGraph(GraphMatrix *G)
{ // 本函数输出图的邻接矩阵
    int i, j;
    for (i = 0; i < G->vcount; i++)
    {
        //  printf("%c ",G->vexs[i]);
        for (j = 0; j < G->vcount; j++)
            printf("%d ", G->arcs[i][j]);
        printf("\n");
    }
}

/*第一关 完成图初始化-邻接矩阵
 */
GraphMatrix *initGraphMatrix()
{
    /*第一行输入图的类型、图的顶点数和边数，第二行输入各条边的两顶点的编号，按顶点编号从小到大的顺序输入。
  输出邻接矩阵，不需要考虑输入的数字非法情况，不输入顶点的信息*/
    // 测试输入：
    // 0 5 6
    // 0 1 0 3 1 2 1 4 2 3 2 4
    GraphMatrix *GM = (GraphMatrix *)malloc(sizeof(GraphMatrix));
    int edges = 0;
    int v1, v2 = 0;
    scanf("%d %d %d", &(GM->type), &(GM->vcount), &edges);
    // 初始化关系矩阵
    for (int i = 0; i < GM->vcount; i++)
    {
        for (int j = 0; j < GM->vcount; j++)
        {
            GM->arcs[i][j] = 0;
        }
    }
    // 构建关系矩阵
    for (int k = 0; k < edges; k++) // 循环(边数次)
    {
        scanf("%d %d", &v1, &v2);
        GM->arcs[v1][v2] = 1;
        // 如果是无向图,对称位置也为1;
        if (GM->type == 0)
        {
            GM->arcs[v2][v1] = 1;
        }
    }
    return GM;
}
void printGraphMatrix(GraphMatrix *G)
{
    for (int i = 0; i < G->vcount; i++)
    {
        for (int j = 0; j < G->vcount; j++)
        {
            printf("%d", G->arcs[i][j]);
        }
        printf("\n");
    }
}
/*第二关 完成图初始化-邻接表,并完成输出图的邻接表函数
 */
GraphList *initGraphList()
{
    /*第一行输入图的类型、图的顶点数和边数，第二行输入各条边的两顶点的编号，按顶点编号从小到大的顺序输入。
  输出邻接表。不需考虑输入的数字非法情况，输入顶点的信息*/
    // 测试输入：
    // 0 4 5
    // 0123
    // 0 1 0 2 0 3 1 2 1 3
    // —— 预期输出 ——
    // 0->3->2->1
    // 1->3->2->0
    // 2->1->0
    // 3->1->0
    GraphList *map = (GraphList *)malloc(sizeof(GraphList));
    int n; // n为边数
    scanf("%d%d%d", &map->type, &map->vcount, &n);

    char c[map->vcount + 1]; // 创建字符数组
    scanf("%s", c);          // 输入字符串
    // 初始化节点信息
    // 初始化图的顶点数据
    for (int i = 0; i < map->vcount; i++)
    {
        map->vexs[i].vertex = c[i];
        map->vexs[i].degree = 0;
    }

    // 输入顶点数据

    int v1, v2, m; // m代表权重

    int i = 0;

    // 初始化图的边链表
    for (int i = 0; i < map->vcount; i++)
    {
        map->vexs[i].edgelist = NULL;
    }

    // 添加边的信息
    while (i < n) // n为边数
    {

        // scanf("%d%d", &v1, &v2);                                // 第一个节点值和第二个节点值
        scanf("%d%d%d", &v1, &v2, &m);                          // 如果带权则换该scanf;
        EdgeList s = (EdgeList)malloc(sizeof(struct EdgeNode)); // 新的边表节点
        // s是新的边表中的节点
        s->endvex = v2;
        s->nextedge = map->vexs[v1].edgelist; // 前插法,s->endvex=3,s->nextEdge=1
        map->vexs[v1].edgelist = s;           // v1.nextEdge=s,此处链接:0->3->1
        // 之前链接:0->1.
        // 从头哥输入来看,即为0->3->1;1->4->2;2->4->3

        if (map->type == 0) // 如果是无向图,对称一下
        {
            EdgeList s1 = (EdgeList)malloc(sizeof(struct EdgeNode));
            s1->endvex = v1; // 从v2对应到v1
            s1->nextedge = map->vexs[v2].edgelist;
            map->vexs[v2].edgelist = s1;
            s->weight = s1->weight = m; // 权重都一样
        }
        else
        {
            map->vexs[v2].degree++; // 不是无向图则v2的入度++,因为链接表示出度
        }
        i++;
    }
    return map;
}

void printGraphLit(GraphList *G)
{
    /*输出邻接表，输出格式：顶点->邻接顶点编号->...*/
    for (int i = 0; i < G->vcount; i++)
    {
        EdgeList p = G->vexs[i].edgelist; // 取到对应节点的边表
        printf("%c ", G->vexs[i].vertex); // 输出节点信息
        while (p != NULL)
        {
            printf("->%d", p->endvex);
            p = p->nextedge;
        }
        printf("\n");
    }
}

/*第三关 完成图的广度遍历（周游），可根据需要添加自定义函数
 */
void BFS_list(GraphList *G)
{
    bool visited[N];                         // 记录顶点是否被访问过
    memset(visited, false, sizeof(visited)); // 使用memset将visited数组初始化为false

    int queue[MAX_SIZE]; // 新建一个队列
    int front, rear = 0; // 定义队列的头和尾指针
    memset(queue, 0, sizeof(queue));
    for (int i = 0; i < G->vcount; i++)
    {
        if (visited[i] == false) // 如果顶点i未被访问，则进行广度遍历
        {
            visited[i] = true;                // 将当前顶点标记为已访问
            printf("%c ", G->vexs[i].vertex); // 输出当前顶点

            queue[rear] = i; // 将当前顶点入队
            rear++;
            while (front != rear) // 队列不为空时继续遍历
            {
                int cur = queue[front]; // 出队当前顶点
                front++;
                EdgeList p = G->vexs[cur].edgelist; // 取到对应节点的边表

                while (p != NULL)
                {
                    int next = p->endvex; // 获取相邻顶点的下标
                    if (visited[next] == false)
                    {                                        // 如果相邻顶点未被访问，则进行广度遍历
                        visited[next] = true;                // 将相邻顶点标记为已访问
                        printf("%c ", G->vexs[next].vertex); // 输出相邻顶点
                        queue[rear++] = next;                // 将相邻顶点入队
                    }
                    p = p->nextedge;
                }
            }
        }
    }
}

/*第四关 完成图的深度遍历（周游），可根据需要添加自定义函数
 */
// 获取第一个邻居函数,获取第二个邻居函数
//  递归辅助函数，用于深度优先搜索（DFS）
void DFSUtil(GraphList *G, int v, bool visited[])
{
    // v是当前顶点
    visited[v] = true;
    printf("%c ", G->vexs[v].vertex);
    // 获取当前顶点的边表头指针
    EdgeList p = G->vexs[v].edgelist;
    while (p != NULL)
    {
        int next = p->endvex; // 获取相邻顶点的下标
        if (!visited[next])   // 初始化visited数组都为False.
        {
            DFSUtil(G, next, visited);
        }
        p = p->nextedge;
    }
}

// 图的深度优先搜索（DFS）遍历，邻接表表示法
void DFS_list(GraphList *G)
{
    bool visited[N];                         // 记录顶点是否被访问过
    memset(visited, false, sizeof(visited)); // 使用memset将visited数组初始化为false
    for (int i = 0; i < G->vcount; i++)
    {
        if (!visited[i]) // 如果当前顶点i未被访问,就进行深度遍历
        {
            DFSUtil(G, i, visited);
        }
    }
}

/*第五关 生成图的拓扑排序，可根据需要添加自定义函数*/
// 使用队列:
typedef struct
{
    int data[MAX_SIZE]; // 存储队列中的数据
    int front, rear;    // 队列的头和尾指针
} Queue;

// 初始化队列
void InitQueue(Queue *q)
{
    q->front = q->rear = -1; // 初始化队列的头尾指针
}

// 入队操作
void Enqueue(Queue *q, int value)
{
    if ((q->rear + 1) % MAX_SIZE == q->front)
    {
        printf("Queue is full. Cannot enqueue %d.\n", value);
        return;
    }
    if (q->front == -1) // 如果队列为空，更新头指针
    {
        q->front = q->rear = 0;
    }
    else
    {
        q->rear = (q->rear + 1) % MAX_SIZE; // 更新尾指针
    }
    q->data[q->rear] = value; // 将值入队
}

// 检查队列是否为空
int isQueueEmpty(Queue *q)
{
    return (q->front == -1); // 返回头指针是否为-1，即队列是否为空
}

// 出队操作
int Dequeue(Queue *q)
{
    if (q->front == -1)
    {
        printf("Queue is empty. Cannot dequeue.\n");
        return -1; // 队列为空，返回-1表示出错
    }
    int value = q->data[q->front]; // 取出队头元素的值
    if (q->front == q->rear)       // 如果队列只有一个元素，出队后更新头尾指针
    {
        q->front = q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % MAX_SIZE; // 更新头指针
    }
    return value; // 返回出队的元素值
}

// 使用队列实现的拓扑排序函数
void Top_list(GraphList *G)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    int vcount = G->vcount;                           // 图中的顶点数
    int *print = (int *)malloc(sizeof(int) * vcount); // 存储拓扑排序的结果
    InitQueue(queue);
    for (int i = 0; i < G->vcount; i++)
    {
        if (G->vexs[i].degree == 0) // 如果入度为0,则全部入队
        {
            Enqueue(queue, i); // 入队的是顶点在顶点数组的下标
        }
    }
    int count = 0; // 记录已输出的顶点数
    while (!isQueueEmpty(queue))
    {
        int cur = Dequeue(queue);
        print[count++] = cur; // 将当前顶点放入结果数组中
        // 将所有cur指向的顶点的入度-1,并且将入度减为0的顶点入队
        EdgeList p = G->vexs[cur].edgelist;
        // 遍历该顶点指向的链表,也就是和自己有链接关系的节点
        while (p != NULL)
        {
            int endvex = p->endvex;   // 获取相邻顶点的下标
            G->vexs[endvex].degree--; // 相邻顶点的入度-1,逻辑上就是把cur不再指向相邻的节点了.
            if (G->vexs[endvex].degree == 0)
            {
                Enqueue(queue, endvex);
            }
            p = p->nextedge;
        }
    }
    for (int i = 0; i < count; i++)
    {
        printf("%c ", G->vexs[print[i]].vertex); // print数组存储节点的下标
    }
}

/*第六关 prim算法生成最小生成树
 */
int selected[N]; // 标记顶点是否被选择
int distance[N]; // 记录顶点与最小生成树之间的最小权重
int parent[N];   // 记录顶点的父节点

void Prim_list(GraphList *G)
{
    memset(distance, 0x3f, sizeof(distance)); // 初始化 distance 数组为最大值,0*3f是十六进制,十进制是1061109567

    for (int i = 0; i < G->vcount; i++)
    {
        int minVertex = -1; // 记录权重最小的顶点

        // 选择权重最小的边
        for (int j = 0; j < G->vcount; j++)
        {
            if (!selected[j] && (minVertex == -1 || distance[minVertex] > distance[j])) // 如果顶点未被选择,顶点j的权重小于顶点minVertex的权重
            {
                minVertex = j; // 更新minVertex
            }
        }

        if (i && distance[minVertex] == 0x3f3f3f3f) // 如果权重最小的顶点的权重为最大值,说明无法建树
        {
            puts("无法建树");
            return;
        }

        if (i) // 输出最小生成树的边
        {
            printf("%d %d\n", parent[minVertex], minVertex);
        }

        selected[minVertex] = 1; // 标记顶点minVertex被选择

        for (int j = 0; j < G->vcount; j++)
        {
            int edgeWeight = 0x3f3f3f3f; // 0x3f3f3f3f是十六进制,十进制是1061109567

            // 寻找顶点 minVertex 到顶点 j 的权重
            for (EdgeList p = G->vexs[minVertex].edgelist; p; p = p->nextedge) // 遍历顶点minVertex的边表
            {
                if (p->endvex == j) // 如果顶点minVertex和顶点j有链接关系
                {
                    edgeWeight = p->weight; // 更新权重
                    break;
                }
            }

            if (distance[j] > edgeWeight) // 如果顶点j的权重大于顶点minVertex到顶点j的权重
            {
                distance[j] = edgeWeight; // 更新顶点j的权重
                parent[j] = minVertex;    // 更新顶点j的父节点
            }
        }
    }
}
