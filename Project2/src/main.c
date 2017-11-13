#include "../include/defs.h"
#include "../include/graph.h"
#include "../include/linked_list.h"
#include "../include/functions.h"

int main(int argc, char const *argv[])
{
    int choice = 0;
    bool keepRunning = true;
    FILE *fp = NULL;
    char *char_buffer = NULL;
    char *ret_val_fgets = NULL;
    int ret_val_sscanf = 0;

    SinglyLinkedList *edge_list_head = NULL;
    Graph *graph = NULL;

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

        char_buffer = (char *)malloc(CHAR_BUFFER_SIZE * sizeof(char));

        while(true == keepRunning)
        {
            choice = showMenu();
            switch(choice)
            {
                case 1:
                {
                    if(NULL == edge_list_head)
                    {
                        edge_list_head = readFile(fp);
                    }
                    else
                    {
                        fprintf(stdout, "The file was already read and the edges are in memory\n");
                    }
                    break;
                }
                case 2:
                {
                    if(NULL == edge_list_head)
                    {
                        fprintf(stdout, "No edge list to print! Use option 1 first.\n");
                    }
                    else
                    {
                        printEdges(edge_list_head);
                    }
                    break;
                }
                case 3:
                {
                    if(NULL == edge_list_head)
                    {
                        fprintf(stdout, "No edge list to convert to graph. Use option 1 first.\n");
                    }
                    else if(graph != NULL)
                    {
                        fprintf(stdout, "Graph already constructed!\n");
                    }
                    else
                    {
                        graph = GRAPHinit(65355);
                        GraphFromEdgeList(graph, edge_list_head);
                    }
                    break;
                }
                case 4:
                {
                    if(NULL == graph)
                    {
                        fprintf(stdout, "No graph.\n");
                    }
                    else
                    {
                        GRAPHPrintAdjacenciesList(graph);
                    }
                    break;
                }
                case 5:
                {
                    if(NULL == graph)
                    {
                        fprintf(stdout, "No graph. Use 1\n");
                    }
                    else
                    {
                        if(isCommerciallyConnected(graph))
                        {
                            fprintf(stdout, "The network is commercially connected\n");
                        }
                        else
                        {
                            fprintf(stdout, "The network is not commercially connected\n");
                        }
                    }
                    break;
                }
                /*case 6:
                {
                    if(NULL == tree_root)
                    {
                        fprintf(stdout, "No prefix tree to convert! Use option 1 first.\n");
                    }
                    else
                    {
                        tree_root_2 = BinaryToTwoBit(tree_root);
                        fprintf(stdout, "Convertion complete!\n");
                    }
                    break;
                }
                case 7:
                {
                    if(NULL == tree_root_2)
                    {
                        fprintf(stdout, "No tree to print! Use option 6 first.\n");
                    }else{
                        PrintTableEven(tree_root_2, address);
                    }
                    break;
                }*/
                default:
                {
                    keepRunning = false;
                    break;
                }
            }
        }

        SinglyLinkedList_freeList(edge_list_head, (void (*)(Item))freeEdge);
        GRAPHfree(graph);

        free(char_buffer);
        fclose(fp);

    return 0;
}
