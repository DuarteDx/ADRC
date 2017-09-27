#include "../include/table.h"

struct tableEntry
{
    char* prefix;
    int next_hop;
    struct tableEntry * next;
};

TableEntry initTable()
{
    return NULL;
}

TableEntry readTable(FILE* fp)
{
    TableEntry table_head = NULL;

    return table_head;
}
