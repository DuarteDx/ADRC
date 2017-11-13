#ifndef _GRAPH_H_
#define _GRAPH_H_
#endif

#ifndef _DEFS_H_
#include "./defs.h"
#endif

#ifndef _EDGE_H
#include "./edge.h"
#endif

#ifndef _NODE_H_
#include "./node.h"
#endif

#ifndef _LINKED_LIST_H
#include "./linked_list.h"
#endif

/* Edge relationships:
 * -1 - no relationship
 * 1 - tail is a provider of head;
 * 2 - tail is a peer of head;
 * 3 - tail is a costumer of head;
 */

/* Adjacency list representation of a graph */
typedef struct graph_ Graph;

Graph * GRAPHinit(long int);

void GRAPHinsertEdge(Graph *, Edge *);

void GRAPHshow(Graph *);

void GRAPHplot(Graph *, char *);

int randV(Graph *);

Graph GRAPHrandE(int, int);

Graph GRAPHrandp(int, int);

void GraphFromEdgeList(Graph *graph, SinglyLinkedList *edge_list_head);

void GRAPHPrintAdjacenciesList(Graph *graph);
