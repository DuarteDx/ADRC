#include "../include/graph.h"

#define MAX_DISTANCE 10000

int Comparison(Item a, Item b)
{
    int aa, bb;

    bb = *((int *) b);
    aa = *((int *) a);

    return (aa >= bb);
}

void findRoute(Graph *G, int s, int* st, int* wt)
{
    int v, w, vertices, *newint, weight;
    ListNode * t;
    Heap* heap;
    vertices = GetGraphVertices(G);
    heap = NewHeap(vertices, Comparison);
    Adjacency * adjacency;

    for (v = 0; v < vertices; v++)
    {
        st[v] = -1;
        wt[v] = MAX_DISTANCE;

        newint = (int*) malloc(sizeof(int));
        VerifyMalloc((Item) newint);
        *newint = v;
        HeapInit(heap, (Item) newint); /*Se nao funcionar pode ser esta wannabe passagem por referencia*/
    }
    wt[s] = 0;
    st[s] = s;
    FixUp(heap, s, wt);

    while (HeapEmpty(heap))
    {

      /** printf("antes do removemin \n"); */
      /** PrintMe(heap); */

       v = *((int *)RemoveMin(heap, wt)); /*Removes the min value form the heap, returns it, and makes the array an heap again*/

       /**printf("depois do removemin \n");*/
       /**PrintMe(heap);*/

        if (wt[v] != MAX_DISTANCE) /* != '.' because it cant circulate over parking spots */
        {

            for (t = GetGraphAdjHead(G, v); t != NULL; t=getNextNodeLinkedList(t))
            {
                adjacency = (Adjacency*) getItemLinkedList(t);
                w = GetAdjacencyVertice (adjacency);
                weight = GetAdjacencyWeight(adjacency);

                if( wt[w] > (wt[v] + ( weight)))  /*If he's walking weight_mult_factor = 3; if he's on the car weight_mult_factor = 1;*/
                {
                       wt[w] = wt[v] + ( weight);
                       st[w] = v;
                       FixUp(heap, w, wt);
                      /** printf("Fix up \n"); */
                      /** PrintMe(heap);*/
                }
            }
        }
    }
    FreeHeap(heap, vertices);
}
