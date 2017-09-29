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
                    printTable(table_head);
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
                    break;
                }
                case 4:
                {
                    break;
                }
                case 5:
                {
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
