
#include "../../src/graph.h"
#include "../../src/AdjacencyTableUndirectedGraph.h"
#include "../../src/AdjacencyMatrixUndirectedGraph.h"
#include <memory>
#include <cstring>

const int NUM = 9;

EdgeType arcs[NUM][NUM] = {
        {0,         10,        GINFINITY, GINFINITY, GINFINITY, 11,        GINFINITY, GINFINITY, GINFINITY},
        {10,        0,         18,        GINFINITY, GINFINITY, GINFINITY, 16,        GINFINITY, 12},
        {GINFINITY, 18,        0,         22,        GINFINITY, GINFINITY, GINFINITY, GINFINITY, 8},
        {GINFINITY, GINFINITY, 22,        0,         20,        GINFINITY, 24,        16,        21},
        {GINFINITY, GINFINITY, GINFINITY, 20,        0,         26,        GINFINITY, 7,         GINFINITY},
        {11,        GINFINITY, GINFINITY, GINFINITY, 26,        0,         17,        GINFINITY, GINFINITY},
        {GINFINITY, 16,        GINFINITY, 24,        GINFINITY, 17,        0,         19,        GINFINITY},
        {GINFINITY, GINFINITY, GINFINITY, 16,        7,         GINFINITY, 19,        0,         GINFINITY},
        {GINFINITY, 12,        8,         21,        GINFINITY, GINFINITY, GINFINITY, GINFINITY, 0}
};

void AdjacencyTableTest(std::array<VertexType, NUM> &vertexes, EdgeType (*arcs)[NUM]) {
    GraphAdjList G;
    G.numVertexes = NUM;
    G.numEdges = 15;

    int i, j;
    EdgeNode *edgeNode;
    for (i = 0; i < NUM; i++) {
        VertextNode vertextNode;
        vertextNode.data = vertexes[i];
        vertextNode.firstEdge = nullptr;
        for (j = 0; j < NUM; j++) {
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

    AdjacencyTableUndirectedGraph graph{};
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

void AdjacencyMatrixTest(std::array<VertexType, NUM> &vertexes, EdgeType (*arcs)[NUM]) {
    MGraph G;
    G.numVertexes = NUM;
    G.numEdges = 15;
    for (int i = 0; i < NUM; i++) {
        G.vexs[i] = vertexes[i];
    }
    int i = 0;
    for (auto &ary:G.arcs) {
        std::memcpy(&ary, arcs[i], sizeof(EdgeType) * NUM);
        i++;
    }

    AdjacencyMatrixUndirectedGraph graph{};
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

    cout << "邻接表 - 最小生成树 - Prim" << endl;
    graph.MiniSpanTree_Prim(G);
    cout << endl;

    cout << "邻接矩阵 - 最小生成树 - Kruskal" << endl;
    graph.MiniSpanTree_Kruskal(G);
    cout << endl;
}

int main() {
    std::array<VertexType, NUM> vertexes = {"v0",
                                            "v1",
                                            "v2",
                                            "v3",
                                            "v4",
                                            "v5",
                                            "v6",
                                            "v7",
                                            "v8"};

//    AdjacencyMatrixTest(vertexes, arcs);
    AdjacencyTableTest(vertexes, arcs);

    return 0;
}