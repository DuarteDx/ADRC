#include "../include/defs.h"

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

int readTable(FILE* fp)
{
    TableEntry table_head = initTable();

    return table_head;
}