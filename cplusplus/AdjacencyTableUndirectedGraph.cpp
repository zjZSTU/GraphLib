//
// Created by zj on 19-10-24.
//

#include "AdjacencyTableUndirectedGraph.h"

void AdjacencyTableUndirectedGraph::CreateGraphAdjList(GraphAdjList *G) {
    int i, j, k, w;
    EdgeNode *e;

    cout << "输入顶点数: ";
    cin >> G->numVertexes;
    cout << "输入边集数: ";
    cin >> G->numEdges;

    cout << "输入顶点信息：" << endl;
    for (i = 0; i < G->numVertexes; i++) {
        cin >> G->adjList[i].data;
        G->adjList[i].firstEdge = nullptr;
    }

    cout << "输入边信息" << endl;
    for (k = 0; k < G->numEdges; k++) {
        cout << "输入第" << k << "条边的上标、下标和权值: ";
        cin >> i >> j >> w;
        // 申请内存空间
        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        e->adjvex = j;
        e->weight = w;
        // 头插法
        e->next = G->adjList[i].firstEdge;
        G->adjList[i].firstEdge = e;

        // 无向图的边表对称
        e = (EdgeNode *) malloc(sizeof(EdgeNode));
        e->adjvex = i;
        e->weight = w;
        // 头插法
        e->next = G->adjList[j].firstEdge;
        G->adjList[j].firstEdge = e;
    }
}

void AdjacencyTableUndirectedGraph::PrintGraphAdjList(GraphAdjList G) {
    cout << "顶点数和边数: ";
    cout << G.numVertexes << " " << G.numEdges << endl;
    cout << "顶点信息: " << endl;
    for (int i = 0; i < G.numVertexes; i++) {
        cout << " " << G.adjList[i].data;
    }
    cout << endl;

    cout << "边集信息: " << endl;
    EdgeNode *edgeNode;
    for (int i = 0; i < G.numVertexes; i++) {
        edgeNode = G.adjList[i].firstEdge;
        while (edgeNode != nullptr) {
            printf("(%d, %d) %d ", i, edgeNode->adjvex, edgeNode->weight);
            edgeNode = edgeNode->next;
        }
        cout << endl;
    }
    cout << endl;
}

int *AdjacencyTableUndirectedGraph::DFSTraverse(GraphAdjList G) {
    int i;
    for (i = 0; i < G.numVertexes; i++) {
        visited[i] = false;
    }

    int index = 0;
    for (i = 0; i < G.numVertexes; i++) {
        if (!visited[i]) {
            DFS(G, i, &index);
        }
    }

    return ordered;
}

void AdjacencyTableUndirectedGraph::DFS(GraphAdjList G, int up, int *index) {
    // 访问顶点up
    visited[up] = true;
    ordered[*index] = up;
    *index += 1;

    EdgeNode *e = G.adjList[up].firstEdge;
    while (e != nullptr) {
        if (!visited[e->adjvex]) {
            DFS(G, e->adjvex, index);
        }
        e = e->next;
    }
}

int *AdjacencyTableUndirectedGraph::BFSTraverse(GraphAdjList G) {
    int i, k;
    EdgeNode *e;
    int index = 0;
    std::queue<int> q;
    for (i = 0; i < G.numVertexes; i++) {
        visited[i] = false;
    }

    for (i = 0; i < G.numVertexes; i++) {
        if (!visited[i]) {
            // 访问顶点i
            visited[i] = true;
            ordered[index] = i;
            index++;

            q.push(i);
            while (!q.empty()) {
                // 出队
                k = q.front();
                q.pop();

                e = G.adjList[k].firstEdge;
                while (e != nullptr) {
                    if (!visited[e->adjvex]) {
                        // 访问顶点adjvex
                        visited[e->adjvex] = true;
                        ordered[index] = e->adjvex;
                        index++;

                        q.push(e->adjvex);
                    }
                    e = e->next;
                }
            }
        }
    }

    return ordered;
}

void AdjacencyTableUndirectedGraph::MiniSpanTree_Prim(GraphAdjList G) {
    int min, i, j, k;
    EdgeNode *e;
    std::array<int, MAXVEX> adjvex = {};
    std::array<int, MAXVEX> lowcost = {};

    // 初始化
    for (i = 0; i < G.numVertexes; i++) {
        lowcost[i] = GINFINITY;
        adjvex[i] = 0;
    }

    // 默认添加顶点0到MST
    // adjvex赋值为边的另一个顶点值， 如果顶点已在MST中，指定下标赋值为-1
    adjvex[0] = 0;
    lowcost[0] = -1;
    e = G.adjList[0].firstEdge;
    while (e != nullptr) {
        lowcost[e->adjvex] = e->weight;
        adjvex[e->adjvex] = 0;

        e = e->next;
    }

//    int index = 0;
    // 遍历n-1轮，得到另外的顶点
    for (i = 1; i < G.numVertexes; i++) {
        min = GINFINITY;
        // 遍历n-1次，搜索最小权值边
        j = 1, k = 0;
        while (j < G.numVertexes) {
            if (lowcost[j] != -1 and lowcost[j] < min) {
                min = lowcost[j];
                k = j;
            }
            j++;
        }

        // 输出最小权值边
        printf("(%d, %d)", adjvex[k], k);
//        arrs[index][0] = adjvex[k];
//        arrs[index][1] = k;
//        index++;
        // 顶点k已加入MST，lowcost赋值为-1
        lowcost[k] = -1;

        // 比较顶点k的边集和MST的最小权值边集
        e = G.adjList[k].firstEdge;
        while (e != nullptr) {
            if (lowcost[e->adjvex] != -1 and e->weight < lowcost[e->adjvex]) {
                lowcost[e->adjvex] = e->weight;
                adjvex[e->adjvex] = k;
            }

            e = e->next;
        }
    }
}

void AdjacencyTableUndirectedGraph::MiniSpanTree_Kruskal(GraphAdjList G) {
    int i, j, k, n, m;
    EdgeNode *e;
    std::array<Edge, MAXEDGE> edges = {};
    // 保存最小生成树，数组下标表示一个顶点，赋值表示另一个顶点
    int parent[MAXVEX];

    // 将边集赋值给edges
    k = 0;
    for (i = 0; i < G.numVertexes; i++) {
        e = G.adjList[i].firstEdge;

        while (e != nullptr) {
            Edge edge;
            edge.begin = i;
            edge.end = e->adjvex;
            edge.weight = e->weight;

            edges[k] = edge;
            k++;

            e = e->next;
        }
    }
    // 按权值升序排序
    std::sort(edges.begin(), edges.begin() + G.numEdges, less_second);
//    for (i = 0; i < G.numEdges; i++) {
//        printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
//    }

    // 初始化
    for (i = 0; i < G.numVertexes; i++) {
        parent[i] = 0;
    }
    // 升序遍历
    for (i = 0; i < G.numEdges; i++) {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        // 判断两个分量是否同属一个
        if (n != m) {
            parent[n] = m;
            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
        }
    }
}

bool AdjacencyTableUndirectedGraph::less_second(Edge x, Edge y) {
    return x.weight < y.weight;
}

int AdjacencyTableUndirectedGraph::Find(int *parent, int f) {
    // 遍历分量
    while (parent[f] > 0) {
        f = parent[f];
    }

    return f;
}