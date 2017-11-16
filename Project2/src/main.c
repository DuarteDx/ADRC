#include "../include/defs.h"
#include "../include/graph.h"
#include "../include/linked_list.h"
#include "../include/functions.h"

int main(int argc, char const *argv[])
{
    long int i = 0;

    FILE *fp = NULL;

    Graph *graph = NULL;

    int *routes = NULL;

    bool flag_comercially_connected = false;
    bool flag_customer_cycle = false;

    SinglyLinkedList *edge_list_head = NULL;
    SinglyLinkedList *routes_head = NULL;
    SinglyLinkedList *aux = NULL;

    double customer_routes = 0;
    double peer_routes = 0;
    double provider_routes = 0;
    double no_routes = 0;
    double total_routes = 0;
    double percent_customer_routes = 0;
    double percent_peer_routes = 0;
    double percent_provider_routes = 0;
    double percent_no_routes = 0;

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
        graph = GRAPHinit(HUGE_GRAPH_SIZE);
        GraphFromEdgeList(graph, edge_list_head);
        flag_customer_cycle = hasCustomerCycles(graph);
        flag_comercially_connected = isCommerciallyConnected(graph);

        if(!flag_comercially_connected)
        {
            fprintf(stdout, "WARNING: It was determined that this network is not commercially connected.\nRoute calculation may take a long time\n");
        }

        for(i = 0; i < Graph_getV(graph); i += 1)
        {
            // if exists
            if(Graph_getAdjOfV(graph, i) != NULL)
            {
                routes = computeElectedRoutes(graph, i, flag_comercially_connected);
                routes_head = SinglyLinkedList_insertAtHead(routes_head, SinglyLinkedList_newNode(routes));
            }
        }

        for(aux = routes_head; aux != NULL; aux = SinglyLinkedList_getNextNode(aux))
        {
            routes = ((int *)SinglyLinkedList_getItem(aux));

            for(i = 0; i < Graph_getV(graph); i += 1)
            {
                if(Graph_getAdjOfV(graph, i) != NULL)
                {
                    if(routes[i] == CUSTOMER)
                    {
                        customer_routes += 1;
                    }
                    else if(routes[i] == PEER)
                    {
                        peer_routes += 1;
                    }
                    else if(routes[i] == PROVIDER)
                    {
                        provider_routes += 1;
                    }
                    else if(routes[i] == NO_ROUTE)
                    {
                        no_routes += 1;
                    }
                }
            }
        }

        total_routes = customer_routes + peer_routes + provider_routes;

        percent_customer_routes = (customer_routes / total_routes) * 100;
        percent_peer_routes = (peer_routes / total_routes) * 100;
        percent_provider_routes = (provider_routes / total_routes) * 100;
        percent_no_routes = (no_routes / total_routes) * 100;

        if(flag_customer_cycle)
        {
            fprintf(stdout, "This network has customer cycles.\n");
        }
        else
        {
            fprintf(stdout, "This network does not have customer cycles.\n");
        }

        if(flag_comercially_connected)
        {
            fprintf(stdout, "This network is commercially connected.\n");
        }
        else
        {
            fprintf(stdout, "This network is not commercially connected.\n");
        }

        fprintf(stdout, "Customer routes: %.0lf (%2.2lf %%)\nPeer routes: %.0lf (%2.2lf %%)\nProvider routes: %.0lf (%2.2lf %%)\nNo routes: %.0lf (%2.2lf %%)\nTotal routes: %.0lf\n", customer_routes, percent_customer_routes, peer_routes, percent_peer_routes, provider_routes, percent_provider_routes, no_routes, percent_no_routes, total_routes);

        SinglyLinkedList_freeList(edge_list_head, (void (*)(Item))freeEdge);
        GRAPHfree(graph);
        SinglyLinkedList_freeList(routes_head, NULL);

        fclose(fp);

    exit(EXIT_SUCCESS);
}
