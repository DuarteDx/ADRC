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

//Basic functions
TreeNode* PrefixTree(TableEntry *table_head){

    TreeNode *tree_root = NULL;
    TableEntry *aux = NULL;
    int i = 0;

        for(aux = table_head; aux != NULL; aux = TableEntry_getNextTableEntry(aux)) {
            if(strncmp(TableEntry_getPrefix(aux), "e", PREFIX_SIZE) == 0){
            }
        }

    return tree_root;
}

void PrintTable(){

}

int LookUp(){

  return 0;
}

int DeletePrefix(){

  return 0;
}

//Extra functions
int BinaryToTwoBit(){

  return 0;
}

void PrintTableEven(){

}
