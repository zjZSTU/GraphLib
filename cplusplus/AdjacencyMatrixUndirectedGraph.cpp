//
// Created by zj on 19-10-24.
//

#include "AdjacencyMatrixUndirectedGraph.h"

void AdjacencyMatrixUndirectedGraph::CreateMGraph(MGraph *G) {
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

void AdjacencyMatrixUndirectedGraph::PrintMGraph(MGraph G) {
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

int *AdjacencyMatrixUndirectedGraph::DFSTraverse(MGraph G) {
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

void AdjacencyMatrixUndirectedGraph::DFS(MGraph G, int up, int *index) {
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


int *AdjacencyMatrixUndirectedGraph::BFSTraverse(MGraph G) {
    int i, j, k;
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
                // 获取队头未访问的顶点
                k = q.front();
                q.pop();

                // 遍历邻接矩阵
                for (j = 0; j < G.numVertexes; j++) {
                    if (k != j and G.arcs[k][j] != GINFINITY and !visited[j]) {
                        // 访问顶点k
                        visited[j] = true;
                        ordered[index] = j;
                        index++;

                        q.push(j);
                    }
                }
            }
        }
    }

    return ordered;
}


void AdjacencyMatrixUndirectedGraph::MiniSpanTree_Prim(MGraph G) {
    int min, i, j, k;
    std::array<int, MAXVEX> adjvex = {};
    std::array<int, MAXVEX> lowcost = {};

    // 最先添加顶点0到MST中
    // adjvex赋值为边的另一个顶点值， 如果顶点已在MST中，指定下标赋值为-1
    int begin_vex = 0;
    adjvex[begin_vex] = 0;
    lowcost[begin_vex] = -1;
    for (i = 1; i < G.numVertexes; i++) {
        lowcost[i] = G.arcs[0][i];
        adjvex[i] = 0;
    }

    int weight = 0;
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
        printf("(%d, %d) %d\n", adjvex[k], k, lowcost[k]);
        weight += lowcost[k];
        // 顶点k已加入MST，lowcost赋值为-1
        lowcost[k] = -1;

        // 比较顶点k的边集和MST的最小权值边集，进行替换
        for (j = 1; j < G.numVertexes; j++) {
            if (k != j and lowcost[j] != -1 and G.arcs[k][j] < lowcost[j]) {
                lowcost[j] = G.arcs[k][j];
                adjvex[j] = k;
            }
        }
    }
    cout << "MST权值和为：" << weight << endl;
}

void AdjacencyMatrixUndirectedGraph::MiniSpanTree_Kruskal(MGraph G) {
    int i, j, k, n, m;
    std::array<Edge, MAXEDGE> edges = {};
    // 保存最小生成树，数组下标表示一个顶点，赋值表示另一个顶点
    std::array<int, MAXEDGE> parent = {};

    // 将边集赋值给edges
    k = 0;
    for (i = 0; i < G.numVertexes; i++) {
        for (j = i + 1; j < G.numVertexes; j++) {
            if (G.arcs[i][j] != GINFINITY) {
                Edge edge;
                edge.begin = i;
                edge.end = j;
                edge.weight = G.arcs[i][j];

                edges[k] = edge;
                k++;
            }
        }
    }
    // 按权值升序排序
    std::sort(edges.begin(), edges.begin() + G.numEdges, less_second);

    int weight = 0;
    // 遍历所有边，
    for (i = 0; i < G.numEdges; i++) {
        n = Find(parent, edges[i].begin);
        m = Find(parent, edges[i].end);
        // 判断两个分量是否同属一个
        if (n != m) {
            parent[n] = m;
            printf("(%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
            weight += edges[i].weight;
        }
    }
    cout << "MST权值和为：" << weight << endl;
}

bool AdjacencyMatrixUndirectedGraph::less_second(Edge x, Edge y) {
    return x.weight < y.weight;
}

int AdjacencyMatrixUndirectedGraph::Find(std::array<int, MAXEDGE> &parent, int f) {
    // 遍历分量
    while (parent[f] > 0) {
        f = parent[f];
    }

    return f;
}
