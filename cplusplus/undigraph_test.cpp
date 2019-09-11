//
// Created by zj on 19-8-21.
//

#include "undigraph_test.h"

void UndigraphTest::MGraphUse(EdgeType (*arcs)[9]) {
    MGraph G;
    G.numVertexes = 9;
    G.numEdges = 15;
    G.vexs = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"};
    int i = 0;
    for (auto &ary:G.arcs) {
        memcpy(&ary, arcs[i], sizeof(EdgeType) * 9);
        i++;
    }

    Undigraph graph;
//    graph.CreateMGraph(&G);
    graph.PrintMGraph(G);

    cout << "邻接矩阵 - 深度优先遍历" << endl;
    int *idxes = graph.DFSTraverse(G);
    for (i = 0; i < G.numVertexes; i++) {
        cout << G.vexs[idxes[i]] << " ";
    }
    cout << endl;

    cout << "邻接矩阵 - 广度优先遍历" << endl;
    idxes = graph.BFSTraverse(G);
    for (i = 0; i < G.numVertexes; i++) {
        cout << G.vexs[idxes[i]] << " ";
    }
    cout << endl;

    cout << "邻接矩阵 - 最小生成树 - Prim" << endl;
    graph.MiniSpanTree_Prim(G);
    cout << endl;

    cout << "邻接矩阵 - 最小生成树 - Kruskal" << endl;
    graph.MiniSpanTree_Kruskal(G);
    cout << endl;
}

void UndigraphTest::GraphAdjListUse(array<VertexType, 9> vertexes, EdgeType (*arcs)[9]) {
    GraphAdjList G;
    G.numVertexes = 9;
    G.numEdges = 15;

    int i, j;
    EdgeNode *edgeNode;
    for (i = 0; i < 9; i++) {
        VertextNode vertextNode;
        vertextNode.data = vertexes[i];
        vertextNode.firstEdge = nullptr;
        for (j = 0; j < 9; j++) {
            if (i != j and arcs[i][j] != GINFINITY) {
                edgeNode = (EdgeNode *) malloc(sizeof(EdgeNode));
                edgeNode->adjvex = j;
                edgeNode->weight = arcs[i][j];
                edgeNode->next = vertextNode.firstEdge;
                vertextNode.firstEdge = edgeNode;
            }
        }
        G.adjList[i] = vertextNode;
    }

    Undigraph graph;
//    graph.CreateGraphAdjList(&G);
    graph.PrintGraphAdjList(G);

    cout << "邻接表 - 深度优先遍历" << endl;
    int *idxes = graph.DFSTraverse(G);
    for (i = 0; i < G.numVertexes; i++) {
        cout << G.adjList[idxes[i]].data << " ";
    }
    cout << endl;

    cout << "邻接表 - 广度优先遍历" << endl;
    idxes = graph.BFSTraverse(G);
    for (i = 0; i < G.numVertexes; i++) {
        cout << G.adjList[idxes[i]].data << " ";
    }
    cout << endl;

    cout << "邻接表 - 最小生成树 - Prim" << endl;
    graph.MiniSpanTree_Prim(G);
    cout << endl;

    cout << "邻接表 - 最小生成树 - Kruskal" << endl;
    graph.MiniSpanTree_Kruskal(G);
    cout << endl;
}