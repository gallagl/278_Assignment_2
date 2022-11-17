#include <stdlib.h>
#include <stdio.h>

int BST_FAIL = 0;
int BST_SUCCESS = 1;

char array[10];
int j = 0;

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node;

node *newnode(int val) {
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
        printf("%d ", root->data);
    }
}

int insert(int v, node *root)
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
    int result = BST_FAIL;
    // this if statement can only be true with first root (root of whole tree)
    if (root == NULL)  {
        node *n = newnode(v);
        root = n;
        return BST_SUCCESS;
    }
        // already exists in tree ==> can't insert
        //if (root->val == v)
        //result = BST_FAIL;
    else if (v < root->data) {
        // key value less than key value in root node - try to insert into left
        // subtree, if it exists.
        if (root->left!= NULL)
            // there is a left subtree - insert it
            result = insert(v, root->left);
        else {
            // new node becomes the left subtree
            node *n = newnode(v);
            root->left = n;
            result = BST_SUCCESS;
        }
    } else {         // test actually redundant
        // key is greater than this nodes key value, so value goes into right
        // subtree, if it exists
        if (root->right != NULL)
            // there is a right subtree - insert new node
            result = insert(v,root->right);
        else {
            // no right subtree - new node becomes right subtree
            node*n = newnode(v);
            root->right = n;
            result = BST_SUCCESS;
        }
    }
    return result;
}//insert()

void *Merge(node *r1, node *r2){
    if (r2 == NULL) return;
    Merge(r1,r2->left);
    int i = r2->data;
    insert(i,r1);
    Merge(r1,r2->right);
}

int tree_height(node* root) {
    // Get the height of the tree
    if (!root)
        return 0;
    else {
        // Find the height of both subtrees
        // and use the larger one
        int left_height = tree_height(root->left);
        int right_height = tree_height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

void print_level(node* root, int level_no) {

    if (!root)
        return;
    if (level_no == 0) {
        // We are at the top of a subtree
        // So print the auxiliary root node
        array[j] = root->data;
        j++;
    }
    else {
        // Make the auxiliary root node to
        // be the left and right nodes for
        // the subtrees and decrease level by 1, since
        // you are moving from top to bottom
        print_level(root->left, level_no - 1);
        print_level(root->right, level_no - 1);
    }
}

void print_tree_level_order(node* root) {
    if (!root)
        return;
    int height = tree_height(root);
    for (int i=0; i<height; i++) {
        print_level(root, i);
    }
    printf("\n");
}

int main() {

    // Question 2

    int tree21[4] = {3,2,5,1};
    int tree22[5] = {4,1,7,2,9};

    int l1 = 4;
    int l2 = 5;

    node *t1 = newnode(tree21[0]);
    node *t2 = newnode(tree22[0]);

    for (int i = 1;i < l1;i++){
        insert(tree21[i],t1);
    }
    for (int i = 1;i < l2;i++){
        insert(tree22[i],t2);
    }

    Merge(t1,t2);

    print_tree_level_order(t1);

    for (int k = 0; k < 9;k++){
        printf("%d ",array[k]);
    }
}
