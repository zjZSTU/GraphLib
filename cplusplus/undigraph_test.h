//
// Created by zj on 19-8-21.
//

#ifndef CPLUSPLUS_UNDIGRAPH_TEST_H
#define CPLUSPLUS_UNDIGRAPH_TEST_H


#include "common_iostream.h"
#include "undigraph.h"
#include <cstring>

using std::memcpy;
using std::array;

class UndigraphTest {

public:
    void MGraphUse(EdgeType arcs[][9]);

    void GraphAdjListUse(array<VertexType, 9> vertexes, EdgeType arcs[][9]);

};


#endif //CPLUSPLUS_UNDIGRAPH_TEST_H
