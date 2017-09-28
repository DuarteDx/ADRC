#include "defs.h"
#include "../include/table.h"

typedef struct treeNode_ TreeNode;
typedef struct treeNode_2_ TreeNode_2;

//Basic functions
TreeNode* PrefixTree(TableEntry *);
void PrintTable(TreeNode *, char *);
int LookUp(TreeNode *, char *);
TreeNode* InsertPrefix(TreeNode *, char *, int);
TreeNode* DeletePrefix(TreeNode *, char *);

//Extra functions for extra point
int BinaryToTwoBit();
void PrintTableEven();
