#ifndef _TREE2_H_
#define _TREE2_H_
#include "defs.h"
#include "tree.h"

typedef struct treeNode_2_ TreeNode_2;

/* Support functions */

// Constructor / initializer

/* newTreeNode_2
 * Description: Allocates memory for a new quad tree node element and initializes its fields
 * Arguments: void
 * Return value: TreeNode_2 * - pointer to the alocated TreeNode_2 element
*/
TreeNode_2 * newTreeNode_2(void);

// Getters

/* TreeNode_2_getNextHop
 * Description: getter for the nextHop field of a TreeNode_2
 * Arguments: TreeNode_2 *treeNode - pointer to the node from which we want the value of nextHop
 * Return value: int - the next hop in the tree node
*/
int TreeNode_2_getNextHop(TreeNode_2 *treeNode_2);

/* TreeNode_2_getZero
 * Description: getter for the 'zero' field of a TreeNode_2 (a pointer to the "left-most" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node from which we want the pointer to its "left-most" child
 * Return value: TreeNode * - pointer to the "left-most" child of the parent we called the function on
*/
TreeNode_2 * TreeNode_2_getZero(TreeNode_2 *treeNode_2);

/* TreeNode_2_getOne
 * Description: getter for the 'one' field of a TreeNode_2 (a pointer to the "inner-left" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node from which we want the pointer to its "inner-left" child
 * Return value: TreeNode * - pointer to the "inner-left" child of the parent we called the function on
*/
TreeNode_2 * TreeNode_2_getOne(TreeNode_2 *treeNode_2);

/* TreeNode_2_getTwo
 * Description: getter for the 'two' field of a TreeNode_2 (a pointer to the "inner-right" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node from which we want the pointer to its "inner-right" child
 * Return value: TreeNode * - pointer to the "inner-right" child of the parent we called the function on
*/
TreeNode_2 * TreeNode_2_getTwo(TreeNode_2 *treeNode_2);

/* TreeNode_getThree
 * Description: getter for the 'three' field of a TreeNode_2 (a pointer to the "right-most" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node from which we want the pointer to its "right-most" child
 * Return value: TreeNode_2 * - pointer to the "right-most" child of the parent we called the function on
*/
TreeNode_2 * TreeNode_2_getThree(TreeNode_2 *treeNode_2);

// Setters

/* TreeNode_2_setNextHop
 * Description: setter for the nextHop field of a TreeNode_2
 * Arguments: TreeNode_2 *treeNode - pointer to the node for which we want to change the value of nextHop
 * Return value: void
*/
void TreeNode_2_setNextHop(TreeNode_2 *treeNode_2, int);

/* TreeNode_2_setZero
 * Description: setter for the 'zero' field of a TreeNode_2 (a pointer to the "left-most" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node for which we want to change the value of the 'zero' field;
 * TreeNode_2 *nextZero - the new value for the 'zero' field (a pointer to the new "left-most" child)
 * Return value: void
*/
void TreeNode_2_setZero(TreeNode_2 *treeNode_2, TreeNode_2 *nextZero);

/* TreeNode_2_setOne
 * Description: setter for the 'one' field of a TreeNode_2 (a pointer to the "inner-left" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node for which we want to change the value of the 'one' field;
 * TreeNode_2 *nextOne - the new value for the 'one' field (a pointer to the new "inner-left" child)
 * Return value: void
*/
void TreeNode_2_setOne(TreeNode_2 *treeNode_2, TreeNode_2 *nextOne);

/* TreeNode_2_setTwo
 * Description: setter for the 'two' field of a TreeNode_2 (a pointer to the "inner-right" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node for which we want to change the value of the 'two' field;
 * TreeNode_2 *nextTwo - the new value for the 'two' field (a pointer to the new "inner-right" child)
 * Return value: void
*/
void TreeNode_2_setTwo(TreeNode_2 *treeNode_2, TreeNode_2 *nextTwo);

/* TreeNode_2_setThree
 * Description: setter for the 'three' field of a TreeNode_2 (a pointer to the "right-most" child)
 * Arguments: TreeNode_2 *treeNode - pointer to the node for which we want to change the value of the 'three' field;
 * TreeNode_2 *nextThree - the new value for the 'three' field (a pointer to the new "right-most" child)
 * Return value: void
*/
void TreeNode_2_setThree(TreeNode_2 *treeNode_2, TreeNode_2 *nextThree);

// Destructors

/* freeTree2
 * Description: Frees the memory alocated for a quad tree.
 * Starts from the first entry (root) of the tree and frees all children.
 * Arguments: TreeNode *tree_root_2 - pointer to the first node (root) of the quad tree.
 * Return value: void
*/
void freeTree2(TreeNode_2 *tree_root_2);

// TODO: Document all the functions in this header file.
/* Extra functionality functions */

TreeNode_2 * BinaryToTwoBit(TreeNode *tree_root);
// support for BinaryToTwoBit
void BinaryToTwoBit_recursive(TreeNode *tree_root, TreeNode_2 **tree_root_2, char** address);
void TreeNode_2_buildNode(TreeNode_2 **tree_root_2, char two_bit_address[PREFIX_SIZE], int nextHop);


void PrintTableEven();

#endif
