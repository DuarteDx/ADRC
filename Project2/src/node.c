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

int Node_getRelationship(Node* node)
{
    return node->relationship;
}


void Node_printNode(Node *node)
{
    fprintf(stdout, "Number: %7ld | relationship: %d\n", node->v, node->relationship);

    return;
}

void Node_free(Node *node)
{
    free(node);

    return;
}
