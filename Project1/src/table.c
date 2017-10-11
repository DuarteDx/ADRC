#include "../include/table.h"

/* struct tableEntry_
 * Alias: TableEntry;
 * Description: a row of the prefix table. The whole prefix table is a linked list of tableEntry_ elements
 * Fields: char prefix[PREFIX_SIZE]: string representation of a prefix
 *         int nextHop: the nextHop corresponding to the prefix
 *         struct tableEntry_ *next: pointer to the next row
*/
struct tableEntry_
{
    char prefix[PREFIX_SIZE];
    int nextHop;
    TableEntry *next;
};

TableEntry * newTableEntry()
{
    TableEntry *tableEntry = NULL;

        tableEntry = (TableEntry *)malloc(sizeof(TableEntry));
        tableEntry->nextHop = NO_HOP;
        tableEntry->next = NULL;

    return tableEntry;
}

char * TableEntry_getPrefix(TableEntry *tableEntry)
{
    return tableEntry->prefix;
}

int TableEntry_getNextHop(TableEntry *tableEntry)
{
    return tableEntry->nextHop;
}

TableEntry * TableEntry_getNextTableEntry(TableEntry *tableEntry)
{
    return tableEntry->next;
}

void TableEntry_setPrefix(TableEntry *tableEntry, char prefix[PREFIX_SIZE])
{
    strncpy(tableEntry->prefix, prefix, PREFIX_SIZE);

    return;
}

void TableEntry_setNextHop(TableEntry *tableEntry, int nextHop)
{
    tableEntry->nextHop = nextHop;

    return;
}

void TableEntry_setNextTableEntry(TableEntry *current, TableEntry *next)
{
    current->next = next;

    return;
}

void freeTable(TableEntry *table_head)
{
    TableEntry *aux_table_entry = NULL;

        aux_table_entry = table_head;

        while(NULL != aux_table_entry)
        {
            table_head = TableEntry_getNextTableEntry(table_head);
            free(aux_table_entry);
            aux_table_entry = table_head;
        }

    return;
}

TableEntry * readTable(FILE *fp)
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

            aux_table_entry->nextHop = nextHop;
            TableEntry_setPrefix(aux_table_entry, prefix);

            aux_table_entry2 = newTableEntry();
            aux_table_entry->next = aux_table_entry2;
            aux_table_entry3 = aux_table_entry;
            aux_table_entry = aux_table_entry2;
        }

        free(aux_table_entry);
        aux_table_entry3->next = NULL;

    return table_head;
}

void printTable(TableEntry *table_head)
{
    TableEntry *aux_table_entry = NULL;
    int i = 0;

        for(aux_table_entry = table_head, i = 0; aux_table_entry != NULL; aux_table_entry = aux_table_entry->next, i += 1)
        {
            fprintf(stdout, "Entry %d: Prefix: %s | Next hop: %d\n", i, aux_table_entry->prefix, aux_table_entry->nextHop);
        }

    return;
}
