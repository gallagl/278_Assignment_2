#include <stdlib.h>
#include <stdio.h>

// Global variables for BST insert
int BST_FAIL = 0;
int BST_SUCCESS = 1;

// Global array and counter used to store breadth-first order traversal node values
char array[10];
int j = 0;

// Node definition
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

// New node definition
node *newNode(int val) {
    node *n = (node *) malloc(sizeof(node));
    n->data = val;
    n->left = NULL;
    n->right = NULL;
    return n;
}

// BST insert function
int insert(int v, node *root){
    int result = BST_FAIL;
    if (root == NULL)  {
        node *n = newNode(v);
        root = n;
        return BST_SUCCESS;
    }
    else if (v < root->data) {
        if (root->left!= NULL)
            result = insert(v, root->left);
        else {
            node *n = newNode(v);
            root->left = n;
            result = BST_SUCCESS;
        }
    } else {
        if (root->right != NULL)
            result = insert(v,root->right);
        else {
            node*n = newNode(v);
            root->right = n;
            result = BST_SUCCESS;
        }
    }
    return result;
}//insert()

// Function used to merge the two binary trees. 
void *Merge(node *r1, node *r2){
    if (r2 == NULL) return;
    Merge(r1,r2->left);
    int i = r2->data;
    insert(i,r1);
    Merge(r1,r2->right);
}

// Returns height of tree from an input node. 
int height(node* root) {
    // Get the height of the tree
    if (!root)
        return 0;
    else {
        // Find the height of both subtrees
        // and use the larger one
        int left_height = height(root->left);
        int right_height = height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

// Prints nodes at a certain level
void breathUtilFunc(node* root, int level_no) {

    if (!root)
        return;
    if (level_no == 0) {
        array[j] = root->data;
        j++;
    }
    else {
        breathUtilFunc(root->left, level_no - 1);
        breathUtilFunc(root->right, level_no - 1);
    }
}

// Uses previous two functions to output breadth-first traversal
void breathfirstprint(node* root) {
    if (!root)
        return;
    int h = height(root);
    for (int i=0; i<h; i++) {
        breathUtilFunc(root, i);
    }
    printf("\n");
}


int main() {

    // Initializing trees to be merged. 
    int tree21[4] = {3,2,5,1};
    int tree22[5] = {4,1,7,2,9};
    
    int l1 = 4;
    int l2 = 5;

    node *t1 = newNode(tree21[0]);
    node *t2 = newNode(tree22[0]);

    for (int i = 1;i < l1;i++){
        insert(tree21[i],t1);
    }
    for (int i = 1;i < l2;i++){
        insert(tree22[i],t2);
    }

    // Using merge function
    Merge(t1,t2);

    // Create array of breathfirst values
    breathfirstprint(t1);

    // Iterate through array to display answer. 
    printf("Breadth-first traversal of the merged trees:\n");
    for (int k = 0; k < 9;k++){
        printf("%d ",array[k]);
    }
}
