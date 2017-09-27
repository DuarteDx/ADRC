#include "../include/table.h"

/* struct tableEntry
 * Description: a row of the prefix table. The whole prefix table is a linked list of tableEntry elements
 * Fields: char prefix[PREFIX_SIZE]: string representation of a prefix
 *         int nextHop: the nextHop corresponding to the prefix
 *         struct tableEntry *next: pointer to the next row (also a struct ableEntry)
*/
struct tableEntry_
{
    char prefix[PREFIX_SIZE];
    int nextHop;
    TableEntry* next;
};

int TableEntry_getNextHop(TableEntry* tableEntry)
{
    return tableEntry->nextHop;
}

char* TableEntry_getPrefix(TableEntry* tableEntry)
{
    return tableEntry->prefix;
}

TableEntry* TableEntry_getNextTableEntry(TableEntry* tableEntry)
{
    return tableEntry->next;
}

void TableEntry_setPrefix(TableEntry* tableEntry, char prefix[PREFIX_SIZE])
{
    strncpy(tableEntry->prefix, prefix, PREFIX_SIZE);

    return;
}

void TableEntry_setNextHop(TableEntry* tableEntry, int nextHop)
{
    tableEntry->nextHop = nextHop;

    return;
}

void TableEntry_insertNext(TableEntry* current, TableEntry* next)
{
    current->next = next;

    return;
}

TableEntry* newTableEntry()
{
    TableEntry *tableEntry = NULL;

        tableEntry = (TableEntry*)malloc(sizeof(TableEntry));

    return tableEntry;
}

TableEntry* readTable(FILE *fp)
{
    TableEntry *table_head = NULL;
    TableEntry *aux_table_entry = NULL;
    TableEntry *aux_table_entry2 = NULL;
    TableEntry *aux_table_entry3 = NULL;
    int nextHop = 0;
    char prefix[PREFIX_SIZE];
    char buffer[CHAR_BUFFER_SIZE];
    int ret_val_sscanf = 0;

        table_head = newTableEntry();
        aux_table_entry = table_head;

        while(NULL != fgets(buffer, PREFIX_SIZE, fp))
        {
            ret_val_sscanf = sscanf(buffer, "%s %d", prefix, &nextHop);
            if(ret_val_sscanf != 2)
            {
                continue;
            }

            TableEntry_setNextHop(aux_table_entry, nextHop);
            TableEntry_setPrefix(aux_table_entry, prefix);

            aux_table_entry2 = newTableEntry();
            TableEntry_insertNext(aux_table_entry, aux_table_entry2);
            aux_table_entry3 = aux_table_entry;
            aux_table_entry = aux_table_entry2;
        }

        free(aux_table_entry);
        aux_table_entry3->next = NULL;

    return table_head;
}

void printTable(TableEntry *table_head)
{
    TableEntry* aux_table_entry = NULL;
    int i = 0;

        for(aux_table_entry = table_head, i = 0; aux_table_entry != NULL; aux_table_entry = TableEntry_getNextTableEntry(aux_table_entry), i += 1)
        {
            fprintf(stdout, "Entry %d: Prefix: %s | Next hop: %d\n", i, TableEntry_getPrefix(aux_table_entry), TableEntry_getNextHop(aux_table_entry));
        }

    return;
}

void freeTable(TableEntry* table_head)
{
    TableEntry* aux_table_entry = NULL;

        aux_table_entry = table_head;

        while(NULL != aux_table_entry) {
            table_head = TableEntry_getNextTableEntry(table_head);
            free(aux_table_entry);
            aux_table_entry = table_head;
        }

    return;
}
