#include "../include/tree.h"

struct treeNode_
{
    int nextHop;
    TreeNode *zero;
    TreeNode *one;
};

struct treeNode_2_
{
    int nextHop;
    TreeNode_2 *zero;
    TreeNode_2 *one;
    TreeNode_2 *two;
    TreeNode_2 *three;
};


int TreeNode_getNextHop(TreeNode *treeNode)
{
    return treeNode->nextHop;
}

TreeNode* TreeNode_getZero(TreeNode *treeNode)
{
    return treeNode->zero;
}

TreeNode* TreeNode_getOne(TreeNode *treeNode)
{
    return treeNode->one;
}

void TreeNode_setZero(TreeNode *treeNode, TreeNode *nextZero)
{
    treeNode->zero = nextZero;

    return;
}

void TreeNode_setOne(TreeNode *treeNode, TreeNode *nextOne)
{
    treeNode->one = nextOne;

    return;
}

void TreeNode_setNextHop(TreeNode *treeNode, int nextHop)
{
    treeNode->nextHop = nextHop;

    return;
}

TreeNode* newTreeNode(void)
{
    TreeNode *tree_node = NULL;

        tree_node = (TreeNode*)malloc(sizeof(TreeNode));
        TreeNode_setZero(tree_node, NULL);
        TreeNode_setOne(tree_node, NULL);
        TreeNode_setNextHop(tree_node, -1);

    return tree_node;
}

//Basic functions
TreeNode* PrefixTree(TableEntry *table_head){

    TreeNode *tree_root = NULL;
    TreeNode *tree_aux = NULL;
    TableEntry *aux = NULL;
    unsigned long int i = 0;
    char prefix[PREFIX_SIZE];
    int nextHop = 0;

        //If the table is not empty we create a tree_root, otherwise we keep it NULL
        if (table_head != NULL)
        {
            tree_root = newTreeNode();
        }

        for(aux = table_head; aux != NULL; aux = TableEntry_getNextTableEntry(aux))
        {

            //If the prefix is e (the rest) we update the tree_root next_hop
            if(strncmp(TableEntry_getPrefix(aux), "e", PREFIX_SIZE) == 0){
                tree_root->nextHop = TableEntry_getNextHop(aux);
            }
            //If the prefix is not "e" we create as many nodes as we need to match the prefix
            else
            {
                strncpy(prefix, TableEntry_getPrefix(aux), PREFIX_SIZE);
                nextHop = TableEntry_getNextHop(aux);

                //Start tree_aux as tree_root
                tree_aux = tree_root;

                for(i = 0; i < strnlen(prefix, PREFIX_SIZE); i++)
                {
                    if(prefix[i] == '0')
                    {
                        if(tree_aux->zero == NULL)
                        {
                            //Create a new node and add it
                            tree_aux->zero = newTreeNode();
                        }

                        //Get the next node
                        tree_aux = tree_aux->zero;
                    }
                    else if(prefix[i] == '1')
                    {
                        if(tree_aux->one == NULL)
                        {
                            //Create a new node and add it
                            tree_aux->one = newTreeNode();
                        }

                        //Get the next node
                        tree_aux = tree_aux->one;
                    }
                    else
                    {
                        fprintf(stdout, "Error reading prefix\n");
                    }
                }

                //Set next_hop in the last tree node
                tree_aux->nextHop = nextHop;
            }
        }

    return tree_root;
}

//Recusive function, needs to be called with the tree_root and an empty string
void PrintTable(TreeNode *tree_node, char address[PREFIX_SIZE]){

    if(tree_node->nextHop != -1)
    {
        //Special case for the tree root
        if(address[0] == '\0')
        {
            printf("e   %d\n", tree_node->nextHop);
        }
        else
        {
            printf("Prefix: %s | Next hop: %d\n", address, tree_node->nextHop);
        }
    }

    if(tree_node->zero != NULL)
    {
        PrintTable(tree_node->zero, strncat(address, "0", 1));
    }
    if(tree_node->one != NULL)
    {
        PrintTable(tree_node->one, strncat(address, "1", 1));
    }

    //delete the lasr char from the path string
    address[strlen(address) - 1] = '\0';

    return;
}

int LookUp(TreeNode *tree_root, char *address){

    int next_hop = -1;
    TreeNode *tree_aux = tree_root;
    unsigned long int i = 0;

    //Save the best next_hop if it exists on this node
    if(tree_root->nextHop != -1)
    {
        next_hop = tree_aux->nextHop;
    }

    for(i = 0; i < strnlen(address, PREFIX_SIZE); i++)
    {
        //Go to the next node
        if(address[i] == '0')
        {
            tree_aux =tree_aux->zero;
        }
        else if(address[i] == '1')
        {
            tree_aux = tree_aux->one;
        }

        //Save the best next_hop if it exists on this node
        if(tree_aux->nextHop != -1)
        {
            next_hop = tree_aux->nextHop;
        }
    }

    return next_hop;
}

TreeNode* InsertPrefix(TreeNode *tree_root, char *address, int next_hop){

    int i = 0;
    TreeNode* tree_aux = tree_root;

    //In case the user is changing the  root of the three
    if(address[0] == 'e')
    {
        tree_root->nextHop = next_hop;

        return tree_root;
    }

    for(i = 0; (size_t)i<strnlen(address, PREFIX_SIZE); i++)
    {
        //Go to the next node
        if(address[i] == '0')
        {
            if(tree_aux->zero == NULL)
            {
                //Create a new node and add it
                tree_aux->zero = newTreeNode();
            }

            //Get the next node
            tree_aux = tree_aux->zero;
        }
        else if(address[i] == '1')
        {
            if(tree_aux->one == NULL)
            {
                tree_aux->one = newTreeNode();
            }

            tree_aux = tree_aux->one;
        }
    }

    //Give a value to the inserted node next_hop
    tree_aux->nextHop = next_hop;

return tree_root;

}

TreeNode* DeletePrefix(TreeNode* tree_root, char* prefix){

    int i = 0;
    TreeNode* tree_aux = tree_root;
    TreeNode* tree_previous_aux = NULL;

    //0 for left 1 for right
    int oneZeroFlag = -1;

    for(i = 0; (size_t)i<strnlen(prefix, PREFIX_SIZE); i++)
    {
        //Go to the next node
        if(prefix[i] == '0')
        {
            if(tree_aux->zero != NULL)
            {
                tree_previous_aux = tree_aux;
                oneZeroFlag = 0;
                tree_aux = tree_aux->zero;
            }
            else
            {
                printf("Non exixting prefix. No changes were made.\n");

                break;
            }
        }
        else if(prefix[i] == '1')
        {
            if(tree_aux->one != NULL)
            {
                tree_previous_aux = tree_aux;
                oneZeroFlag = 1;
                tree_aux = tree_aux->one;
            }
            else
            {
                printf("Non exixting prefix. No changes were made.\n");

                break;
            }
        }
    }

    //Delete the next hop
    if(tree_aux->nextHop != -1)
    {
        tree_aux->nextHop = -1;
    }

    //Free memory if the node is not necessary anymore
    if(tree_aux->zero == NULL && tree_aux->one == NULL)
    {
        if(oneZeroFlag == 0)
        {
            tree_previous_aux->zero = NULL;
        }
        else if(oneZeroFlag == 1)
        {
            tree_previous_aux->one = NULL;
        }

        free(tree_aux);
    }



    return tree_root;
}

//Extra functions
int BinaryToTwoBit(){

  return 0;
}

void PrintTableEven(){

}
