#ifndef _GRAPH_H_
#define _GRAPH_H_
#endif

#ifndef _DEFS_H_
#include "./defs.h"
#endif

#ifndef _EDGE_H
#include "./edge.h"
#endif

#ifndef _LINKED_LIST_H
#include "./linked_list.h"
#endif

#ifndef _HEAP_H
#include "./heap.h"
#endif

/* Edge relationships:
 * -1 - no relationship
 * 1 - tail is a provider of head;
 * 2 - tail is a peer of head;
 * 3 - tail is a costumer of head;
 */

/* Adjacency list representation of a graph */
typedef struct graph_ Graph;


Graph GRAPHinit(int);

void GRAPHinsertE(Graph, Edge);

void GRAPHshow(Graph);

void GRAPHplot(Graph, char *);

int randV(Graph);

Graph GRAPHrandE(int, int);

Graph GRAPHrandp(int, int);

int GetGraphVertices(Graph *);
