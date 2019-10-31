//
// Created by zj on 19-10-24.
//

#ifndef CPLUSPLUS_ADJACENCYMATRIXUNDIRECTEDGRAPH_H
#define CPLUSPLUS_ADJACENCYMATRIXUNDIRECTEDGRAPH_H

#include <iomanip>
#include <algorithm>
#include <iostream>
#include <queue>
#include "common_iostream.h"
#include "graph.h"
#include "DisjointSet.h"

/**
 * 无向图，实现操作如下：
 * 1. 图数据载入
 * 2. 深度优先遍历
 * 3. 广度优先遍历
 * 3. 最小生成树创建（prim/kruskal）
 */
class AdjacencyMatrixUndirectedGraph {

public:
    void CreateMGraph(MGraph *G);

    void PrintMGraph(MGraph G);

    int *DFSTraverse(MGraph G);

    int *BFSTraverse(MGraph G);

    void MiniSpanTree_Prim(MGraph G);

    void MiniSpanTree_Kruskal(MGraph G);

private:

    void DFS(MGraph G, int up, int *index);

    static bool less_second(Edge x, Edge y);

    bool visited[MAXVEX];
    int ordered[MAXVEX];
};


#endif //CPLUSPLUS_ADJACENCYMATRIXUNDIRECTEDGRAPH_H
