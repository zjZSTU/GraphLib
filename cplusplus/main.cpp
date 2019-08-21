
#include "undigraph_test.h"

std::array<VertexType, 9> vertexes = {"v0",
                                      "v1",
                                      "v2",
                                      "v3",
                                      "v4",
                                      "v5",
                                      "v6",
                                      "v7",
                                      "v8"};
EdgeType arcs[9][9] = {
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


int main() {
    UndigraphTest undigraphTest;
//    undigraphTest.MGraphUse(arcs);
    undigraphTest.GraphAdjListUse(vertexes, arcs);

    return 0;
}