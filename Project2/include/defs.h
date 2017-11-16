#ifndef _DEFS_H_
#define _DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @brief Generic pointer type Item
 *
 * Saves the pain of always writing the *, making the code easier to read
 */
typedef void *Item;

/* CHAR_BUFFER_SIZE
 * Description: generic text input buffer size limit
*/
#ifndef CHAR_BUFFER_SIZE
#define  CHAR_BUFFER_SIZE 512
#endif

#ifndef HUGE_GRAPH_SIZE
#define  HUGE_GRAPH_SIZE 65536
#endif

#endif
