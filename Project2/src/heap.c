#include <stdlib.h>
#include <stdio.h>
#include "../include/heap.h"

/* to remove comments, just delete or comment the next line */
#define DEMO

/* A heap is represented by a structure: */
struct _heap
{
    int (*comparison) (Item, Item);     /* function pointer to comparison function of elements in the heap. */
    long int n_elements; 	            /* # elements in heap */
    long int size;                     /* max size of the heap. */
    Item *heapdata;               /* An array of Items. */
};

void PrintHeap(Heap *heap, void (*Item_Print) (Item))
{
    long int i;

        for(i = 0; i < heap->n_elements; i += 1)
        {
            (*Item_Print)(heap->heapdata[i]);
        }

    return;
}

/******************************************************************************
 * NewHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 *
 *****************************************************************************/

Heap * NewHeap(long int size, int (*comparison) (Item, Item))
{
    Heap *heap = NULL;

        heap = (Heap *)malloc(sizeof(Heap));
        if(heap == NULL)
        {
            fprintf(stderr, "Error in malloc of heap\n");
            exit(EXIT_FAILURE);
        }

        heap->n_elements = 0;
        heap->comparison = comparison;
        heap->size = size;
        heap->heapdata = (Item *)malloc(size * sizeof(Item));
        for(long int i = 0; i < size; i += 1)
        {
            heap->heapdata[i] = NULL;
        }

        if(heap->heapdata == NULL)
        {
            printf("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        if(heap->heapdata ==  NULL)
        {
            fprintf(stderr, "Error in malloc of heap data\n");
            exit(EXIT_FAILURE);
        }

    return heap;
}

/******************************************************************************
 * HeapInit()
 *
 * Arguments: heap - pointer to heap
 *            element - pointer to new element
 * Returns: vopid
 * Side-Effects: none
 *
 * Description: add element at the end of heap but does not perform fixup
 *
 *****************************************************************************/

int HeapInit(Heap *heap, Item item)
{
    if (heap->n_elements == heap->size)
    {
        fprintf(stdout, "Heap full (size = %7ld) !\n", heap->size);
        return 0;
    }
    heap->heapdata[heap->n_elements] = item;

    heap->n_elements += 1;

    return 1;
}

/******************************************************************************
 * FixUp()
 *
 * Arguments: heap - pointer to heap structure
 *            k - index of element to fixup
 * Returns:
 * Side-Effects: none
 *
 * Description: Performs fixup from index
 *
 *****************************************************************************/

void FixUp(Heap *heap, long int a, int *weight)
{
    Item t;
    long int k;

        for(k = 0; a != *((long int *)heap->heapdata[k]); k += 1);

        while((k > 0) && (heap->comparison) ((Item) &weight[*((long int*)heap->heapdata[(k - 1) / 2])], (Item) &weight[*((long int*)heap->heapdata[k])]))
        {
            t = (heap->heapdata)[k];
            (heap->heapdata)[k] = (heap->heapdata)[(k - 1) / 2];
            (heap->heapdata)[(k - 1) / 2] = t;

            k = (k - 1) / 2;
        }

    return;
}

/******************************************************************************
 * FixDown()
 *
 * Arguments: heap - pointer to heap structure
 *            k - index of element to fixdown
 * Returns:
 * Side-Effects: none
 *
 * Description: performs fixdown from index
 *
 *****************************************************************************/

void FixDown(Heap * heap, int k, int *weight)
{
    long int j;
    Item t;

        while ((2 * k + 1) < heap->n_elements)
        {
            j = 2 * k + 1;
            if(((j + 1) < heap->n_elements) && (heap->comparison) ((Item) &weight[*((long int    *)heap->heapdata[j])], (Item) &weight[*((long int *)heap->heapdata[j+1])]))
            {
                /* second offspring is smaller than its brother */
                j++;
            }

            if (!(heap->comparison) ((Item) &weight[*((long int *)heap->heapdata[k])], (Item) &weight[*((long int *)heap->heapdata[j])]))
            {
                /* Elements are already in correct order. */
                break;
            }

            /* the 2 elements are not correctly sorted, it is
            necessary to exchange them */
            t = (heap->heapdata)[k];
            (heap->heapdata)[k] = (heap->heapdata)[j];
            (heap->heapdata)[j] = t;
            k = j;
        }

    return;
}

/******************************************************************************
 * RemovePriority
 *
 * Arguments: heap - pointer to heap
 *
 * Returns: Item inse the min value of the heap
 *
 *
 *****************************************************************************/

Item RemoveRoot(Heap *heap, int *weight)
{
    Item t;

        if (heap->n_elements > 0)
        {
            t = (heap->heapdata)[0];
            (heap->heapdata)[0] = (heap->heapdata)[heap->n_elements - 1];
            (heap->heapdata)[heap->n_elements - 1] = t;
            heap->n_elements -= 1;
            FixDown(heap, 0, weight);
            return t;
        }

    return NULL;
}

int HeapEmpty(Heap* heap)
{
    if(heap->n_elements == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int GetHeapN_Elements(Heap *heap)
{
    return (heap->n_elements);
}


/******************************************************************************
 * FreeHeap()
 *
 * Arguments: size - heap size
 *            less - item comparison function
 * Returns: Heap
 * Side-Effects: none
 *
 * Description: allocates space for a new heap of specified size
 *
 *****************************************************************************/

void FreeHeap(Heap *heap, long int vertices)
{
    long int c;

    for(c = 0; c < vertices; c += 1)
    {
        if(heap->heapdata[c] != NULL)
        {
            free(heap->heapdata[c]);
        }
    }
    free(heap->heapdata);
    free (heap);

    return;
}
