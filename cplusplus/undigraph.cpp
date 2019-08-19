//
// Created by zj on 19-8-19.
//

#include "undigraph.h"

void Undigraph::CreateMGraph(MGraph *G) {
    int i, j, k, w;

    cout << "输入顶点数: ";
    cin >> G->numVertexes;
    cout << "输入边集数: ";
    cin >> G->numEdges;

    cout << "输入顶点信息：" << endl;
    for (i = 0; i < G->numVertexes; i++) {
        cin >> G->vexs[i];
    }

    // 初始化边集二维数组
    for (i = 0; i < G->numVertexes; i++) {
        for (j = 0; j < G->numVertexes; j++) {
            if (i == j)
                G->arcs[i][j] = 0;
            else
                G->arcs[i][j] = GINFINITY;
        }
    }

    cout << "输入边信息" << endl;
    for (k = 0; k < G->numEdges; k++) {
        cout << "输入第" << k << "条边的上标、下标和权值: ";
        cin >> i >> j >> w;
        G->arcs[i][j] = w;
        G->arcs[j][i] = w;
    }
}

void Undigraph::PrintMGraph(MGraph G) {
    cout << "顶点数和边数: ";
    cout << G.numVertexes << " " << G.numEdges << endl;
    cout << "顶点信息: " << endl;
    for (int i = 0; i < G.numVertexes; i++) {
        cout << " " << G.vexs[i];
    }
    cout << endl;

    cout << "边集信息: " << endl;
    for (int i = 0; i < G.numVertexes; i++) {
        for (int j = 0; j < G.numVertexes; j++) {
            if (G.arcs[i][j] == GINFINITY) {
                cout.width(4);          // 设置显示域宽10
                cout << "--";
            } else {
                cout.width(4);          // 设置显示域宽10
                cout << G.arcs[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;

}

int *Undigraph::DFSTraverse(MGraph G) {
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

void Undigraph::DFS(MGraph G, int up, int *index) {
    int j;
    // 访问顶点up
    visited[up] = true;
    ordered[*index] = up;
    *index += 1;

    for (j = 0; j < G.numVertexes; j++) {
        if (up != j and G.arcs[up][j] != GINFINITY and !visited[j]) {
            DFS(G, j, index);
        }
    }
}
