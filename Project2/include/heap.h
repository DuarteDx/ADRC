#include "defs.h"


typedef struct _heap Heap;

Heap *NewHeap(long int, int (*comparison) (Item, Item));
void FixUp(Heap *heap, long int a, int *weight, long int *);
void FixDown(Heap *, int, int *, long int *);
int HeapInit(Heap *, Item, long int *);
int HeapEmpty(Heap*);
Item RemoveRoot(Heap * h, int *, long int *);
void FreeHeap(Heap * , long int);
void PrintHeap(Heap *heap, void (*Item_Print) (Item));
