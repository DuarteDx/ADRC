#include "../include/graph.h"

struct graph_ {
    int v;
    int e;
    Node **adj;
};

int GetGraphVertices(Graph *g)
{
    return g->v;
}
