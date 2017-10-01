#include "defs.h"

typedef struct tableEntry_ TableEntry;

/* readTable
 * Description: reads a prefix table from a file and stores it in memory.
 * Arguments: FILE *fp - pointer to the file containing the prefix table in text format
 * Return value: TableEntry - pointer to the (first row of the) prefix table
*/
TableEntry * readTable(FILE *fp);

/* TableEntry_getNextHop
 * Description: getter for the nextHop field of a TableEntry
 * Arguments: TableEntry tableEntry - pointer to the row from which we want the value of nextHop
 * Return value: int - the next hop in the table entry
*/
int TableEntry_getNextHop(TableEntry *tableEntry);

/* TableEntry_getPrefix
 * Description: getter for the prefix field of a TableEntry
 * Arguments: TableEntry tableEntry - pointer to the row from which we want the value of prefix
 * Return value: int - the prefix in the table entry
*/
char* TableEntry_getPrefix(TableEntry *tableEntry);

/* TableEntry_getNextTableEntry
 * Description: returns a pointer to the next table entry
 * Arguments: TableEntry tableEntry - pointer to the current table entry
 * Return value: TableEntry - pointer to the next table entry
*/
TableEntry * TableEntry_getNextTableEntry(TableEntry *tableEntry);

/* newTableEntry
 * Description: Allocates memory for a new table entry element and initializes its fields
 * Arguments: void
 * Return value: TableEntry - pointer to the alocated TableEntry element
*/
TableEntry * newTableEntry(void);

/* printTable
 * Description: Prints to stdout the list of TableEntry elements.
 * Arguments: TableEntry table_head - the element of the list from which to start printing until the end of the list.
 * Return value: void
*/
void printTable(TableEntry *table_head);

/* TableEntry_setPrefix
 * Description: setter for the prefix field of a TableEntry
 * Arguments: TableEntry tableEntry - pointer to the row from which we want to set the value of prefix;
 * char prefix[PREFIX_SIZE] - The new prefix to set
 * Return value: void
*/
void TableEntry_setPrefix(TableEntry *tableEntry, char prefix[PREFIX_SIZE]);

/* TableEntry_setNextHop
 * Description: setter for the nextHop field of a TableEntry
 * Arguments: TableEntry tableEntry - pointer to the row from which we want to set the value of nextHop;
 * int nextHop - The new nextHop to set
 * Return value: void
*/
void TableEntry_setNextHop(TableEntry *tableEntry, int nextHop);

/* TableEntry_insertLast
 * Description: Inserts a table entry at the end of a list of table entries
 * Arguments: TableEntry current - pointer to the current last element of the TableEntry list;
 * TableEntry next: pointer to the TableEntry element which is to be the new last elemente of the TableEntry list.
 * Return value: void
*/
void TableEntry_insertLast(TableEntry *current, TableEntry *next);

/* freeTable
 * Description: Frees the memory alocated for a list of table entries.
 * The frees are iterative, starting from the first entry (head) of the table.
 * Arguments: TableEntry table_head - pointer to the first entry (row) of the table.
 * Return value: void
*/
void freeTable(TableEntry *table_head);
