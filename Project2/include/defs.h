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

#ifndef LINKED_LIST_H
#include "linked_list.h"
#endif

#ifndef HEAP_H
#include "heap.h"
#endif

#ifndef GRAPH_H
#include "graph.h"
#endif

#ifndef _EDGE_H
#include "./edge.h"
#endif

/* CHAR_BUFFER_SIZE
 * Description: generic text input buffer size limit
*/
#ifndef CHAR_BUFFER_SIZE
#define  CHAR_BUFFER_SIZE 512
#endif

/* PREFIX_SIZE
 * Description: IPv6 addresses are 128 bits in length, so prefixes will never exceed 128 bits
 */
#ifndef PREFIX_SIZE
#define PREFIX_SIZE 128
#endif

#endif
