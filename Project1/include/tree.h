#include "defs.h"
#include "../include/table.h"

typedef struct treeNode * TreeNode;
typedef struct treeNode_2 * TreeNode_2;

//Basic functions
TreeNode PrefixTree(TableEntry table_head);
void PrintTable();
int LookUp();
int InsertPrefix();
int DeletePrefix();

//Extra functions for extra point
int BinaryToTwoBit();
void PrintTableEven();
