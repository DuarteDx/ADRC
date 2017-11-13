#ifndef _NODE_H_
#define _NODE_H_
#endif


#ifndef _DEFS_H_
#include "./defs.h"
#endif

#ifndef _LINKED_LIST_H
#include "./linked_list.h"
#endif

typedef struct node_ Node;

Node * newNode();
Node * newNodeWithInit(long int v, int relationship);
void Node_printNode(Node *node);
void Node_free(Node *node);
