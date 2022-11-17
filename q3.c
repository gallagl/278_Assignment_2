#include <stdio.h>
#include <stdlib.h>


void insertAVL (Key k, void *v, Tree *t)
// Add new data item to tree.  Use two data components - key and actual data -
// to create new node and insert node in appropriate place.
{
    // Check for mistakes, including verification of tree type
    if ((t == NULL) || (t->tt != AVL))	return;
    //printf("Insert %d into AVL\n", k);
    // Check if tree empty - if so, insert first node
    if (t->root == NULL) {
        Node *n = initNode(k, v);
        n->height = 0;
        t->root = n;
    } else	{
        t->root = insertNodeAVL(k, v, t->root);
    }
    return;
}//insert()

Node* insertNodeAVL(Key k, void *v, Node *root)
// Build new node and insert into (non-empty) tree. Check if insertion has
// created imbalance and rebalance if necessary.
{
    if (root==NULL) {
        Node *n = initNode(k, v);
        n->height = 0;
        return n;
    }
    if (k < root->key) {
        root->leftChild = insertNodeAVL(k, v, root->leftChild);
        root->height = calcHeight(root);
    } else if (k > root->key) {
        root->rightChild = insertNodeAVL(k, v, root->rightChild);
        root->height = calcHeight(root);
    }
    // Note - ignored equal case - should not occur.
    return rebalance(root);
}//insertNode()
