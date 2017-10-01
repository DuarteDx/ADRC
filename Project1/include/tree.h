#include "defs.h"
#include "../include/table.h"

typedef struct treeNode_ TreeNode;
typedef struct treeNode_2_ TreeNode_2;

//Basic functions
TreeNode * PrefixTree(TableEntry *);
void PrintTable(TreeNode *, char address[PREFIX_SIZE]);
int LookUp(TreeNode *, char *);
TreeNode * InsertPrefix(TreeNode *, char *, int);
TreeNode * DeletePrefix(TreeNode *, char *);
void TreeNode_setZero(TreeNode *treeNode, TreeNode *nextZero);
void TreeNode_setOne(TreeNode *treeNode, TreeNode *nextOne);
void TreeNode_setNextHop(TreeNode *treeNode, int nextHop);
TreeNode * newTreeNode(void);
void freeTree(TreeNode * tree_root);

//Extra functions for extra point

void BinaryToTwoBit();
void PrintTableEven();
