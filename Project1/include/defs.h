#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
