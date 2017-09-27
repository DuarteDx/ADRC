#include "defs.h"

/* PREFIX_SIZE
 * Description: IPv6 addresses are 128 bits in length, so prefixes will never exceed 128 bits
 */
#ifndef PREFIX_SIZE
#define PREFIX_SIZE 128
#endif

typedef struct tableEntry *TableEntry;

/* readTable
 * Description: reads a prefix table from a file and stores it in memory.
 * Arguments: FILE *fp - pointer to the file containing the prefix table in text format
 * Return value: TableEntry - pointer to the (first row of the) prefix table
*/
TableEntry readTable(FILE *fp);

/* TableEntry_getNextHop
 * Description: getter for the nextHop field of a TableEntry
 * Arguments: TableEntry tableEntry - pointer to the row from which we want the value of nextHop
 * Return value: int - the next hop in the table entry
*/
int TableEntry_getNextHop(TableEntry tableEntry);

/* TableEntry_getPrefix
 * Description: getter for the prefix field of a TableEntry
 * Arguments: TableEntry tableEntry - pointer to the row from which we want the value of prefix
 * Return value: int - the prefix in the table entry
*/
char* TableEntry_getPrefix(TableEntry tableEntry);

/* TableEntry_getPrefix
 * Description: returns a pointer to the next table entry
 * Arguments: TableEntry tableEntry - pointer to the current table entry
 * Return value: TableEntry - pointer to the next table entry
*/
TableEntry TableEntry_getNextTableEntry(TableEntry tableEntry);

/* UNDOCUMENTED TODO */
TableEntry initTable();
