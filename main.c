#include <stdlib.h>
#include <stdio.h>

typedef struct node{
    char data;
    struct node *left;
    struct node *right;
}node;

node* newNode(char val){
    node *n = (node*)malloc(sizeof(node));
    n->data = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

char *postOrder(node *root){
    if (root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%c",root->data);
    }
}

node* makeTree(char arr[],int i, int n){
    node *root = NULL;
    // Base case for recursion
    if (i < n)
    {
        root = newNode(arr[i]);
        // insert left child
        root->left = makeTree(arr, 2 * i + 1, n);
        // insert right child
        root->right = makeTree(arr, 2 * i + 2, n);
    }
    return root;
}

void printLevelOrder(struct node* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i);
}

/* Print nodes at a current level */
void printCurrentLevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        printf("%c ", root->data);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1);
        printCurrentLevel(root->right, level - 1);
    }
}
int height(struct node* node)
{
    if (node == NULL)
        return 0;
    else {

        int l = height(node->left);
        int r = height(node->right);

        if (l > r)
            return (l + 1);
        else
            return (r + 1);
    }
}

int main(){
    char tree[20] = {'A','B','C','D','E','F','G','H','I','J','0','0','K','0'};
    node *t;
    t = makeTree(tree,0,14);

    postOrder(t);
    //printLevelOrder(t);



}