#include "../include/functions.h"

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

        while(NULL != fgets(buffer, CHAR_BUFFER_SIZE, fp))
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

// figure out if there are customer cycles by ordering topologically
bool hasCustomerCycles(Graph *graph)
{
    long int i = 0;
    SinglyLinkedList *head = NULL;
    SinglyLinkedList *aux = NULL;
    SinglyLinkedList *aux2 = NULL;
    int in_neighbours[HUGE_GRAPH_SIZE];
    long int *number = NULL;
    long int node_to_process = 0;
    long int counter = 0;
    long int number_of_nodes = 0;

        memset(in_neighbours, 0, HUGE_GRAPH_SIZE*sizeof(int));

        // populate array of inbound neighbours. Node i has an inbound neighbours, each corresponding to a provider
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
                number_of_nodes += 1;
            }
            else
            {
                in_neighbours[i] = -1;
            }
        }

        // make list of nodes to process
        for(i = 0; i < Graph_getV(graph); i += 1)
        {
            if(in_neighbours[i] == 0)
            {
                number = malloc(sizeof(long int));
                *number = i;
                head = SinglyLinkedList_insertAtHead(head, SinglyLinkedList_newNode(number));
            }
        }

        // start removing nodes and remove inbound neighbours accordingly
        while(head != NULL)
        {
            aux = head;
            head = SinglyLinkedList_getNextNode(head);

            node_to_process = *((long int *)SinglyLinkedList_getItem(aux));

            for(aux2 = Graph_getAdjOfV(graph, node_to_process); aux2 != NULL; aux2 = SinglyLinkedList_getNextNode(aux2))
            {
                if(Node_getRelationship((Node *)SinglyLinkedList_getItem(aux2)) == CUSTOMER)
                {
                    in_neighbours[Node_getV((Node *)SinglyLinkedList_getItem(aux2))] -= 1;
                    if(in_neighbours[Node_getV((Node *)SinglyLinkedList_getItem(aux2))] == 0)
                    {
                        number = malloc(sizeof(long int));
                        *number = Node_getV((Node *)SinglyLinkedList_getItem(aux2));
                        head = SinglyLinkedList_insertAtHead(head, SinglyLinkedList_newNode(number));
                    }

                }
            }

            counter += 1;

            SinglyLinkedList_freeNode(aux, (void (*)(Item))&Int_free);
        }

        if(counter == number_of_nodes)
        {
            return false;
        }

    return true;
}

// priorities: SOURCE > CUSTOMER > PEER > PROVIDER > NO ROUTE > NULL
// maxHeap (greatest value at root)
int comparison(Item a, Item b)
{
    int aa, bb;

    bb = *((int *) b);
    aa = *((int *) a);

    return (aa <= bb);
}

// Computes the elected routes for a certain destination in a network. Returns the elected routes
int * computeElectedRoutes(Graph *graph, long int destination, bool flag_comercially_connected)
{
    int *routes = NULL;
    long int *num_ptr = NULL;
    long int tail = -1;
    long int i = 0;
    long int head = -1;
    int relationship = -1;
    Heap *heap = NULL;
    SinglyLinkedList *adjHead = NULL;
    long int num_nodes = 0;
    bool allProviderFlag = false;

        num_nodes = Graph_getV(graph);

        //Allocate and initialize routes array
        routes = (int *)malloc(sizeof(int) * num_nodes);
        memset(routes, -1, sizeof(int) * num_nodes);

        //Initialize destination Node
        routes[destination] = SOURCE;

        //Precisamos de inicializar o Heap
        heap = NewHeap(num_nodes, comparison);

        // Put all nodes in the heap
        for(i = 0; i < num_nodes; i += 1)
        {
            if(Graph_getAdjOfV(graph, i) != NULL)
            {
                num_ptr = malloc(sizeof(long int));
                *num_ptr = i;

                HeapInit(heap, (Item)num_ptr);
                FixUp(heap, i, routes);
            }
        }

        while(!HeapEmpty(heap))
        {
            //Ir buscar a maior prioridade do Heap, a ordem de prioridades, da maior para a menor é: source(10) - customer link(3) - peer link(2) - provider link(1) - not linked(0)
            head = *(int *)RemoveRoot(heap, routes);

            if(flag_comercially_connected)
            {
                if(routes[head] == PROVIDER)
                {
                    allProviderFlag = true;
                    break;
                }
            }

            // for each neighbour v of u
            for(adjHead = Graph_getAdjOfV(graph, head); adjHead != NULL; adjHead = SinglyLinkedList_getNextNode(adjHead))
            {
                tail = Node_getV((Node*)SinglyLinkedList_getItem(adjHead));
                relationship = Node_getRelationship((Node*)SinglyLinkedList_getItem(adjHead));

                //If the tail is a provider and our elected route is a customer link we export our route
                if(relationship == PROVIDER && (routes[head] == CUSTOMER || routes[head] == SOURCE))
                {
                    //Change the elected route of the Tail if the existing one is worse
                    if(routes[tail] < CUSTOMER)
                    {
                        routes[tail] = CUSTOMER;
                        FixUp(heap, tail, routes);
                    }
                }
                //If the tail is a peer and we're source or have a customer link our elected route is a customer link and we export our route
                else if((relationship == PEER) && (routes[head] == CUSTOMER || routes[head] == SOURCE))
                {
                    //Change the elected route of the Tail if the existing one is worse
                    if(routes[tail] < PEER)
                    {
                        routes[tail] = PEER;
                        FixUp(heap, tail, routes);
                    }
                }
                //If the tail is a customer we export our route
                else if(relationship == CUSTOMER)
                {
                    //Change the elected route of the Tail if the existing one is worse
                    if(routes[tail] < PROVIDER)
                    {
                        routes[tail] = PROVIDER;
                        FixUp(heap, tail, routes);
                    }
                }

                // TODO: BUG
                if(routes[tail] < NO_ROUTE)
                {
                    routes[tail] = NO_ROUTE;
                }
            }
        }

        if(allProviderFlag)
        {
            for(i = 0; i < num_nodes; i += 1)
            {
                if(Graph_getAdjOfV(graph, i) != NULL)
                {
                    if(routes[i] < PROVIDER)
                    {
                        routes[i] = PROVIDER;
                    }
                }
            }
        }

        FreeHeap(heap, num_nodes);

    return routes;
}

void printRoutes(int *routes, long int num_nodes)
{
    long int i = 0;

        for(i = 0; i < num_nodes; i += 1)
        {
            if(routes[i] != -1)
            {
                fprintf(stdout, "Node: %7ld | Route: %d\n", i, routes[i]);
            }
        }
        fprintf(stdout, "\n");

    return;
}
