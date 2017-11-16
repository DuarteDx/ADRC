#include "../include/graph.h"

struct graph_ {
    long int V;
    long int E;
    SinglyLinkedList **adj;
};

long int Graph_getV(Graph *graph)
{
    return graph->V;
}

long int Graph_getE(Graph *graph)
{
    return graph->E;
}

SinglyLinkedList ** Graph_getAdjList(Graph *graph)
{
    return graph->adj;
}

SinglyLinkedList * Graph_getAdjOfV(Graph * graph, long int v)
{
    if((v >= (graph->V)) || (v < 0))
    {
        return NULL;
    }

    return graph->adj[v];
}

Graph * GRAPHinit(long int v)
{
    long int i = 0;
    Graph *graph = NULL;

        graph = (Graph *)malloc(sizeof(Graph));

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
    Node * node_w = NULL;
    SinglyLinkedList *list_element_w = NULL;

        v = Edge_getHead(edge);
        w = Edge_getTail(edge);
        r = Edge_getRelationship(edge);

        node_w = newNodeWithInit(w, r);

        list_element_w = SinglyLinkedList_newNode(node_w);

        graph->adj[v] = SinglyLinkedList_insertAtHead(graph->adj[v], list_element_w);

        graph->E += 1;

    return;
}

void GraphFromEdgeList(Graph *graph, SinglyLinkedList *edge_list_head)
{
    SinglyLinkedList *aux = NULL;

    for(aux = edge_list_head; aux != NULL; aux = SinglyLinkedList_getNextNode(aux))
    {
        GRAPHinsertEdge(graph, (Edge *)SinglyLinkedList_getItem(aux));
    }

    // dirty fix for edge count
    graph->E /= 2;

    return;
}

void GRAPHPrintAdjacenciesList(Graph *graph)
{
    long int i = 0;
    SinglyLinkedList *aux = NULL;

        for(i = 0; i < graph->V; i += 1)
        {
            aux = graph->adj[i];
            if(aux != NULL)
            {
                fprintf(stdout, "Adjacency list for node %7ld:\n", i);
                SinglyLinkedList_printListItems(aux, (void(*)(Item))&Node_printNode);
            }
            else
            {
                // FIXME: this will print a huge spam of no Adjacency nodes
                //fprintf(stdout, "No adjencencies for node %7ld\n", i);
            }
        }

        fprintf(stdout, "Number of edges: %7ld\n", graph->E);

    return;
}

void GRAPHfree(Graph *graph)
{
    long int i = 0;

        for(i = 0; i < graph->V; i += 1)
        {
            if(graph->adj[i] != NULL)
            {
                SinglyLinkedList_freeList(graph->adj[i], (void (*)(Item))&Node_free);
            }
        }

        free(graph->adj);
        free(graph);

    return;
}
