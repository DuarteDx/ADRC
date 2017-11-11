#include "../include/edge.h"

struct edge_
{
    long int head;
    long int tail;
    int relationship;
};

Edge * newEdge()
{
    Edge *edge = NULL;

        edge = malloc(sizeof(Edge));

        edge->head = -1;
        edge->tail = -1;
        edge->relationship = -1;

    return edge;
}

void Edge_setHead(Edge *edge, int head)
{
    edge->head = head;

    return;
}

void Edge_setTail(Edge *edge, int tail)
{
    edge->tail = tail;

    return;
}

void Edge_setRelationship(Edge *edge, int relationship)
{
    edge->relationship = relationship;

    return;
}
