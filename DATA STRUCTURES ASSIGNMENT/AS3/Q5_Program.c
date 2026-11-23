#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
int key;
struct Node *left, *right;
} Node;
Node *rightRotate(Node *x) {
Node *y = x->left;
x->left = y->right;
y->right = x;
return y;
}
Node *leftRotate(Node *x) {
Node *y = x->right;
x->right = y->left;
y->left = x;
return y;
}
Node *splay(Node *root, int key) {
if (root == NULL || root->key == key)
return root;
if (key < root->key) {
if (root->left == NULL)
return root;
if (key < root->left->key) {
root->left->left =
splay(root->left->left, key);
root = rightRotate(root);
} else if (key > root->left->key) {
root->left->right =
splay(root->left->right, key);
if (root->left->right)
root->left = leftRotate(root->left);
}
return root->left ? rightRotate(root) : root;
} else {
if (root->right == NULL)
return root;
if (key > root->right->key) {
root->right->right =
splay(root->right->right, key);
root = leftRotate(root);
} else if (key < root->right->key) {
root->right->left =
splay(root->right->left, key);
if (root->right->left)
root->right = rightRotate(root->right);
}
return root->right ? leftRotate(root) : root;
}
}
Node *newNode(int key) {
Node *n = malloc(sizeof(Node));
n->key = key; n->left = n->right = NULL;
return n;
}
Node *insert(Node *root, int key) {
if (!root) return newNode(key);
root = splay(root, key);
if (root->key == key) return root;
Node *n = newNode(key);
if (key < root->key) { n->right = root; n->left = root->left; root->left = NULL; }
else { n->left = root; n->right = root->right; root->right = NULL; }
return n;
}
int main(void) {
int keys[] = {5, 1, 7, 3, 9, 2, 8};
Node *root = NULL;
for (int i = 0; i < 7; i++) root = insert(root, keys[i]);
root = splay(root, 3);
printf("Root after accessing 3: %d\n", root->key);
root = splay(root, 9);
printf("Root after accessing 9: %d\n", root->key);
return 0;
}
