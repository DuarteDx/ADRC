#include "../include/table.h"

struct tableEntry
{
    char prefix[PREFIX_SIZE];
    int nextHop;
    struct tableEntry * next;
};

TableEntry readTable(FILE* fp)
{
    TableEntry table_head = NULL;

        table_head = initTable();

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
