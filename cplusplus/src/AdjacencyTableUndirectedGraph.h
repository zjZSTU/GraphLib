//
// Created by zj on 19-10-24.
//

#ifndef CPLUSPLUS_ADJACENCYTABLEUNDIRECTEDGRAPH_H
#define CPLUSPLUS_ADJACENCYTABLEUNDIRECTEDGRAPH_H

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
 * 2. 深度/广度优先便利
 * 3. 最小生成树创建
 */
class AdjacencyTableUndirectedGraph {

public:
    void CreateGraphAdjList(GraphAdjList *G);

    void PrintGraphAdjList(GraphAdjList G);

    int *DFSTraverse(GraphAdjList G);

    int *BFSTraverse(GraphAdjList G);

    void MiniSpanTree_Prim(GraphAdjList G);

    void MiniSpanTree_Kruskal(GraphAdjList G);

private:
    void DFS(GraphAdjList G, int up, int *index);

    static bool less_second(Edge x, Edge y);

    bool visited[MAXVEX];
    int ordered[MAXVEX];
};


#endif //CPLUSPLUS_ADJACENCYTABLEUNDIRECTEDGRAPH_H
