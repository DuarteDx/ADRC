#include "../include/functions.h"

int showMenu(void)
{
    int option = 0;
    int ret_val_sscanf = 0;
    char *ret_val_fgets = NULL;
    char *char_buffer = NULL;

        char_buffer = (char *)malloc(CHAR_BUFFER_SIZE * sizeof(char));

        fprintf(stdout, "\nChoose a function to call (number); any other number exits the program:\n");
        fprintf(stdout, "1 - Reads a file into an edge list.\n");
        fprintf(stdout, "2 - Prints the edge list.\n");
        fprintf(stdout, "3 - Makes graph from edge list.\n");
        fprintf(stdout, "4 - Prints adjacencies list of graph\n");

        ret_val_fgets = fgets(char_buffer, sizeof(char_buffer), stdin);
        if(NULL == ret_val_fgets)
        {
            fprintf(stdout, "Error reading option, try again.\n");
        }
        ret_val_sscanf = sscanf(char_buffer, "%d\n", &option);
        if(1 != ret_val_sscanf)
        {
            fprintf(stdout, "Error reading option, try again.\n");
        }

        free(char_buffer);

    return option;
}

// reads file contents into an edge list in heap memory
// list is in reverse order of text file lines.
SinglyLinkedList * readFile(FILE *fp)
{
    SinglyLinkedList *edge_list_head = NULL;
    SinglyLinkedList *aux = NULL;
    Edge *edge = NULL;
    long int head = 0;
    long int tail = 0;
    int relationship = 0;
    char buffer[CHAR_BUFFER_SIZE];
    int ret_val_sscanf = 0;

        while(NULL != fgets(buffer, PREFIX_SIZE, fp))
        {
            ret_val_sscanf = sscanf(buffer, "%ld %ld %d", &tail, &head, &relationship);
            if(ret_val_sscanf != 3)
            {
                continue;
            }

            edge = newEdge();
            Edge_setHead(edge, head);
            Edge_setTail(edge, tail);
            Edge_setRelationship(edge, relationship);

            aux = SinglyLinkedList_newNode(edge);

            edge_list_head = SinglyLinkedList_insertAtHead(edge_list_head, aux);
        }

    return edge_list_head;
}

// prints the whole list of edges
void printEdges(SinglyLinkedList *edge_list_head)
{
    fprintf(stdout, "Edge list:\n");
    SinglyLinkedList_printListItems(edge_list_head, (void (*)(Item))&printEdge);

    return;
}
