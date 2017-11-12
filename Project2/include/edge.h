#ifndef _EDGE_H_
#define _EDGE_H_
#endif

#ifndef _DEFS_H_
#include "./defs.h"
#endif

typedef struct edge_ Edge;

Edge * newEdge();

void Edge_setHead(Edge *edge, long int head);
void Edge_setTail(Edge *edge, long int tail);
void Edge_setRelationship(Edge *edge, int relationship);

long int Edge_getHead(Edge *edge);
long int Edge_getTail(Edge *edge);
int Edge_getRelationship(Edge *edge);

void printEdge(Edge *edge);

void freeEdge(Edge *edge);
