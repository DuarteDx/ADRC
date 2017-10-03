#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#include "defs.h"

/* showMenu
 * Description: Shows the user a menu, and returns the slection number to the calling function
 * Arguments: void
 * Return value: int - the selection number
*/
int showMenu(void);
bool checkValidPrefix(char prefix[PREFIX_SIZE]);

#endif
