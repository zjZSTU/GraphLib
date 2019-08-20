//
// Created by zj on 19-8-19.
//

#ifndef CPLUSPLUS_GRAPH_H
#define CPLUSPLUS_GRAPH_H

/**
 * 保存图的存储结构以及常用的宏定义
 */

#include <iostream>
#include <array>

// 假定最大顶点个数
#define MAXVEX 100
// 假定最大边集个数
#define MAXEDGE 100
// 模拟无穷大
#define GINFINITY 63335


// 顶点数据类型
typedef std::string VertexType;
// 边权值类型
typedef int EdgeType;

// 权值边存储结构
typedef struct {
    int begin;
    int end;
    int weight;
} Edge;

// 邻接矩阵存储结构
typedef struct {
    // 顶点表
    std::array<VertexType, MAXVEX> vexs;
    // 边表
    std::array<std::array<EdgeType, MAXVEX>, MAXVEX> arcs;
    int numVertexes, numEdges;
} MGraph;

#endif //CPLUSPLUS_GRAPH_H
