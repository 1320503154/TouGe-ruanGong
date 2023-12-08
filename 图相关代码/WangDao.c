// 包含必要的头文件
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// 定义常量
#define MAX_VERTEX_NUM 20 // 最大顶点个数
#define INFINITY 65535    // 无穷大
// 定义数据结构
typedef char VertexType; // 顶点类型
typedef int EdgeType;    // 边上的权值类型
typedef struct
{
    VertexType vexs[MAX_VERTEX_NUM];               // 顶点表
    EdgeType arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 邻接矩阵
    int vexnum, arcnum;                            // 图的当前顶点数和弧数
} Graph;
// 定义函数
bool visited[MAX_VERTEX_NUM]; // 访问标记数组
int FirstNeighbor(Graph G, int v)
{
    // 返回顶点v的第一个邻接顶点的序号
    for (int j = 0; j < G.vexnum; ++j)
    {
        if (G.arcs[v][j].adj == 1)
        {
            return j;
        }
    }
    return -1;
}
int NextNeighbor(Graph G, int v, int w)
{
    // 返回顶点v的相对于w的下一个邻接顶点的序号
    for (int j = w + 1; j < G.vexnum; ++j)
    {
        if (G.arcs[v][j].adj == 1)
        {
            return j;
        }
    }
    return -1;
}
void DFS(Graph G, int v)
{
    // 从第v个顶点出发递归地深度优先遍历图G
    visited[v] = true;
    printf("%c ", G.vexs[v]);
    for (int w = FirstNeighbor(G, v); w >= 0; w = NextNeighbor(G, v, w))
    {
        if (!visited[w])
        {
            DFS(G, w);
        }
    }
}
void DFSTraverse(Graph G)
{
    // 对图G进行深度优先遍历
    for (int v = 0; v < G.vexnum; ++v)
    {
        visited[v] = false;
    }
    for (int v = 0; v < G.vexnum; ++v)
    {
        if (!visited[v])
        {
            DFS(G, v);
        }
    }
}