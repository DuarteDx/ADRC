#include "../include/functions.h"
#include "../include/table.h"
#include "../include/tree.h"
#include "../include/tree2.h"

int main(int argc, char const *argv[])
{

    int choice = 0;
    FILE *fp = NULL;
    TableEntry *table_head = NULL;
    TreeNode *tree_root = NULL;
    TreeNode_2 *tree_root_2 = NULL;
    bool keepRunning = true;
    char address[PREFIX_SIZE];
    char lookupPrefix[PREFIX_SIZE];
    char insertPrefix[PREFIX_SIZE];
    char deletePrefix[PREFIX_SIZE];
    int lookUpResult = 0;
    int insertNextHop = -1;
    char *char_buffer = NULL;
    char *ret_val_fgets = NULL;
    int ret_val_sscanf = 0;

        // static array initilization
        memset(address, 0, PREFIX_SIZE * sizeof(char));
        memset(lookupPrefix, 0, PREFIX_SIZE * sizeof(char));
        memset(insertPrefix, 0, PREFIX_SIZE * sizeof(char));
        memset(deletePrefix, 0, PREFIX_SIZE * sizeof(char));

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
                    if(NULL == table_head)
                    {
                        table_head = readTable(fp);
                        tree_root = PrefixTree(table_head);
                    }
                    else
                    {
                        fprintf(stdout, "The file was already read and the tree is in memory!\n");
                    }
                    break;
                }
                case 2:
                {
                    if(NULL == tree_root)
                    {
                        fprintf(stdout, "No tree to print! Use option 1 first.\n");
                    }
                    else
                    {
                        PrintTable(tree_root, address);
                    }
                    break;
                }
                case 3:
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
                }
                default:
                {
                    keepRunning = false;
                    break;
                }
            }
        }

        free(char_buffer);
        if(NULL != table_head)
        {
            freeTable(table_head);
        }
        if(NULL != tree_root)
        {
            freeTree(tree_root);
        }
        if(NULL != tree_root_2)
        {
            freeTree2(tree_root_2);
        }

        fclose(fp);

    exit(EXIT_SUCCESS);
}
