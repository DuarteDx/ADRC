#include "../include/table.h"

/* struct tableEntry
 * Description: a row of the prefix table. The whole prefix table is a linked list of tableEntry elements
 * Fields: char prefix[PREFIX_SIZE]: string representation of a prefix
 *         int nextHop: the nextHop corresponding to the prefix
 *         struct tableEntry *next: pointer to the next row (also a struct ableEntry)
*/
struct tableEntry
{
    char prefix[PREFIX_SIZE];
    int nextHop;
    struct tableEntry *next;
};

TableEntry readTable(FILE *fp)
{
    TableEntry table_head = NULL;

        table_head = initTable();

        while(!feof(fp)){

        }

    return table_head;
}

int TableEntry_getNextHop(TableEntry tableEntry)
{
    return tableEntry->nextHop;
}

char* TableEntry_getPrefix(TableEntry tableEntry)
{
    return tableEntry->prefix;
}

TableEntry TableEntry_getNextTableEntry(TableEntry tableEntry)
{
    return tableEntry->next;
}

TableEntry initTable()
{
    return NULL;
}
