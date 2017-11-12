#include "../include/defs.h"
#include "../include/edge.h"
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
                /*case 3:
                {
                    if(NULL == tree_root)
                    {
                        fprintf(stdout, "No tree to lookup! Use option 1 first.\n");
                    }
                    else
                    {
                        fprintf(stdout, "Insert address for which to retrieve the next hop:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                            break;
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%s\n", lookupPrefix);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading option, try again.\n");
                            break;
                        }
                        if(!checkValidPrefix(lookupPrefix))
                        {
                            fprintf(stdout, "Wrong type of prefix. Must be a string of 0 and 1.\n");
                            break;
                        }

                        lookUpResult = LookUp(tree_root, lookupPrefix);

                        fprintf(stdout, "Next-Hop: %d\n", lookUpResult);
                    }
                    break;
                }
                case 4:
                {
                    if(NULL == tree_root)
                    {
                        fprintf(stdout, "No tree to insert prefix in! Use option 1 first.\n");
                    }
                    else
                    {
                        fprintf(stdout, "Insert the new address:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                            break;
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%s\n", insertPrefix);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                            break;
                        }
                        if(!checkValidPrefix(insertPrefix))
                        {
                            fprintf(stdout, "Wrong type of prefix. Must be a string of 0 and 1.\n");
                            break;
                        }

                        fprintf(stdout, "Insert the next hop associated with the new address:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                            break;
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%d\n", &insertNextHop);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                            break;
                        }

                        tree_root = InsertPrefix(tree_root, insertPrefix, insertNextHop);

                        fprintf(stdout, "New Prefix added!\n");
                    }
                    break;
                }
                case 5:
                {
                    if(NULL == tree_root)
                    {
                        fprintf(stdout, "No tree to delete prefix from! Use option 1 first.\n");
                    }
                    else
                    {
                        fprintf(stdout, "Insert prefix to delete from tree:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                            break;
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%s\n", deletePrefix);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading option, try again.\n");
                            break;
                        }
                        if(!checkValidPrefix(deletePrefix))
                        {
                            fprintf(stdout, "Wrong type of prefix. Must be a string of 0 and 1.\n");
                            break;
                        }

                        tree_root = DeletePrefix(tree_root, deletePrefix);

                        fprintf(stdout, "Delete operation completed!\n");
                    }
                    break;
                }
                case 6:
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

        free(char_buffer);
        fclose(fp);

    return 0;
}
