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
        fprintf(stdout, "5 - Is it commercially connected? Find out now!\n");

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

bool isATierOne(long int *tier_one_array, int array_size, long int element)
{
    int i = 0;

        for(i = 0; i < array_size; i += 1)
        {
            if(tier_one_array[i] == element)
            {
                return true;
            }
        }

    return false;
}

bool isCommerciallyConnected(Graph *graph)
{
    long int i = 0;
    long int *tier_one = NULL;
    SinglyLinkedList *aux = NULL;
    bool isTierOne = true;
    int tier_one_count = 0;
    int tier_one_connections = 0;

        // find all tier ones (and their count) and put them in an array
        for(i = 0; i < Graph_getV(graph); i += 1)
        {
            if(Graph_getAdjOfV(graph, i) != NULL)
            {
                for(aux = Graph_getAdjOfV(graph, i); aux != NULL; aux = SinglyLinkedList_getNextNode(aux))
                {
                    if(Node_getRelationship((Node *)SinglyLinkedList_getItem(aux)) == PROVIDER)
                    {
                        isTierOne = false;
                        break;
                    }
                }

                if(true == isTierOne)
                {
                    tier_one_count += 1;
                    tier_one = realloc(tier_one, tier_one_count * sizeof(long int));
                    tier_one[tier_one_count-1] = i;
                }
                else
                {
                    isTierOne = true;
                }
            }
        }

        fprintf(stdout, "TIER ONES ARE:\n");
        for(i = 0; i < tier_one_count; i += 1)
        {
            fprintf(stdout, "%7ld\n", tier_one[i]);
        }

        // iterate through the array of tier ones to find if they are all connected to each other
        // if they are, then the network is commercially connected.
        // if at least one of the tier_ones is not connected to ALL of the others, then the network is not commercially connected.
        for(i = 0; i < tier_one_count; i += 1)
        {
            for(aux = Graph_getAdjOfV(graph, tier_one[i]); aux != NULL; aux = SinglyLinkedList_getNextNode(aux))
            {
                // A tier 1 can have relationships with other piers that are themselves NOT tier 1
                if(isATierOne(tier_one, tier_one_count, Node_getV((Node *)SinglyLinkedList_getItem(aux))))
                {
                    tier_one_connections += 1;
                }
            }
            if(tier_one_connections == (tier_one_count - 1))
            {
                tier_one_connections = 0;
            }
            else
            {
                return false;
            }
        }

        free(tier_one);

    return true;
}

void Int_free(int *number)
{
    free(number);

    return;
}

bool hasCustomerCycles(Graph *graph)
{
    long int i = 0;
    SinglyLinkedList *head = NULL;
    SinglyLinkedList *aux = NULL;
    SinglyLinkedList *aux2 = NULL;
    int in_neighbours[65536];
    long int *number = NULL;
    long int node_to_process = 0;
    long int counter = 0;
    long int nodes_with_inbound_neighbour = 0;

        memset(in_neighbours, 0, 65536*sizeof(int));

        // populate array of inbount neighbours. Node i has an inbound neighbours, each corresponding to a provider
        for(i = 0; i < Graph_getV(graph); i += 1)
        {
            if(Graph_getAdjOfV(graph, i) != NULL)
            {
                for(aux = Graph_getAdjOfV(graph, i); aux != NULL; aux = SinglyLinkedList_getNextNode(aux))
                {
                    if(Node_getRelationship((Node *)SinglyLinkedList_getItem(aux)) == PROVIDER)
                    {
                        in_neighbours[i] += 1;
                    }
                }
            }
            else
            {
                in_neighbours[i] = -1;
            }
        }

        for(i = 0; i < Graph_getV(graph); i += 1)
        {
            if(in_neighbours[i] == 0)
            {
                number = malloc(sizeof(long int));
                *number = i;
                head = SinglyLinkedList_insertAtHead(head, SinglyLinkedList_newNode(number));
            }
        }

        aux = head;
        while(head != NULL)
        {
            aux = head;

            node_to_process = *((long int *)SinglyLinkedList_getItem(aux));

            for(aux2 = Graph_getAdjOfV(graph, node_to_process); aux2 != NULL; aux2 = SinglyLinkedList_getNextNode(aux2))
            {
                if(Node_getRelationship((Node *)SinglyLinkedList_getItem(aux)) == CUSTOMER)
                {
                    in_neighbours[i] += 1;
                }
            }

            SinglyLinkedList_getNextNode(head);
            SinglyLinkedList_freeNode(aux, (void (*)(Item))&Int_free);
        }
}

// TODO: SHITSTORM
/*
Computes the elected routes for a certain destination in a network.
Returns the elected routes
*/
//TODO: FIRST CHECK IF IT'S COMMERCIALLY CONNECTED. IF NOT WE RUN THIS ALGO. IF IT IS WE RUN ANOTHER ALGO.
/*
int* computeElectedRoutes(Graph *graph, long int destination)
{
    int * routes = NULL;
    int i = 0;
    int node = -1;
    int tail = -1;
    int head = -1;
    int relationship = -1;
    int head_route = -1;
    SinglyLinkedList* nodeAdjs = NULL;
    SinglyLinkedList* aux = NULL;

    //Get memory for the routes array
    routes = (int*)malloc(sizeof(int) * GRAPH_getV(graph));

    //Initialize routes array
    for(i = 0; i < GRAPH_getV(graph); i++)
    {
        routes[i] = -1;
    }

    //Initialize destination Node
    routes[destination] = 10;

    //Precisamos de inicializar o Heap com o numero de nos e tudo a 0.
    HEAP_init(0);

    //Add destination to Heap
    HEAP_changeNode(destination, 10);
    HEAP_fixUp();

    while(!HEAP_isEmpty())
    {
        //Ir buscar a maior prioridade do Heap, a ordem de prioridades, da maior para a menor é: source(10) - customer link(3) - peer link(2) - provider link(1) - not linked(0)
        head = HEAP_getHighestPriority(heap) //Precisa de condição caso a prioridade seja 0. Nesse caso teremos de descartar esse nó, returnar -1 e chegar à conclusão que a rede não é commercially linked.

        //Get the adjancency list for this node
        nodeAdj = GRAPH_getAdj(head);

        while(nodeAdj != NULL)
        {
            tail = Edge_getHead((Edge)SinglyLinkedList_getItem(nodeAdj));
            relationship = Edge_getRelationship((Edge)SinglyLinkedList_getItem(nodeAdj));

            //If the tail is a provider and we're source or our elected route is a customer link we export our route
            if(relationship == 1 && (routes[head] == 10 || routes[head] == 3))
            {
                //Change the elected route of the Tail if the existing one is worse
                if(routes[tail] < 3)
                {
                    //Change the prioriy of the node in the heap
                    HEAP_changeNode(tail, 3);
                    HEAP_fixUp();
                    routes[tail] = 3;
                }
            }
            }
            //If the tail is a peer and we're source or have a customer link our elected route is a customer link and we export our route
            else if (relationship == 2 && (routes[head] == 10 || routes[head] == 3))
            {
                //Change the prioriy of the node in the heap
                HEAP_changeNode(tail, 2);

                //Change the elected route of the Tail if the existing one is worse
                if(routes[tail] < 2)
                {
                    //Change the prioriy of the node in the heap
                    HEAP_changeNode(tail, 2);
                    HEAP_fixUp();

                    routes[tail] = 2;
                }
            }
            //If the tail is a customer we export our route
            else if (relationship == 3 && routes[head] != -1)

            {
                //Change the elected route of the Tail if the existing one is worse
                if(routes[tail] < 1)
                {
                    //Change the prioriy of the node in the heap
                    HEAP_changeNode(tail, 1);
                    HEAP_fixUp();

                    routes[tail] = 1;
                }
            }


            //Get the next node in the adjencencies list
            nodeAdj = SinglyLinkedList_getNextNode(nodeAdj);
        }

        //Remove the node we just treated from the heap and fix it
        HEAP_remove(head);
        HEAP_fixUp();
    }

    return routes;
}
*/
