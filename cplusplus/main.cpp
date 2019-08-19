#include <iostream>
#include <cstring>
#include "common_iostream.h"
#include "undigraph.h"

int main() {
    MGraph G;
    G.numVertexes = 9;
    G.numEdges = 15;
    G.vexs = {"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8"};
    EdgeType arcs[9][9] = {
            {0,         10,        GINFINITY, GINFINITY, GINFINITY, 11,        GINFINITY, GINFINITY, GINFINITY},
            {10,        0,         18,        GINFINITY, GINFINITY, GINFINITY, 16,        GINFINITY, 12},
            {GINFINITY, 18,        0,         22,        GINFINITY, GINFINITY, GINFINITY, GINFINITY, 8},
            {GINFINITY, GINFINITY, 22,        0,         20,        GINFINITY, 24,        16,        21},
            {GINFINITY, GINFINITY, GINFINITY, 20,        0,         26,        GINFINITY, 7,         9},
            {11,        GINFINITY, GINFINITY, GINFINITY, 26,        0,         17,        GINFINITY, GINFINITY},
            {GINFINITY, 16,        GINFINITY, 24,        GINFINITY, 17,        0,         19,        GINFINITY},
            {GINFINITY, GINFINITY, GINFINITY, 16,        7,         GINFINITY, 19,        0,         GINFINITY},
            {GINFINITY, 12,        8,         21,        GINFINITY, GINFINITY, GINFINITY, GINFINITY, 0}
    };
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

    return 0;
}