#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "defs.h"
#include "linked_list.h"
#include "edge.h"

/* showMenu
 * Description: Shows the user a menu, and returns the slection number to the calling function
 * Arguments: void
 * Return value: int - the selection number
*/
int showMenu(void);
SinglyLinkedList * readFile(FILE *fp);

#endif
