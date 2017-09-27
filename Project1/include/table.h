#include "defs.h"
typedef struct tableEntry * TableEntry;

#ifndef PREFIX_SIZE
#define PREFIX_SIZE 128
#endif

TableEntry readTable(FILE* fp);
TableEntry initTable();

int TableEntry_getNextHop(TableEntry tableEntry);
char* TableEntry_getPrefix(TableEntry tableEntry);
TableEntry TableEntry_getNextTableEntry(TableEntry tableEntry);
