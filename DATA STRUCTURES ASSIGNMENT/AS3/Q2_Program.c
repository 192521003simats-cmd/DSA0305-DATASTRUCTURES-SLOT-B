#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
int key, height;
struct Node *left, *right;
} Node;
int getHeight(Node *n) {
return n ? n->height : 0;
}
int maximum(int a, int b) {
return a > b ? a : b;
}
void updateHeight(Node *n) {
n->height = 1 + maximum(
getHeight(n->left),
getHeight(n->right)
);
}
Node *rightRotate(Node *y) {
Node *x = y->left;
Node *t = x->right;
x->right = y;
y->left = t;
updateHeight(y);
updateHeight(x);
return x;
}
Node *leftRotate(Node *x) {
Node *y = x->right;
Node *t = y->left;
y->left = x;
x->right = t;
updateHeight(x);
updateHeight(y);
return y;
}
int getBalance(Node *n) {
return n ? getHeight(n->left) - getHeight(n->right) : 0;
}
Node *newNode(int key) {
Node *n = malloc(sizeof(Node));
n->key = key; n->height = 1; n->left = n->right = NULL;
return n;
}
Node *insert(Node *root, int key) {
if (!root) return newNode(key);
if (key < root->key) root->left = insert(root->left, key);
else if (key > root->key) root->right = insert(root->right, key);
else return root;
updateHeight(root);
int bal = getBalance(root);
if (bal > 1 && key < root->left->key) return rightRotate(root);
if (bal < -1 && key > root->right->key) return leftRotate(root);
if (bal > 1) { root->left = leftRotate(root->left); return rightRotate(root); }
if (bal < -1) { root->right = rightRotate(root->right); return leftRotate(root); }
return root;
}
void preorder(Node *n) {
if (!n) return;
printf("%d ", n->key);
preorder(n->left);
preorder(n->right);
}
int main(void) {
int prices[] = {10, 20, 30, 40, 50, 25};
Node *root = NULL;
for (int i = 0; i < 6; i++) root = insert(root, prices[i]);
printf("Preorder: ");
preorder(root);
printf("\nHeight: %d\n", getHeight(root));
return 0;
}
