#include <stdlib.h>
#include <stdio.h>

char array[10];
int i = 0;

typedef struct node {
    char data;
    struct node *left;
    struct node *right;
} node;

node *newNode(char val) {
    node *n = (node *) malloc(sizeof(node));
    n->data = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void *postOrder(node *root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        //printf("%c ", root->data);
        array[i] = root->data;
        i++;
    }
}

int main() {

    // Question 1

    node *t = newNode('A');
    t->left = newNode('B');
    t->left->right = newNode('E');
    t->left->right->left = newNode('J');
    t->left->left = newNode('D');
    t->left->left->left = newNode('H');
    t->left->left->right = newNode('I');

    t->right = newNode('C');
    t->right->left = newNode('F');
    t->right->right = newNode('G');
    t->right->right->left = newNode('K');

    postOrder(t);

    for (int j = 0; j < 11;j++){
        printf("%c ",array[j]);
    }

}

