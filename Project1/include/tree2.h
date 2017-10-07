#ifndef _TREE2_H_
#define _TREE2_H_
#include "defs.h"
#include "tree.h"

typedef struct treeNode_2_ TreeNode_2;

// TODO: Document all the functions in this header file.

/* Support functions */

// Constructor / initializer
TreeNode_2 * newTreeNode_2(void);

// Getters TODO

// Setters
void TreeNode_2_setZero(TreeNode_2 *, TreeNode_2 *);
void TreeNode_2_setOne(TreeNode_2 *, TreeNode_2 *);
void TreeNode_2_setTwo(TreeNode_2 *, TreeNode_2 *);
void TreeNode_2_setThree(TreeNode_2 *, TreeNode_2 *);
void TreeNode_2_setNextHop(TreeNode_2 *, int);

// Destructor TODO
void freeTree2(TreeNode_2 * tree_root_2);

/* Extra functionality functions */

void Recursive2BitPrefixTree(TreeNode *,TreeNode_2 *, char *);
void Insert2BitPrefix(TreeNode_2 *root, char *, int);
TreeNode_2 * BinaryToTwoBit(TreeNode *);
void PrintTableEven();

#endif
