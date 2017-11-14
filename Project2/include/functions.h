#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#ifndef _DEFS_H_
#include "./defs.h"
#endif

#ifndef _LINKED_LIST_H
#include "./linked_list.h"
#endif

#ifndef _NODE_H_
#include "./graph.h"
#endif

/* showMenu
 * Description: Shows the user a menu, and returns the slection number to the calling function
 * Arguments: void
 * Return value: int - the selection number
*/
int showMenu(void);
SinglyLinkedList * readFile(FILE *fp);
void printEdges(SinglyLinkedList *edge_list_head);
bool isATierOne(long int *tier_one_array, int array_size, long int element);
bool isCommerciallyConnected(Graph *graph);
bool hasCustomerCycles(Graph *graph);

#endif
