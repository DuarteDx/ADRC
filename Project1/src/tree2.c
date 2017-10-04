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
TreeNode_2* BinaryToTwoBit(TreeNode *tree_root){

    TreeNode* tree_aux = tree_root;
    char* adress = (char*)malloc(PREFIX_SIZE*sizeof(char));
    int i;
    for(i = 0; i<PREFIX_SIZE; i++)
    {
        adress[i] = 'x';
    }
    TreeNode_2* tree_root2 = newTreeNode_2();
    TreeNode_2* tree2_aux = tree_root2;

    tree_root2->nextHop = TreeNode_getNextHop(tree_root);

    Recursive2BitPrefixTree(tree_aux, tree2_aux, adress);

    return tree_root2;
}

//Iterates over all of the PrefixTree
void Recursive2BitPrefixTree(TreeNode *tree_node, TreeNode_2* tree_node2, char* adress)
{
    if(-1 != TreeNode_getNextHop(tree_node))
    {
        Insert2BitPrefix(tree_node2, adress, TreeNode_getNextHop(tree_node));
    }

    if(NULL != TreeNode_getZero(tree_node))
    {
        if(adress[0]=='x')
        {
            adress[0] = '0';
        }
        for(int i = 0; adress[i] == 'x'; i+=1)
        {
            if(adress[i+1] == 'x')
            {
                adress[i+1] = '0';
            }
        }
        Recursive2BitPrefixTree(TreeNode_getZero(tree_node), tree_node2, adress);
        for(int i = 0; adress[i] == 'x'; i+=1)
        {
            if(adress[i+1] == 'x')
            {
                adress[i] = 'x';
            }
        }

    }

    if(TreeNode_getNextHop(tree_node) != -1)
    {
        Insert2BitPrefix(tree_node2, adress, TreeNode_getNextHop(tree_node));
    }

    if(NULL != TreeNode_getOne(tree_node))
    {
        if(adress[0]=='x')
        {
            adress[0] = '0';
        }
        for(int i = 0; adress[i] == 'x'; i += 1)
        {
            if(adress[i+1] == 'x')
            {
                adress[i+1] = '0';
            }
        }
        Recursive2BitPrefixTree(TreeNode_getOne(tree_node), tree_node2, adress);
        for(int i = 0; adress[i] == 'x'; i += 1)
        {
            if(adress[i+1] == 'x')
            {
                adress[i] = 'x';
            }
        }
    }

    return;
}

//Inserts a NextHop to a 2BitPrefixTree by knowing the address

void Insert2BitPrefix(TreeNode_2* tree_node2, char* address, int nextHop)
{
  TreeNode_2* tree_aux = tree_node2;
  for(int i = 0; address[i] != 'x'; i++)
  {
    if(address[i] == '0')
    {
      if(tree_aux->zero == NULL){
        tree_aux->zero = newTreeNode_2();
      }
      if(tree_aux->one == NULL){
        tree_aux->one = newTreeNode_2();
      }
      if(address[i+1] == 'x'){
        if(tree_aux->zero->nextHop == -1){tree_aux->zero->nextHop = nextHop;}
        else if(tree_aux->one->nextHop == -1){tree_aux->one->nextHop = nextHop;}
      }
      if(address[i+1] == '0'){tree_aux = tree_aux->zero;}
      if(address[i+1] == '1'){tree_aux = tree_aux->one;}
    }

    if(address[i] == '1')
    {
      if(tree_aux->two == NULL){
        tree_aux->two = newTreeNode_2();
      }
      if(tree_aux->three == NULL){
        tree_aux->three = newTreeNode_2();
      }
      if(address[i+1] == 'x'){
        if(tree_aux->two->nextHop == -1){tree_aux->two->nextHop = nextHop;}
        else if(tree_aux->three->nextHop == -1){tree_aux->three->nextHop = nextHop;}
      }
      if(address[i+1] == '0'){tree_aux = tree_aux->two;}
      if(address[i+1] == '1'){tree_aux = tree_aux->three;}
    }
  }
}

void PrintTableEven(TreeNode_2 *tree_node2, char address[512]){

    if(-1 != tree_node2->nextHop)
    {
        if('\0' == address[0])
        {
            fprintf(stdout, "e   %d\n", tree_node2->nextHop);
        }
        else
        {
            fprintf(stdout, "Prefix: %s | Next hop: %d\n", address, tree_node2->nextHop);
        }
    }

    if(NULL != tree_node2->zero)
    {
        PrintTableEven(tree_node2->zero, strncat(address, "00", 2));
    }
    if(NULL != tree_node2->one)
    {
        PrintTableEven(tree_node2->one, strncat(address, "01", 2));
    }
    if(NULL != tree_node2->two)
    {
        PrintTableEven(tree_node2->two, strncat(address, "10", 2));
    }
    if(NULL != tree_node2->three)
    {
        PrintTableEven(tree_node2->three, strncat(address, "11", 2));
    }

    //delete the last char from the path string
    if(((long int)strnlen(address, 512) - 2) >= 0)
    {
        address[strnlen(address, 512) - 2] = '\0';
    }

    return;
}
