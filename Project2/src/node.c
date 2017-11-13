#include "../include/node.h"

struct node_
{
    long int v;
    int relationship;
};

Node * newNode()
{
    Node *node = NULL;

        node = malloc(sizeof(Node));

    return node;
}

Node * newNodeWithInit(long int v, int relationship)
{
    Node *node = NULL;

        node = malloc(sizeof(Node));
        node->v = v;
        node->relationship = relationship;

    return node;
}
