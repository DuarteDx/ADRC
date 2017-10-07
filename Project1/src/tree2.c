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

void TreeNode_2_setNextHop(TreeNode_2 *treeNode, int nextHop)
{
    treeNode->nextHop = nextHop;

    return;
}

TreeNode_2* newTreeNode_2(void)
{
  TreeNode_2 *tree_node_2 = NULL;

    tree_node_2 = (TreeNode_2*)malloc(sizeof(TreeNode_2));
    TreeNode_2_setZero(tree_node_2, NULL);
    TreeNode_2_setOne(tree_node_2, NULL);
    TreeNode_2_setTwo(tree_node_2, NULL);
    TreeNode_2_setThree(tree_node_2, NULL);
    TreeNode_2_setNextHop(tree_node_2, -1);

    return tree_node_2;
}

//Extra functions
void BinaryToTwoBit_recursive(TreeNode *tree_root, TreeNode_2 **tree_root_2)
{
    TreeNode *son0 = NULL;
    TreeNode *son1 = NULL;
    TreeNode *grandson00 = NULL;
    TreeNode *grandson01 = NULL;
    TreeNode *grandson10 = NULL;
    TreeNode *grandson11 = NULL;

        if(NULL == tree_root)
        {
            return;
        }

        //TODO: encapsulate all of this in an if checking for NO_HOP in tree root

        son0 = TreeNode_getZero(tree_root);
        son1 = TreeNode_getOne(tree_root);

            if(NULL != son0)
            {
                grandson00 = TreeNode_getZero(son0);
                grandson01 = TreeNode_getOne(son0);

                if(NO_HOP != TreeNode_getNextHop(son0))
                {
                    if((NULL != grandson00) && (NULL != grandson01))
                    {
                        if((NO_HOP != TreeNode_getNextHop(grandson00)) && (NO_HOP != TreeNode_getNextHop(grandson01)))
                        {
                            (*tree_root_2)->zero = newTreeNode_2();
                            (*tree_root_2)->zero->nextHop = TreeNode_getNextHop(grandson00);
                            (*tree_root_2)->one = newTreeNode_2();
                            (*tree_root_2)->one->nextHop = TreeNode_getNextHop(grandson01);

                            // TODO: are these ifs necessary? I think not, if first arg is NULL, recursion should return anyway.
                            if(NULL != TreeNode_getZero(grandson00))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getZero(grandson00), &((*tree_root_2)->zero));
                            }
                            else if(NULL != TreeNode_getOne(grandson00))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getOne(grandson00), &((*tree_root_2)->zero));
                            }
                            else if(NULL != TreeNode_getZero(grandson01))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getZero(grandson01), &((*tree_root_2)->one));
                            }
                            else if(NULL != TreeNode_getOne(grandson01))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getOne(grandson01), &((*tree_root_2)->one));
                            }
                        }
                        else if((NO_HOP != TreeNode_getNextHop(grandson00)) && (NO_HOP == TreeNode_getNextHop(grandson01)))
                        {
                            (*tree_root_2)->zero = newTreeNode_2();
                            (*tree_root_2)->zero->nextHop = TreeNode_getNextHop(grandson00);
                            (*tree_root_2)->one = newTreeNode_2();
                            (*tree_root_2)->one->nextHop = TreeNode_getNextHop(son0);

                            // TODO: are these ifs necessary? I think not, if first arg is NULL, recursion should return anyway.
                            if(NULL != TreeNode_getZero(grandson00))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getZero(grandson00), &((*tree_root_2)->zero));
                            }
                            else if(NULL != TreeNode_getOne(grandson00))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getOne(grandson00), &((*tree_root_2)->zero));
                            }
                            else if(NULL != TreeNode_getZero(grandson01))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getZero(grandson01), &((*tree_root_2)->one));
                            }
                            else if(NULL != TreeNode_getOne(grandson01))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getOne(grandson01), &((*tree_root_2)->one));
                            }
                        }
                        else if((NO_HOP == TreeNode_getNextHop(grandson00)) && (NO_HOP != TreeNode_getNextHop(grandson01)))
                        {
                            // only grandson01 has next hop
                        }
                        else // Both grandsons NO_HOP
                        {
                            // code
                        }
                    }
                    else if((NULL != grandson00) && (NULL == grandson01))
                    {
                        if(NO_HOP != TreeNode_getNextHop(grandson00))
                        {
                            // grandson00 has nexthop
                            (*tree_root_2)->zero = newTreeNode_2();
                            (*tree_root_2)->zero->nextHop = TreeNode_getNextHop(grandson00);
                            (*tree_root_2)->one = newTreeNode_2();
                            (*tree_root_2)->one->nextHop = TreeNode_getNextHop(son0);

                            if(NULL != TreeNode_getZero(grandson00))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getZero(grandson00), &((*tree_root_2)->zero));
                            }
                            else if(NULL != TreeNode_getOne(grandson00))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getOne(grandson00), &((*tree_root_2)->zero));
                            }
                        }
                        else
                        {
                            // No hop
                        }
                    }
                    else if((NULL == grandson00) && (NULL != grandson01))
                    {
                        if(NO_HOP != TreeNode_getNextHop(grandson01))
                        {
                            // grandson01 has nexthop
                            (*tree_root_2)->zero = newTreeNode_2();
                            (*tree_root_2)->zero->nextHop = TreeNode_getNextHop(son0);
                            (*tree_root_2)->one = newTreeNode_2();
                            (*tree_root_2)->one->nextHop = TreeNode_getNextHop(grandson01);

                            if(NULL != TreeNode_getZero(grandson01))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getZero(grandson01), &((*tree_root_2)->one));
                            }
                            else if(NULL != TreeNode_getOne(grandson01))
                            {
                                BinaryToTwoBit_recursive(TreeNode_getOne(grandson01), &((*tree_root_2)->one));
                            }
                        }
                        else
                        {
                            // No hop
                        }
                    }
                    else // both grandsons NULL
                    {
                        (*tree_root_2)->zero = newTreeNode_2();
                        (*tree_root_2)->zero->nextHop = TreeNode_getNextHop(son0);
                    }

                }
                else // son0 NO_HOP
                {
                    if((NULL != grandson00) && (NULL != grandson01))
                    {
                        if((NO_HOP != TreeNode_getNextHop(grandson00)) && (NO_HOP != TreeNode_getNextHop(grandson01)))
                        {
                            // both have nexthop
                        }
                        else if((NO_HOP != TreeNode_getNextHop(grandson00)) && (NO_HOP == TreeNode_getNextHop(grandson01)))
                        {
                            // only grandson00 has nexthop
                        }
                        else if((NO_HOP == TreeNode_getNextHop(grandson00)) && (NO_HOP != TreeNode_getNextHop(grandson01)))
                        {
                            // only grandson01 has next hop
                        }
                        else // Both grandsons NO_HOP
                        {
                            // code
                        }
                    }
                    else if((NULL != grandson00) && (NULL == grandson01))
                    {
                        if(NO_HOP != TreeNode_getNextHop(grandson00))
                        {
                            // grandson00 has nexthop
                        }
                        else
                        {
                            // No hop
                        }
                    }
                    else if((NULL == grandson00) && (NULL != grandson01))
                    {
                        if(NO_HOP != TreeNode_getNextHop(grandson01))
                        {
                            // grandson01 has nexthop
                        }
                        else
                        {
                            // No hop
                        }
                    }
                    else // both grandsons NULL
                    {
                        // what happens?
                    }
                }
            }
            else // son0 is NULL
            {
                // what happens?
            }


            if(NULL != son1)
            {
                grandson10 = TreeNode_getZero(son1);
                grandson11 = TreeNode_getOne(son1);

                if(NO_HOP != TreeNode_getNextHop(son1))
                {
                    // code
                }
                else
                {

                }
            }

    return;
}

TreeNode_2* BinaryToTwoBit_(TreeNode *tree_root)
{
    TreeNode_2* tree_root2 = NULL;

        tree_root2 = newTreeNode_2();

        tree_root2->nextHop = TreeNode_getNextHop(tree_root);

        BinaryToTwoBit_recursive(tree_root, &tree_root2);

    return tree_root2;
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

    //delete the last chars from the path string
    if(((long int)strnlen(address, PREFIX_SIZE) - 1) >= 0)
    {
        address[strnlen(address, PREFIX_SIZE) - 1] = '\0';
    }
    if(((long int)strnlen(address, PREFIX_SIZE) - 2) >= 0)
    {
        address[strnlen(address, PREFIX_SIZE) - 2] = '\0';
    }

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
