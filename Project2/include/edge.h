#ifndef _EDGE_H_
#define _EDGE_H_
#endif

#ifndef _DEFS_H_
#include "./defs.h"
#endif

typedef struct edge_ Edge;

Edge * newEdge();

void Edge_setHead(Edge *edge, int head);
void Edge_setTail(Edge *edge, int tail);
void Edge_setRelationship(Edge *edge, int relationship);
