#include "../include/table.h"
#include "../include/tree.h"
#include "../include/functions.h"

int main(int argc, char const *argv[]) {

    int choice = 0;
    FILE *fp = NULL;
    TableEntry *table_head = NULL;
    TreeNode *tree_root = NULL;
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
    int i = 0;

        // static array initilization
        for(i = 0; i < PREFIX_SIZE; i += 1)
        {
            address[i] = '\0';
            lookupPrefix[i] = '\0';
            insertPrefix[i] = '\0';
            deletePrefix[i] = '\0';
        }

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
                    table_head = readTable(fp);
                    //printTable(table_head);
                    tree_root = PrefixTree(table_head);
                    break;
                }
                case 2:
                {
                    if(NULL == tree_root)
                    {
                        fprintf(stdout, "No tree to print!\n");
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
                        fprintf(stdout, "No tree to lookup!\n");
                    }
                    else
                    {
                        fprintf(stdout, "Insert address for which to retrieve the next hop:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%s\n", lookupPrefix);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading option, try again.\n");
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
                        fprintf(stdout, "No tree to insert prefix in!\n");
                    }
                    else
                    {
                        fprintf(stdout, "Insert the new address:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%s\n", insertPrefix);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                        }

                        fprintf(stdout, "Insert the next hop associated with the new address:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%d\n", &insertNextHop);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
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
                        fprintf(stdout, "No tree to delete prefix from!\n");
                    }
                    else
                    {
                        fprintf(stdout, "Insert prefix to delete from tree:\n");
                        ret_val_fgets = fgets(char_buffer, PREFIX_SIZE, stdin);
                        if(NULL == ret_val_fgets)
                        {
                            fprintf(stdout, "Error reading input, try again.\n");
                        }
                        ret_val_sscanf = sscanf(char_buffer, "%s\n", deletePrefix);
                        if(ret_val_sscanf != 1)
                        {
                            fprintf(stdout, "Error reading option, try again.\n");
                        }

                        tree_root = DeletePrefix(tree_root, deletePrefix);

                        fprintf(stdout, "Delete operation completed!\n");
                    }
                    break;
                }
                case 6:
                {
                    fprintf(stdout, "This functionality is not implemented yet.\n");
                    break;
                }
                case 7:
                {
                    fprintf(stdout, "This functionality is not implemented yet.\n");
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

        fclose(fp);

    exit(EXIT_SUCCESS);
}
