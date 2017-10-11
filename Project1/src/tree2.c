#ifndef _TREE2_H_
#include "../include/tree2.h"
#endif

struct treeNode_2_
{
    int nextHop;
    TreeNode_2 *zero;
    TreeNode_2 *one;
    TreeNode_2 *two;
    TreeNode_2 *three;
};

TreeNode_2 * newTreeNode_2(void)
{
    TreeNode_2 *tree_node_2 = NULL;

        tree_node_2 = (TreeNode_2*)malloc(sizeof(TreeNode_2));
        tree_node_2->zero = NULL;
        tree_node_2->one = NULL;
        tree_node_2->two = NULL;
        tree_node_2->three = NULL;
        tree_node_2->nextHop = NO_HOP;

    return tree_node_2;
}

int TreeNode_2_getNextHop(TreeNode_2 *treeNode)
{
    return treeNode->nextHop;
}

TreeNode_2 * TreeNode_2_getZero(TreeNode_2 *treeNode)
{
    return treeNode->zero;
}

TreeNode_2 * TreeNode_2_getOne(TreeNode_2 *treeNode)
{
    return treeNode->one;
}

TreeNode_2 * TreeNode_2_getTwo(TreeNode_2 *treeNode)
{
    return treeNode->two;
}

TreeNode_2 * TreeNode_2_getThree(TreeNode_2 *treeNode)
{
    return treeNode->three;
}

void TreeNode_2_setNextHop(TreeNode_2 *treeNode, int nextHop)
{
    treeNode->nextHop = nextHop;

    return;
}

void TreeNode_2_setZero(TreeNode_2 *treeNode, TreeNode_2 *nextZero)
{
    treeNode->zero = nextZero;

    return;
}

void TreeNode_2_setOne(TreeNode_2 *treeNode, TreeNode_2 *nextOne)
{
    treeNode->one = nextOne;

    return;
}

void TreeNode_2_setTwo(TreeNode_2 *treeNode, TreeNode_2 *nextTwo)
{
    treeNode->two = nextTwo;

    return;
}

void TreeNode_2_setThree(TreeNode_2 *treeNode, TreeNode_2 *nextThree)
{
    treeNode->three = nextThree;

    return;
}

void freeTree2(TreeNode_2 *tree_root_2)
{
    if(NULL == tree_root_2)
    {
        return;
    }

    freeTree2(tree_root_2->zero);
    freeTree2(tree_root_2->one);
    freeTree2(tree_root_2->two);
    freeTree2(tree_root_2->three);

    free(tree_root_2);

    return;
}

TreeNode_2 * BinaryToTwoBit(TreeNode *tree_root)
{
    TreeNode_2 *tree_root2 = NULL;
    char *address = NULL;

        address = malloc(PREFIX_SIZE * sizeof(char));
        memset(address, 0, PREFIX_SIZE * sizeof(char));

        tree_root2 = newTreeNode_2();

        tree_root2->nextHop = TreeNode_getNextHop(tree_root);

        BinaryToTwoBit_recursive(tree_root, &tree_root2, &address);

        free(address);

    return tree_root2;
}

void BinaryToTwoBit_recursive(TreeNode *tree_root, TreeNode_2 **tree_root_2, char **address)
{
    unsigned long int address_legth = 0;
    char *new_address = NULL;
    bool add_to_tree2 = false;

        // traverse left then right to the bottom
        if(NULL == tree_root)
        {
            return;
        }

        if(TreeNode_getZero(tree_root) != NULL)
        {
            strncat(*address, "0", 1);
        }
        BinaryToTwoBit_recursive(TreeNode_getZero(tree_root), tree_root_2, address);
        if(TreeNode_getOne(tree_root) != NULL)
        {
            strncat(*address, "1", 1);
        }
        BinaryToTwoBit_recursive(TreeNode_getOne(tree_root), tree_root_2, address);

        // do stuff here for each node, going from bottom to top, left to right

        // get the length of the address
        address_legth = strnlen(*address, PREFIX_SIZE);
        // we only need to build paths for nodes that have a next hop
        if(NO_HOP != TreeNode_getNextHop(tree_root))
        {
            // allocate memory for a new address string
            new_address = malloc(PREFIX_SIZE * sizeof(char));
            memset(new_address, 0, PREFIX_SIZE * sizeof(char));

            // check if number of digits of the address is even or odd
            if(0 == (address_legth % 2)) // even
            {
                // check children to see if the node is not redundant
                add_to_tree2 = true;
                if((TreeNode_getZero(tree_root) != NULL) && (TreeNode_getOne(tree_root) != NULL))
                {
                    if((TreeNode_getNextHop(TreeNode_getZero(tree_root)) != NO_HOP) && (TreeNode_getNextHop(TreeNode_getOne(tree_root)) != NO_HOP))
                    {
                        add_to_tree2 = false;
                    }
                }

                // for even nodes, we simply add them as long as they are not redundant
                if(true == add_to_tree2)
                {
                    strncpy(new_address, *address, PREFIX_SIZE);
                    TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));
                }
            }
            else // odd
            {
                // for odd nodes, the resulting even node(s) for the 2 bit tree depend on the children
                if((TreeNode_getZero(tree_root) == NULL) && (TreeNode_getOne(tree_root) == NULL)) // leaf
                {
                    // add xxx0 to tree
                    strncpy(new_address, *address, PREFIX_SIZE);
                    strncat(new_address, "0", 1);
                    TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));

                    //add xxx1 to tree
                    strncpy(new_address, *address, PREFIX_SIZE);
                    strncat(new_address, "1", 1);
                    TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));
                }
                else if((TreeNode_getZero(tree_root) == NULL) && (TreeNode_getOne(tree_root) != NULL)) // right child is not NULL
                {
                    // check if right child has next hop
                    if(TreeNode_getNextHop(TreeNode_getOne(tree_root)) == NO_HOP) // add prefix as xxx1
                    {
                        strncpy(new_address, *address, PREFIX_SIZE);
                        strncat(new_address, "1", 1);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));
                    }
                    else
                    {
                        strncpy(new_address, *address, PREFIX_SIZE); // add prefix as xxx0
                        strncat(new_address, "0", 1);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));
                    }
                }
                else if((TreeNode_getZero(tree_root) != NULL) && (TreeNode_getOne(tree_root) == NULL)) // left child is not NULL
                {
                    // check if left child has next hop
                    if(TreeNode_getNextHop(TreeNode_getZero(tree_root)) == NO_HOP) // add prefix as xxx0
                    {
                        strncpy(new_address, *address, PREFIX_SIZE);
                        strncat(new_address, "0", 1);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));
                    }
                    else
                    {
                        strncpy(new_address, *address, PREFIX_SIZE); // add prefix as xxx1
                        strncat(new_address, "1", 1);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));
                    }
                }
                else if((TreeNode_getZero(tree_root) != NULL) && (TreeNode_getOne(tree_root) != NULL)) // both children not NULL
                {
                    if((TreeNode_getNextHop(TreeNode_getZero(tree_root)) != NO_HOP) && (TreeNode_getNextHop(TreeNode_getOne(tree_root)) != NO_HOP)) // both children have hop
                    {
                        // do nothing
                    }
                    else if((TreeNode_getNextHop(TreeNode_getZero(tree_root)) == NO_HOP) && (TreeNode_getNextHop(TreeNode_getOne(tree_root)) != NO_HOP)) //right child has hop
                    {
                        // add prefix as xxx0
                        strncpy(new_address, *address, PREFIX_SIZE);
                        strncat(new_address, "0", PREFIX_SIZE);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));

                    }
                    else if((TreeNode_getNextHop(TreeNode_getZero(tree_root)) != NO_HOP) && (TreeNode_getNextHop(TreeNode_getOne(tree_root)) == NO_HOP)) //left child has hop
                    {
                        // add prefix as xxx1
                        strncpy(new_address, *address, PREFIX_SIZE);
                        strncat(new_address, "1", PREFIX_SIZE);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));

                    }
                    else // no child has hop
                    {
                        // add xxx0 to tree
                        strncpy(new_address, *address, PREFIX_SIZE);
                        strncat(new_address, "0", PREFIX_SIZE);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));

                        //add xxx1 to tree
                        strncpy(new_address, *address, PREFIX_SIZE);
                        strncat(new_address, "1", PREFIX_SIZE);
                        TreeNode_2_buildNode(tree_root_2, new_address, TreeNode_getNextHop(tree_root));

                    }
                }
            }
            // free the memory allocated for the new_address string
            free(new_address);
        }

        // go "up" one level by deleting the last digit of the address
        if(address_legth > 0)
        {
            (*address)[address_legth - 1] = '\0';
        }

    return;
}

void TreeNode_2_buildNode(TreeNode_2 **tree_root_2, char two_bit_address[PREFIX_SIZE], int nextHop)
{
    unsigned long int i = 0;
    unsigned long int address_legth = 0;
    unsigned long int even_odd = 0;
    unsigned long int for_control = 0;
    TreeNode_2 **aux = NULL;

        aux = tree_root_2;

        address_legth = strnlen(two_bit_address, PREFIX_SIZE);
        even_odd = address_legth/2 + 1;
        if((even_odd % 2) == 0) // even
        {
            for_control = even_odd + 1;
        }
        else
        {
            for_control = even_odd;
        }

        for(i = 0; i < for_control; i += 2)
        {
            if((two_bit_address[i] == '0') && (two_bit_address[i+1] == '0'))
            {
                if(((*(aux))->zero) == NULL)
                {
                    (*(aux))->zero = newTreeNode_2();
                }
                aux = &((*(aux))->zero);
            }
            else if((two_bit_address[i] == '0') && (two_bit_address[i+1] == '1'))
            {
                if(((*(aux))->one) == NULL)
                {
                    (*(aux))->one = newTreeNode_2();
                }
                aux = &((*(aux))->one);
            }
            else if((two_bit_address[i] == '1') && (two_bit_address[i+1] == '0'))
            {
                if(((*(aux))->two) == NULL)
                {
                    (*(aux))->two = newTreeNode_2();
                }
                aux = &((*(aux))->two);
            }
            else if((two_bit_address[i] == '1') && (two_bit_address[i+1] == '1'))
            {
                if(((*(aux))->three) == NULL)
                {
                    (*(aux))->three = newTreeNode_2();
                }
                aux = &((*(aux))->three);
            }
        }

        TreeNode_2_setNextHop(*aux, nextHop);

    return;
}

void PrintTableEven(TreeNode_2 * tree_root_2, char address[PREFIX_SIZE])
{
    if(NO_HOP != tree_root_2->nextHop)
    {
        //Special case for the tree root
        if('\0' == address[0])
        {
            fprintf(stdout, "Prefix: e | Next hop: %d\n", tree_root_2->nextHop);
        }
        else
        {
            fprintf(stdout, "Prefix: %s | Next hop: %d\n", address, tree_root_2->nextHop);
        }
    }

    if(NULL != tree_root_2->zero)
    {
        PrintTableEven(tree_root_2->zero, strncat(address, "00", 2));
    }
    if(NULL != tree_root_2->one)
    {
        PrintTableEven(tree_root_2->one, strncat(address, "01", 2));
    }
    if(NULL != tree_root_2->two)
    {
        PrintTableEven(tree_root_2->two, strncat(address, "10", 2));
    }
    if(NULL != tree_root_2->three)
    {
        PrintTableEven(tree_root_2->three, strncat(address, "11", 2));
    }

    if(((long int)strnlen(address, PREFIX_SIZE) - 2) >= 0)
    {
        int real_length = strnlen(address, PREFIX_SIZE);
        address[real_length-2] = '\0';
        address[real_length-1] = '\0';
    }

    return;
}
