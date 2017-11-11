#include "../include/node.h"

struct node_
{
    long int v;
    int relationship;
};

Node * newNode(long int v, int relationship)
{
    Node *node = NULL;

        node = malloc(sizeof(Node));
        node->v = v;
        node->relationship = relationship;

    return node;
}
