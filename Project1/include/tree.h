#ifndef _TREE_H_
#define _TREE_H_

#include "defs.h"
#include "../include/table.h"

#ifndef LEFT
#define LEFT 0
#endif

#ifndef RIGHT
#define RIGHT 1
#endif

typedef struct treeNode_ TreeNode;

/* Support functions */

// Constructors / initializers

/* newTreeNode
 * Description: Allocates memory for a new binary tree node element and initializes its fields
 * Arguments: void
 * Return value: TreeNode * - pointer to the alocated TreeNode element
*/
TreeNode * newTreeNode(void);

// Getters

/* TreeNode_getNextHop
 * Description: getter for the nextHop field of a TreeNode
 * Arguments: TreeNode *treeNode - pointer to the node from which we want the value of nextHop
 * Return value: int - the next hop in the tree node
*/
int TreeNode_getNextHop(TreeNode *treeNode);

/* TreeNode_getZero
 * Description: getter for the 'zero' field of a TreeNode (a pointer to the "left" child)
 * Arguments: TreeNode *treeNode - pointer to the node from which we want the pointer to its "left" child
 * Return value: TreeNode * - pointer to the "left" child of the parent we called the function on
*/
TreeNode * TreeNode_getZero(TreeNode *treeNode);

/* TreeNode_getOne
 * Description: getter for the 'one' field of a TreeNode (a pointer to the "right" child)
 * Arguments: TreeNode *treeNode - pointer to the node from which we want the pointer to its "right" child
 * Return value: TreeNode * - pointer to the "right" child of the parent we called the function on
*/
TreeNode * TreeNode_getOne(TreeNode *treeNode);

// Setters

/* TreeNode_setNextHop
 * Description: setter for the nextHop field of a TreeNode
 * Arguments: TreeNode *treeNode - pointer to the node for which we want to change the value of nextHop
 * Return value: void
*/
void TreeNode_setNextHop(TreeNode *treeNode, int nextHop);

/* TreeNode_setZero
 * Description: setter for the zero field of a TreeNode (a pointer to the "left" child)
 * Arguments: TreeNode *treeNode - pointer to the node for which we want to change the value of zero;
 * TreeNode *nextZero - the new value for the zero field (a pointer to the new "left" child)
 * Return value: void
*/
void TreeNode_setZero(TreeNode *treeNode, TreeNode *nextZero);

/* TreeNode_setOne
 * Description: setter for the one field of a TreeNode (a pointer to the "right" child)
 * Arguments: TreeNode *treeNode - pointer to the node for which we want to change the value of one;
 * TreeNode *nextOne - the new value for the one field (a pointer to the new "right" child)
 * Return value: void
*/
void TreeNode_setOne(TreeNode *treeNode, TreeNode *nextOne);

// Destructors

/* freeTree
 * Description: Frees the memory alocated for a tree.
 * Starts from the first entry (root) of the tree and frees all children.
 * Arguments: TreeNode *tree_root - pointer to the first node (root) of the tree.
 * Return value: void
*/
void freeTree(TreeNode *tree_root);

/* PrefixTree
 * Description: reads a prefix table from memory and returns a prefix tree representation of that table;
 * Arguments: TableEntry *table_head - pointer to the first element (row) of the prefix table
 * Return value: TreeNode * - pointer to the root of the prefix tree created from the table.
*/
TreeNode * PrefixTree(TableEntry *table_head);

//Recusive function, needs to be called with the tree_root and an empty string
void PrintTable(TreeNode *tree_root, char address[PREFIX_SIZE]);
int LookUp(TreeNode *tree_root, char address[PREFIX_SIZE]);
TreeNode * InsertPrefix(TreeNode *tree_root, char address[PREFIX_SIZE], int nextHop);
TreeNode * DeletePrefix(TreeNode *tree_root, char prefix[PREFIX_SIZE]);

#endif
