#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#ifndef _DEFS_H_
#include "./defs.h"
#endif

#ifndef _LINKED_LIST_H
#include "./linked_list.h"
#endif

#ifndef _GRAPH_H_
#include "./graph.h"
#endif

#ifndef _HEAP_H_
#include "./heap.h"
#endif

#define SOURCE 100

SinglyLinkedList * readFile(FILE *fp);
void printEdges(SinglyLinkedList *edge_list_head);
bool isATierOne(long int *tier_one_array, int array_size, long int element);
bool isCommerciallyConnected(Graph *graph);
bool hasCustomerCycles(Graph *graph);

int * computeElectedRoutes(Graph *graph, long int destination, bool flag_comercially_connected);

// TODO
void printRoutes(int *routes, long int num_nodes);

#endif
