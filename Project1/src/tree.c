#ifndef _TREE_H_
#include "../include/tree.h"
#endif

struct treeNode_
{
    int nextHop;
    TreeNode *zero;
    TreeNode *one;
};

int TreeNode_getNextHop(TreeNode *treeNode)
{
    return treeNode->nextHop;
}

TreeNode * TreeNode_getZero(TreeNode *treeNode)
{
    return treeNode->zero;
}

TreeNode * TreeNode_getOne(TreeNode *treeNode)
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

TreeNode * newTreeNode(void)
{
    TreeNode *tree_node = NULL;

        tree_node = (TreeNode *)malloc(sizeof(TreeNode));
        TreeNode_setZero(tree_node, NULL);
        TreeNode_setOne(tree_node, NULL);
        TreeNode_setNextHop(tree_node, -1);

    return tree_node;
}

//Basic functions
TreeNode * PrefixTree(TableEntry *table_head){

    TreeNode *tree_root = NULL;
    TreeNode *tree_aux = NULL;
    TableEntry *aux = NULL;
    unsigned long int i = 0;
    char prefix[PREFIX_SIZE];
    int nextHop = 0;

        //If the table is not empty we create a tree_root, otherwise we keep it NULL
        if(NULL != table_head)
        {
            tree_root = newTreeNode();
        }

        for(aux = table_head; NULL != aux; aux = TableEntry_getNextTableEntry(aux))
        {

            //If the prefix is e (the rest) we update the tree_root next_hop
            if(strncmp(TableEntry_getPrefix(aux), "e", PREFIX_SIZE) == 0){
                tree_root->nextHop = TableEntry_getNextHop(aux);
            }
            else //If the prefix is not "e" we create as many nodes as we need to match the prefix
            {
                strncpy(prefix, TableEntry_getPrefix(aux), PREFIX_SIZE);
                nextHop = TableEntry_getNextHop(aux);

                //Start tree_aux as tree_root
                tree_aux = tree_root;

                for(i = 0; i < strnlen(prefix, PREFIX_SIZE); i += 1)
                {

                    if('0' == prefix[i])
                    {
                        if(NULL == tree_aux->zero)
                        {
                            //Create a new node and add it
                            tree_aux->zero = newTreeNode();
                        }

                        //Get the next node
                        tree_aux = tree_aux->zero;
                    }
                    else if('1' == prefix[i])
                    {
                        if(NULL == tree_aux->one)
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
void PrintTable(TreeNode *tree_head, char address[PREFIX_SIZE]){

    if(-1 != tree_head->nextHop)
    {
        //Special case for the tree root
        if('\0' == address[0])
        {
            fprintf(stdout, "e   %d\n", tree_head->nextHop);
        }
        else
        {
            fprintf(stdout, "Prefix: %s | Next hop: %d\n", address, tree_head->nextHop);
        }
    }

    if(NULL != tree_head->zero)
    {
        PrintTable(tree_head->zero, strncat(address, "0", 1));
    }
    if(NULL != tree_head->one)
    {
        PrintTable(tree_head->one, strncat(address, "1", 1));
    }

    //delete the last char from the path string
    if(((long int)strnlen(address, PREFIX_SIZE) - 1) >= 0)
    {
        address[strnlen(address, PREFIX_SIZE) - 1] = '\0';
    }

    return;
}

int LookUp(TreeNode *tree_root, char address[PREFIX_SIZE]){

    int next_hop = -1;
    TreeNode *tree_aux = NULL;
    unsigned long int i = 0;

        tree_aux = tree_root;

        //Save the best next_hop if it exists on this node
        if(-1 != tree_root->nextHop)
        {
            next_hop = tree_root->nextHop;
        }

        for(i = 0; i < strnlen(address, PREFIX_SIZE); i += 1)
        {
            //Go to the next node
            if('0' == address[i])
            {
                tree_aux = tree_aux->zero;
            }
            else if('1' == address[i])
            {
                tree_aux = tree_aux->one;
            }
            else
            {
                fprintf(stdout, "Lookup error: malformed address: contains characters other thant '0' or '1'\n");
                return -1;
            }

            //Test if we arrived at a dead end
            if(NULL == tree_aux)
            {
                //We have found a next hop
                if(next_hop != -1)
                {
                    return next_hop;
                }
                //We haven't found a next hp along the way
                else
                {
                    fprintf(stdout, "No nexthop found for this prefix\n");
                    return -1;
                }
            }

            //Save the best next_hop if it exists on this node
            if(-1 != tree_aux->nextHop)
            {
                next_hop = tree_aux->nextHop;
            }
        }

    return next_hop;
}

TreeNode * InsertPrefix(TreeNode *tree_root, char address[PREFIX_SIZE], int next_hop){

    unsigned long int i = 0;
    TreeNode *tree_aux = NULL;

        tree_aux = tree_root;

        //In case the user is changing the  root of the three
        if('e' == address[0])
        {
            tree_root->nextHop = next_hop;

            return tree_root;
        }

        for(i = 0; i < strnlen(address, PREFIX_SIZE); i += 1)
        {
            //Go to the next node
            if('0' == address[i])
            {
                if(NULL == tree_aux->zero)
                {
                    //Create a new node and add it
                    tree_aux->zero = newTreeNode();
                }

                //Get the next node
                tree_aux = tree_aux->zero;
            }
            else if('1' == address[i])
            {
                if(NULL == tree_aux->one)
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

TreeNode * DeletePrefix(TreeNode *tree_root, char prefix[PREFIX_SIZE]){

    unsigned long int i = 0;
    TreeNode *tree_aux = tree_root;
    TreeNode *delete_after = NULL;
    int delete_direction = -1;
    int save_direction = 0;
    
    for(i = 0; i < strnlen(prefix, PREFIX_SIZE); i += 1)
    {
        //Reset save direction flag
        save_direction = 0;
        
        if(tree_aux != NULL)
        {
            //Save this node if it has two children or has a next_hop
            if(((tree_aux->zero != NULL) && (tree_aux->one != NULL)) || (tree_aux->nextHop != -1))
            {
                delete_after = tree_aux;
                save_direction = 1;
            }
            
            //Go to the next node
            if('0' == prefix[i])
            {
                //Save the direction in which we have to delete from
                if(save_direction)
                {
                    delete_direction = 0;
                }
                
                tree_aux = tree_aux->zero;
            }
            else if('1' == prefix[i])
            {
                //Save the direction in which we have to delete from
                if(save_direction)
                {
                    delete_direction = 1;
                }
                
                tree_aux = tree_aux->one;
            }
            else
            {
                fprintf(stdout, "Prefix does not exist\n");
                return tree_root;
            }

        }
        else
        {
            fprintf(stdout, "Prefix does not exist\n");
            return tree_root;
        }
    }
    
    if(delete_direction == 0)
    {
        //Free nodes from delete_after downwards
        freeTree(delete_after->zero);
        delete_after->zero = NULL;
    }
    else if (delete_direction == 1)
    {
        //Free nodes from delete_after downwards
        freeTree(delete_after->one);
        delete_after->one = NULL;
    }
    
    return tree_root;
}

void freeTree(TreeNode *tree_root)
{
    if(NULL == tree_root)
    {
        return;
    }

    freeTree(TreeNode_getZero(tree_root));
    freeTree(TreeNode_getOne(tree_root));

    free(tree_root);

    return;
}
