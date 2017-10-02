#ifndef _TREE_H_
#define _TREE_H_
#include "defs.h"
#include "../include/table.h"

// TODO: Document all the functions in this header file.

typedef struct treeNode_ TreeNode;

/* Support functions */

// Constructor / initializer
TreeNode * newTreeNode(void);

// Getters
int TreeNode_getNextHop(TreeNode *treeNode);
TreeNode * TreeNode_getZero(TreeNode *treeNode);
TreeNode * TreeNode_getOne(TreeNode *treeNode);

// Setters
void TreeNode_setNextHop(TreeNode *treeNode, int nextHop);
void TreeNode_setZero(TreeNode *treeNode, TreeNode *nextZero);
void TreeNode_setOne(TreeNode *treeNode, TreeNode *nextOne);

// Destructor
void freeTree(TreeNode *tree_root);

/* Basic functionality functions */
TreeNode * PrefixTree(TableEntry *tree_root);
void PrintTable(TreeNode *tree_root, char address[PREFIX_SIZE]);
int LookUp(TreeNode *tree_root, char address[PREFIX_SIZE]);
TreeNode * InsertPrefix(TreeNode *tree_root, char address[PREFIX_SIZE], int nextHop);
TreeNode * DeletePrefix(TreeNode *tree_root, char prefix[PREFIX_SIZE]);

#endif
