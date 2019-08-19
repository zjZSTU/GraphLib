#include <iostream>
#include "common_iostream.h"
#include "undigraph.h"

int main() {
    Undigraph graph;

    MGraph G;
    graph.CreateMGraph(&G);
    graph.PrintMGraph(G);

    return 0;
}