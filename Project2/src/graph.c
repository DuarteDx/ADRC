#include "../include/graph.h"

struct graph_ {
    int V;
    int E;
    SinglyLinkedList **adj;
};

Graph * GRAPHinit(long int v)
{
    int i = 0;
    Graph *graph = NULL;

        graph->V = v;
        graph->E = 0;

        graph->adj = (SinglyLinkedList **)malloc(v * sizeof(SinglyLinkedList *));

        for(i = 0; i < v; i += 1)
        {
            graph->adj[i] = NULL;
        }

    return graph;
}

void GRAPHinsertEdge(Graph *graph, Edge *edge)
{
    int v = 0;
    int w = 0;
    int r = 0;

        v = Edge_getHead(edge);
        w = Edge_getTail(edge);
        r = Edge_getRelationship(edge);

        Node * v__ = newNodeWithInit(v, r);
        Node * w__ = newNodeWithInit(w, r);


        SinglyLinkedList * node = SinglyLinkedList_newNode(Item item);

        graph->adj[v] = SinglyLinkedList_insertAtHead(graph->adj[v], w);
        graph->adj[w] = SinglyLinkedList_insertAtHead(graph->adj[w], v);

        graph->E += 1;

    return;
}
