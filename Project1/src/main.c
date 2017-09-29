#include "../include/table.h"
#include "../include/tree.h"
#include "../include/functions.h"

int main(int argc, char const *argv[]) {

    int choice = 0;
    FILE* fp = NULL;
    TableEntry* table_head = NULL;
    TreeNode* tree_root = NULL;
    bool keepRunning = true;
    char address[PREFIX_SIZE];
    int i = 0;
    char lookupPrefix[PREFIX_SIZE];
    char insertPrefix[PREFIX_SIZE];
    char deletePrefix[PREFIX_SIZE];
    int lookUpResult = 0;
    int insertNextHop = -1;

    // Check for correct number of arguments
    if(argc != 2){
        fprintf(stdout, "\nUSAGE: %s <filename>\n\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the file; abort if unsuccessful
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        fprintf(stdout, "Error opening %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    while(true == keepRunning){
        choice = showMenu();
        switch(choice){
            case 1:
            {
                table_head = readTable(fp);
                //printTable(table_head);
                tree_root = PrefixTree(table_head);
                break;
            }
            case 2:
            {
                if(NULL == tree_root){
                    fprintf(stdout, "No tree to print!\n");
                }
                PrintTable(tree_root, address);
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
                    //Need to fgets the lookup address
                    strcpy(lookupPrefix, "111");
                    lookUpResult = LookUp(tree_root, lookupPrefix);

                    printf("Next-Hop: %d\n", lookUpResult);
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
                    //Need to fgets the insertPrefix and insertNextHop
                    strcpy(insertPrefix, "0001");
                    insertNextHop = 11;

                    tree_root = InsertPrefix(tree_root, insertPrefix, insertNextHop);

                    printf("New Prefix added!\n");
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
                    //Need to fgets the deletePrefix
                    strcpy(deletePrefix, "0001");

                    tree_root = DeletePrefix(tree_root, deletePrefix);

                    printf("Delete operation completed!\n");
                }
                break;
            }
            case 6:
            {
                break;
            }
            default:
            {
                keepRunning = false;
                break;
            }
        }
    }

    freeTable(table_head);
    fclose(fp);

    exit(EXIT_SUCCESS);
}
