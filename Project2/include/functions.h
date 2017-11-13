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
bool isCommerciallyConnected(Graph *graph);

#endif
