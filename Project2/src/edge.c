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

void Edge_setHead(Edge *edge, long int head)
{
    edge->head = head;

    return;
}

void Edge_setTail(Edge *edge, long int tail)
{
    edge->tail = tail;

    return;
}

void Edge_setRelationship(Edge *edge, int relationship)
{
    edge->relationship = relationship;

    return;
}

long int Edge_getHead(Edge *edge)
{
    return edge->head;
}

long int Edge_getTail(Edge *edge)
{
    return edge->tail;
}

int Edge_getRelationship(Edge *edge)
{
    return edge->relationship;
}

void printEdge(Edge* edge)
{
    fprintf(stdout, "Tail: %7ld | Head: %7ld | Relationship: %d\n", edge->tail, edge->head, edge->relationship);

    return;
}

void freeEdge(Edge* edge)
{
    free(edge);

    return;
}
