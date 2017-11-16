#include "../include/defs.h"
#include "../include/graph.h"
#include "../include/linked_list.h"
#include "../include/functions.h"

int main(int argc, char const *argv[])
{
    long int i = 0;
    FILE *fp = NULL;

    SinglyLinkedList *edge_list_head = NULL;
    Graph *graph = NULL;
    int *routes = NULL;

    bool flag_comercially_connected = false;
    bool flag_customer_cycle = false;

    SinglyLinkedList *routes_head = NULL;

        // Check for correct number of arguments
        if(argc != 2)
        {
            fprintf(stdout, "\nUSAGE: %s <filename>\n\n", argv[0]);
            exit(EXIT_FAILURE);
        }

        // Open the file; abort if unsuccessful
        fp = fopen(argv[1], "r");
        if(NULL == fp)
        {
            fprintf(stdout, "Error opening %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        edge_list_head = readFile(fp);
        graph = GRAPHinit(65536);
        GraphFromEdgeList(graph, edge_list_head);
        flag_customer_cycle = hasCustomerCycles(graph);
        flag_comercially_connected = isCommerciallyConnected(graph);


        for(i = 0; i < Graph_getV(graph); i += 1)
        {
            // if exists
            if(Graph_getAdjOfV(graph, i) != NULL)
            {
                routes = computeElectedRoutes(graph, i, flag_comercially_connected);
                routes_head = SinglyLinkedList_insertAtHead(routes_head, SinglyLinkedList_newNode(routes));
                printRoutes(routes, Graph_getV(graph));
            }
        }

        printRoutes(routes, Graph_getV(graph));

        SinglyLinkedList_freeList(edge_list_head, (void (*)(Item))freeEdge);
        GRAPHfree(graph);
        SinglyLinkedList_freeList(routes_head, NULL);

        fclose(fp);

    return 0;
}
