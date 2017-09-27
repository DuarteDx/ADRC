#include "defs.h"
typedef struct tableEntry * TableEntry;

TableEntry initTable(FILE*);
TableEntry readTable(FILE* fp);
