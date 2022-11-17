#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};
// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}
// A utility function to get the height of the tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return 1+max(height(N->left), height(N->right));
}

struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)
            malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 0; // new node is initially added at leaf
    return(node);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
// Perform rotation
    x->right = y;
    y->left = T2;
// Update heights
    y->height = height(y);
    x->height = height(x);
// Return new root
    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;
// Perform rotation
    y->left = x;
    x->right = T2;
// Update heights
    x->height = height(x);
    y->height = height(y);
// Return new root
    return y;
}
// Get Balance factor of node N
int getBalance(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insertBST(struct Node* node, int key) {
/* 1. Perform the normal BST insertion */
    if (node == NULL)
        return (newNode(key));
    if (key < node->key)
        node->left = insertBST(node->left, key);
    else if (key > node->key)
        node->right = insertBST(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
/* 2. Update height of this ancestor node */
    node->height = height(node);
    return node; /* return the (unchanged) node pointer */
}


struct Node* insertAVL(struct Node* node, int key)
{
/* 1. Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
/* 2. Update height of this ancestor node */
    node->height = height(node);
/* 3. Get the balance factor of this ancestor
node to check whether this node became
unbalanced */
    int balance = getBalance(node);
    // If this node becomes unbalanced, then there are 4 cases
// Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
// Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
// Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
// Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node; /* return the (unchanged) node pointer */
}

void preOrderPrint(struct Node *root)
{
    if(root != NULL)
    {
        printf("%d ",root->key);
        preOrderPrint(root->left);
        preOrderPrint(root->right);
    }
}

void preOrderAVL(struct Node *root,struct Node *avlRoot)
{
    if(root != NULL)
    {
        avlRoot = insertAVL(avlRoot,root->key);
        preOrderAVL(root->left,avlRoot);
        preOrderAVL(root->right,avlRoot);
    }
}

struct Node *Rotation(struct Node *root){
    struct Node *avl = NULL;
    preOrderAVL(root,avl);
    return avl;
}

int isBalanced(struct Node* root){
    /* for height of left subtree */
    int lheight;
    /* for height of right subtree */
    int rheight;
    /* If tree is empty then return true */
    if (root == NULL)
        return 1;
    // Check height of l-tree and r-tree
    lheight = height(root->left);
    rheight = height(root->right);
    if (abs(lheight - rheight) <= 1 && isBalanced(root->left)
        && isBalanced(root->right))
        return 1;
    // Not balanced
    return 0;
}

int main()
{
    struct Node *root = NULL;
    struct Node *test = NULL;
/* Constructing tree given in the above figure */
    root = insertBST(root, 12);
    root = insertBST(root, 8);
    root = insertBST(root, 18);
    root = insertBST(root, 17);
    root = insertBST(root, 5);
    root = insertBST(root, 9);
    root = insertBST(root, 5);
    root = insertBST(root, 4);
    root = insertBST(root, 2);

    printf("1 if balanced, else, 0: %d\n",isBalanced(root)); // Should output 0 as we have not yet balanced the tree

    printf("Preorder traversal of the BST tree is \n");
    preOrderPrint(root);
    printf("\nPreorder traversal of the constructed AVL tree is \n");

    return 0;
}
